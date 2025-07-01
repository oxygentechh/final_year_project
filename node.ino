#include <WiFi.h>
#include "painlessMesh.h"
#include <ArduinoJson.h>
#include <map>

// Pin Definitions
#define LED                 2     // Built-in LED

#define DHTPIN           14     // DHT sensor pin (use this for DHT)
#define PRESSURE_PIN     32     // BMP280 Pressure Sensor
#define DAYNIGHT_PIN     33     // LDR (use this for LDR)
#define AIR_QUALITY_PIN  34     // Air Quality Sensor (MQ135 or MQ-6)
#define GPS_RX_PIN       16     // GPS Module RX
#define GPS_TX_PIN       17     // GPS Module TX

// Network Configuration - Match with meshap.ino
#define MESH_PREFIX     "ESP32MeshAP"     // Match with root node
#define MESH_PASSWORD   "12345678"        // Match with root node
#define MESH_PORT       5555              // Match with root node
#define MESH_CHANNEL    6                 // Match with root node
#define MAX_RETRY       3                 // Maximum connection retry attempts
#define RETRY_INTERVAL  5000              // Retry interval in milliseconds
#define MIN_FREE_HEAP   20000            // Minimum free heap before restart

// Sensor Thresholds
#define TEMP_WARN_THRESHOLD    30.0   // Temperature warning level (°C)
#define TEMP_CRIT_THRESHOLD    45.0   // Temperature critical level (°C)
#define HUMID_WARN_THRESHOLD   75.0   // Humidity warning level (%)
#define HUMID_CRIT_THRESHOLD   90.0   // Humidity critical level (%)
#define DAYNIGHT_THRESHOLD     20     // Day/Night transition threshold (%)
#define AIR_QUALITY_WARN      150     // Air quality warning level (ppm)
#define AIR_QUALITY_CRIT      300     // Air quality critical level (ppm)

// Timing Configuration
#define SENSOR_READ_INTERVAL   3000   // Sensor reading interval (ms)
#define STATUS_UPDATE_INTERVAL 5000   // Status update interval (ms)
#define MESH_UPDATE_INTERVAL   1000   // Mesh network update interval (ms)

// Power Management
#define BATTERY_PIN           35     // Battery voltage monitoring
#define LOW_BATTERY_THRESHOLD 3.3    // Low battery warning voltage
#define CRIT_BATTERY_THRESHOLD 3.0   // Critical battery voltage

// Node base class with common functionality
#include <EEPROM.h>
#include <DHT.h>
#include <TinyGPSPlus.h>

#define EEPROM_SIZE 64
#define EEPROM_NAME_ADDR 0

bool hasDHT = false;
bool hasLDR = false;
bool hasGPS = false;
bool hasMQ6 = false;
String nodeName;

#define DHTTYPE DHT11   // DHT 11 or DHT22
DHT dht(DHTPIN, DHTTYPE);
TinyGPSPlus gps;
bool hasDHT = false;
bool hasLDR = false;
bool hasGPS = false;
bool hasAirQuality = false;
String nodeName;

class MeshNode {
protected:
    painlessMesh mesh;
    Scheduler userScheduler;
    
    // Configuration values are inherited from global definitions
    bool useDefaultMeshConfig = true;  // Set to false to override default mesh settings

    // Node state
    uint32_t nodeId;
    uint8_t nodeType;
    bool isActive;
    
    // Sensor configuration
    struct SensorConfig {
        bool hasTempHumidity;    // DHT22 - Combined temperature (-40 to 80°C) and humidity (0-100%) sensor
        bool hasPressure;        // BMP280 - Barometric pressure (300-1100 hPa) and altitude
        bool hasDayNight;        // LDR - Light level sensor for day/night detection (0-100%)
        bool hasAirQuality;      // Air quality sensor (MQ135 or MQ-6)
        bool hasGPS;             // NEO-6M - GPS module for location tracking
    } sensorConfig;

    // Sensor reading storage
    struct SensorReadings {
        struct {
            float temperature;    // Current temperature in Celsius
            float humidity;       // Current humidity percentage
        } tempHumidity;
        float pressure;          // Current pressure in hPa
        String dayNightStatus;   // Current light status: "day", "night", or "transition"
        float airQuality;        // Current air quality in ppm
        struct {
            float latitude;      // Current latitude in degrees
            float longitude;     // Current longitude in degrees
            float altitude;      // Current altitude in meters
            bool fix;           // GPS fix status
        } gpsData;
    } sensorReadings;

    // Node status
    struct NodeStatus {
        unsigned long lastUpdate;
        int signalStrength;
        float memoryUsage;
        uint32_t messagesSent;
        uint32_t messagesReceived;
    } status;

    // Add SCADA and disaster management support
    struct DisasterState {
        bool inDisaster;
        String disasterType;
        unsigned long disasterStartTime;
        float dangerLevel;
    } disasterState;

    struct PowerState {
        bool onMainPower;
        float batteryLevel;
        float powerConsumption;
    } powerState;

    // Enhanced sensor readings with thresholds
    struct SensorThresholds {
        float warningLevel;
        float criticalLevel;
    };
    std::map<String, SensorThresholds> sensorThresholds;

    // Task for sending sensor data
    Task taskSendData;

    // Task management
    Task taskReadSensors;
    Task taskUpdateStatus;
    Task taskCheckPower;

    // Status update task
    Task taskSendStatus;

    // Optimization variables
    unsigned long lastSendTime = 0;
    String lastSensorPayload;

public:
    MeshNode() : 
        taskSendData(TASK_SECOND * 3, TASK_FOREVER, [this]() { 
            sendSensorData(); 
        }),
        taskSendStatus(STATUS_UPDATE_INTERVAL, TASK_FOREVER, [this]() { 
            sendStatusUpdate(); 
        }) {
        
        // Initialize disaster state and power state
        disasterState.inDisaster = false;
        disasterState.dangerLevel = 0;
        
        powerState.onMainPower = true;
        powerState.batteryLevel = 100.0;
        powerState.powerConsumption = random(5, 15);

        // Set default thresholds
        setupDefaultThresholds();
    }

    virtual void init() {
        // EEPROM and node name logic (from mesh2.ino)
        EEPROM.begin(EEPROM_SIZE);
        String savedName = EEPROM.readString(EEPROM_NAME_ADDR);
        if (savedName.length() > 0 && savedName.length() < 32) {
            nodeName = savedName;
            Serial.println("[Node] Loaded name from EEPROM: " + nodeName);
        } else {
            uint32_t chipId = (uint32_t)ESP.getEfuseMac();
            nodeName = "Node_" + String(chipId, HEX);
            EEPROM.writeString(EEPROM_NAME_ADDR, nodeName);
            EEPROM.commit();
        }
        Serial.println("[Node] Booting " + nodeName);
        // Start serial and wait for it to be ready
        Serial.begin(115200);
        while (!Serial) delay(100);
        Serial.println("\nInitializing sensor node...");
        
        // Set up LED
        pinMode(LED, OUTPUT);
        digitalWrite(LED, HIGH);  // LED on during initialization
        
        // Set WiFi mode explicitly
        WiFi.mode(WIFI_STA);
        WiFi.persistent(false);  // Prevent flash wear
        
        // Initialize mesh with minimal debug output
        mesh.setDebugMsgTypes(ERROR | STARTUP);
        
        Serial.println("Starting mesh connection...");
        mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT, WIFI_STA, MESH_CHANNEL);
        
        // Set callbacks
        mesh.onReceive(std::bind(&MeshNode::receivedCallback, this, std::placeholders::_1, std::placeholders::_2));
        mesh.onNewConnection(std::bind(&MeshNode::newConnectionCallback, this, std::placeholders::_1));
        mesh.onChangedConnections(std::bind(&MeshNode::changedConnectionCallback, this));
        
        // Get node ID and configure
        nodeId = mesh.getNodeId();
        configureNode();
        
        // Sensor auto-detection (from mesh2.ino)
        // DHT
        dht.begin();
        delay(2500);
        bool dhtDetected = false;
        for (int i = 0; i < 5; i++) {
            float t = dht.readTemperature();
            float h = dht.readHumidity();
            Serial.printf("[Node][Detect] DHT Reading %d: Temp=%.2fC Hum=%.2f%%\n", i+1, t, h);
            if (!isnan(t)) {
                hasDHT = true;
                dhtDetected = true;
                Serial.println("[Node] DHT sensor detected.");
                break;
            }
            delay(700);
        }
        sensorConfig.hasTempHumidity = hasDHT;
        if (!dhtDetected) {
            hasDHT = false;
            sensorConfig.hasTempHumidity = false;
            Serial.println("[Node] DHT sensor not detected.");
        }
        // LDR
        pinMode(DAYNIGHT_PIN, INPUT);
        int ldrSum = 0;
        int ldrReadings = 10;
        bool ldrConnected = false;
        for (int i = 0; i < ldrReadings; i++) {
            int val = analogRead(DAYNIGHT_PIN);
            Serial.printf("[Node][Detect] LDR Reading %d: %d\n", i+1, val);
            ldrSum += val;
            delay(20);
            if (val > 10 && val < 4090) ldrConnected = true;
        }
        int ldrAvg = ldrSum / ldrReadings;
        hasLDR = ldrConnected;
        sensorConfig.hasDayNight = hasLDR;
        if (ldrConnected) {
            Serial.printf("[Node] LDR sensor detected. Avg value: %d\n", ldrAvg);
        } else {
            Serial.println("[Node] LDR sensor not detected.");
        }
        // GPS
        Serial2.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
        unsigned long start = millis();
        while (millis() - start < 2000) {
            if (Serial2.available()) {
                if (gps.encode(Serial2.read())) {
                    hasGPS = true;
                    Serial.println("[Node] GPS module detected.");
                    break;
                }
            }
        }
        sensorConfig.hasGPS = hasGPS;
        if (!hasGPS) Serial.println("[Node] GPS module not detected.");
        // Air Quality Sensor (MQ135 or MQ-6)
        pinMode(AIR_QUALITY_PIN, INPUT);
        int airVal = analogRead(AIR_QUALITY_PIN);
        hasAirQuality = (airVal >= 0 && airVal <= 4095);
        sensorConfig.hasAirQuality = hasAirQuality;
        if (hasAirQuality) {
            Serial.println("[Node] Air Quality sensor detected.");
        } else {
            Serial.println("[Node] Air Quality sensor not detected.");
        }

        // Initialize sensors (existing logic)
        initializeSensors();
        setupTasks();
        
        // Print node info
        Serial.println("\n=== Node Configuration ===");
        Serial.printf("Node ID: %u\n", nodeId);
        Serial.printf("Node Type: %d\n", nodeType);
        Serial.printf("Mesh SSID: %s\n", MESH_PREFIX);
        Serial.printf("Channel: %d\n", MESH_CHANNEL);
        Serial.println("Active Sensors:");
        if (sensorConfig.hasTempHumidity) Serial.println("- Temperature/Humidity");
        if (sensorConfig.hasPressure) Serial.println("- Pressure");
        if (sensorConfig.hasDayNight) Serial.println("- Day/Night");
        if (sensorConfig.hasAirQuality) Serial.println("- Air Quality");
        if (sensorConfig.hasGPS) Serial.println("- GPS");
        Serial.println("=======================\n");
        
        // Turn off LED to indicate completion
        digitalWrite(LED, LOW);
    }

    virtual void update() {
        static unsigned long lastCheck = 0;
        const unsigned long CHECK_INTERVAL = 10000; // 10 seconds
        
        mesh.update();
        userScheduler.execute();
        
        // Periodic connectivity check
        unsigned long now = millis();
        if (now - lastCheck >= CHECK_INTERVAL) {
            lastCheck = now;
            
            if (mesh.getNodeList().empty()) {
                Serial.println("No mesh connections detected.");
                // Flash LED to indicate no connection
                digitalWrite(LED, HIGH);
                delay(50);
                digitalWrite(LED, LOW);
                // Do NOT force mesh.init() here; let painlessMesh handle reconnection
            }
            
            // Print status
            Serial.printf("Connected nodes: %d\n", mesh.getNodeList().size());
            Serial.printf("Signal Strength: %d dBm\n", WiFi.RSSI());
        }
    }

protected:
    virtual void configureNode() {
        // Configure node type and sensors based on node ID
        nodeType = nodeId % 6;
        
        // Default all sensors to false
        sensorConfig = {false, false, false, false, false};
        
        switch(nodeType) {
            case 0:  // Full sensor suite
                sensorConfig = {true, true, true, true, true};
                break;
            case 1:  // Temp/humidity only
                sensorConfig = {true, false, false, false, false};
                break;
            case 2:  // Temp/humidity, pressure, and GPS
                sensorConfig = {true, true, false, false, true};
                break;
            case 3:  // Day/night and air quality
                sensorConfig = {false, false, true, true, false};
                break;
            case 4:  // Temp/humidity, pressure, and day/night
                sensorConfig = {true, true, true, false, false};
                break;
            case 5:  // GPS only
                sensorConfig = {false, false, false, false, true};
                break;
        }
    }

    void setupDefaultThresholds() {
        // Combined temperature/humidity sensor thresholds
        sensorThresholds["temperature"] = {30.0, 45.0};  // in Celsius
        sensorThresholds["humidity"] = {75.0, 90.0};     // in %
        
        // Day/Night sensor threshold (light level %)
        sensorThresholds["daynight"] = {20.0, 80.0};     // < 20% is night, > 80% is day
        
        // Water level thresholds (in cm)
        sensorThresholds["water_level"] = {50.0, 100.0};
        
        // Vibration thresholds (in g)
        sensorThresholds["vibration"] = {0.5, 2.0};
        
        // Air quality thresholds (in ppm)
        sensorThresholds["air_quality"] = {150.0, 300.0};
    }

    // --- Only process direct commands for this node; all sensor data/messages are handled by the root node (meshap.ino) ---
    virtual void receivedCallback(uint32_t from, String &msg) {
        // Only handle direct commands: REBOOT and NAME change
        if (msg == "REBOOT") {
            Serial.println("[Node] Reboot command received. Rebooting...");
            delay(500);
            ESP.restart();
            return;
        } else if (msg.startsWith("NAME:")) {
            String newName = msg.substring(5);
            nodeName = newName;
            EEPROM.writeString(EEPROM_NAME_ADDR, nodeName);
            EEPROM.commit();
            Serial.println("[Node] Name changed to: " + nodeName);
            return;
        }
        // Ignore all other messages (sensor data, alerts, status, etc.)
    }
    }

    // Accept threshold updates as in meshap.ino
    void handleCommand(uint32_t from, JsonDocument& doc) {
        if (doc.containsKey("command")) {
            const char* command = doc["command"];
            if (strcmp(command, "update_thresholds") == 0 && doc.containsKey("parameters")) {
                JsonObject params = doc["parameters"];
                for (JsonPair kv : params) {
                    if (sensorThresholds.find(kv.key().c_str()) != sensorThresholds.end()) {
                        float val = kv.value().as<float>();
                        sensorThresholds[kv.key().c_str()].warningLevel = val; // or set both warning/critical as needed
                    }
                }
            } else if (strcmp(command, "start_scenario") == 0) {
                disasterState.inDisaster = true;
                disasterState.disasterType = doc["scenarioType"].as<String>();
                disasterState.disasterStartTime = millis();
            } else if (strcmp(command, "stop_scenario") == 0) {
                disasterState.inDisaster = false;
                disasterState.disasterType = "";
            } else if (strcmp(command, "configure") == 0) {
                // Handle sensor configuration updates
                if (doc.containsKey("sensors")) {
                    JsonObject sensors = doc["sensors"];
                    sensorConfig.hasTempHumidity = sensors["tempHumidity"] | sensorConfig.hasTempHumidity;
                    sensorConfig.hasPressure = sensors["pressure"] | sensorConfig.hasPressure;
                    sensorConfig.hasDayNight = sensors["dayNight"] | sensorConfig.hasDayNight;
                    sensorConfig.hasAirQuality = sensors["airQuality"] | sensorConfig.hasAirQuality;
                    sensorConfig.hasGPS = sensors["gps"] | sensorConfig.hasGPS;
                    initializeSensors();
                }
            }
        }
    }

    virtual void newConnectionCallback(uint32_t nodeId) {
        Serial.printf("New Connection: Node %u\n", nodeId);
        digitalWrite(LED, HIGH);
        delay(500);
        digitalWrite(LED, LOW);
    }

    virtual void changedConnectionCallback() {
        Serial.println("Connection changed");
    }

    // --- OPTIMIZATION: Only send sensor data if changed or at interval ---
    virtual void sendSensorData() {
        // Print sensor data to serial (from mesh2.ino)
        if (hasDHT) {
            float t = dht.readTemperature();
            float h = dht.readHumidity();
            Serial.printf("[Node] DHT: Temp=%.2fC Hum=%.2f%%\n", t, h);
        }
        if (hasLDR) {
            int ldrVal = analogRead(DAYNIGHT_PIN);
            Serial.printf("[Node] LDR: %d\n", ldrVal);
        }
        if (hasGPS) {
            while (Serial2.available()) gps.encode(Serial2.read());
            if (gps.location.isValid()) {
                Serial.printf("[Node] GPS: Lat=%.6f Lon=%.6f\n", gps.location.lat(), gps.location.lng());
            }
        }
        if (hasAirQuality) {
            int airVal = analogRead(AIR_QUALITY_PIN);
            Serial.printf("[Node] Air Quality: %d\n", airVal);
            if (airVal > 2000) {
                Serial.println("[Node] Air Quality critical!");
            }
        }
        // Flash LED briefly to show transmission
        digitalWrite(LED, HIGH);
        
        DynamicJsonDocument doc(1024);
        doc["type"] = "sensor_data";
        doc["nodeId"] = nodeId;
        doc["nodeName"] = nodeName;
        JsonObject sensors = doc.createNestedObject("sensors");
        // Serialize all sensor values as strings (JSON for objects)
        if (hasDHT) {
            float t = dht.readTemperature();
            float h = dht.readHumidity();
            if (!isnan(t) && !isnan(h)) {
                DynamicJsonDocument thDoc(128);
                thDoc["temperature"] = t;
                thDoc["humidity"] = h;
                String thStr;
                serializeJson(thDoc, thStr);
                sensors["tempHumidity"] = thStr;
            }
        }
        if (hasLDR) {
            int ldrVal = analogRead(DAYNIGHT_PIN);
            String dayNightStr = ldrVal > 2000 ? "Day" : "Night";
            sensors["dayNight"] = dayNightStr;
        }
        if (hasGPS && gps.location.isValid()) {
            DynamicJsonDocument gpsDoc(128);
            gpsDoc["latitude"] = gps.location.lat();
            gpsDoc["longitude"] = gps.location.lng();
            gpsDoc["altitude"] = gps.altitude.meters();
            String gpsStr;
            serializeJson(gpsDoc, gpsStr);
            sensors["gps"] = gpsStr;
        }
        if (hasAirQuality) {
            int airVal = analogRead(AIR_QUALITY_PIN);
            sensors["airQuality"] = String(airVal);
        }
        String message;
        serializeJson(doc, message);
        mesh.sendBroadcast(message);
        digitalWrite(LED, LOW);
    }

    float simulateSensorValue(const String& type) {
        if (disasterState.inDisaster) {
            if (disasterState.disasterType == "flood") {
                if (type == "water_level") return 80.0 + random(-10, 20);
                if (type == "humidity") return 90.0 + random(-5, 10);
            } else if (disasterState.disasterType == "fire") {
                if (type == "temperature") return 50.0 + random(-5, 10);
                if (type == "air_quality") return 400.0 + random(-50, 100);
            } else if (disasterState.disasterType == "earthquake") {
                if (type == "vibration") return 3.0 + random(0, 20) / 10.0;
            }
        }

        if (type == "temperature") {
            return 20.0 + random(0, 100) / 10.0;
        } else if (type == "humidity") {
            return 40.0 + random(0, 300) / 10.0;
        } else if (type == "pressure") {
            return 980.0 + random(0, 400) / 10.0;
        } else if (type == "light") {
            return random(0, 1000);
        } else if (type == "air_quality") {
            return random(0, 500);
        } else if (type == "water_level") {
            return random(0, 100);
        } else if (type == "vibration") {
            return random(0, 50) / 100.0;
        }
        return 0;
    }

    void checkThreshold(const String& sensor, float value) {
        if (sensorThresholds.find(sensor) == sensorThresholds.end()) return;

        const auto& thresholds = sensorThresholds[sensor];
        DynamicJsonDocument doc(256);
        doc["type"] = "alert";
        doc["nodeId"] = nodeId;
        doc["sensor"] = sensor;
        doc["value"] = value;

        if (value >= thresholds.criticalLevel) {
            doc["severity"] = "critical";
            doc["message"] = sensor + " critical: " + String(value);
            String message;
            serializeJson(doc, message);
            mesh.sendBroadcast(message);
        } else if (value >= thresholds.warningLevel) {
            doc["severity"] = "warning";
            doc["message"] = sensor + " warning: " + String(value);
            String message;
            serializeJson(doc, message);
            mesh.sendBroadcast(message);
        }
    }

    // Initialize sensors based on configuration
    void initializeSensors() {
        if (sensorConfig.hasTempHumidity) {
            // Initialize DHT22
            pinMode(TEMP_HUMID_PIN, INPUT);
        }
        if (sensorConfig.hasPressure) {
            // Initialize BMP280
            pinMode(PRESSURE_PIN, INPUT);
        }
        if (sensorConfig.hasDayNight) {
            // Initialize LDR
            pinMode(DAYNIGHT_PIN, INPUT);
        }
        if (sensorConfig.hasAirQuality) {
            // Initialize MQ135
            pinMode(AIR_QUALITY_PIN, INPUT);
        }
        if (sensorConfig.hasGPS) {
            // Initialize GPS module
            Serial2.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
        }
        
        // Initialize battery monitoring
        pinMode(BATTERY_PIN, INPUT);
        
        // Initialize status LED
        pinMode(LED, OUTPUT);
    }

    // Read all configured sensors
    void readSensors() {
        if (sensorConfig.hasTempHumidity) {
            readTempHumidity();
        }
        if (sensorConfig.hasPressure) {
            readPressure();
        }
        if (sensorConfig.hasDayNight) {
            readDayNight();
        }
        if (sensorConfig.hasAirQuality) {
            readAirQuality();
        }
        if (sensorConfig.hasGPS) {
            readGPS();
        }
        
        // Always read battery level
        readBatteryLevel();
    }

    // Read temperature and humidity from DHT22
    void readTempHumidity() {
        // TODO: Implement DHT22 reading logic
        float temperature = analogRead(TEMP_HUMID_PIN) * 0.1; // Placeholder conversion
        float humidity = analogRead(TEMP_HUMID_PIN) * 0.1;    // Placeholder conversion
        
        sensorReadings.tempHumidity.temperature = temperature;
        sensorReadings.tempHumidity.humidity = humidity;
        
        // Check thresholds
        if (temperature > TEMP_CRIT_THRESHOLD || humidity > HUMID_CRIT_THRESHOLD) {
            // Trigger critical alert
            handleAlert("CRITICAL", "Temperature or humidity critical");
        } else if (temperature > TEMP_WARN_THRESHOLD || humidity > HUMID_WARN_THRESHOLD) {
            // Trigger warning
            handleAlert("WARNING", "Temperature or humidity warning");
        }
    }

    // Read pressure from BMP280
    void readPressure() {
        // TODO: Implement BMP280 reading logic
        float pressure = analogRead(PRESSURE_PIN) * 0.1; // Placeholder conversion
        sensorReadings.pressure = pressure;
    }

    // Read air quality from MQ135
    void readAirQuality() {
        float airQuality = analogRead(AIR_QUALITY_PIN);
        sensorReadings.airQuality = airQuality;
        
        if (airQuality > AIR_QUALITY_CRIT) {
            handleAlert("CRITICAL", "Air quality critical");
        } else if (airQuality > AIR_QUALITY_WARN) {
            handleAlert("WARNING", "Air quality warning");
        }
    }

    // Read GPS data if available
    void readGPS() {
        while (Serial2.available() > 0) {
            // TODO: Implement proper NMEA parsing
            if (Serial2.find("$GPGGA")) {
                String data = Serial2.readStringUntil('\n');
                // Parse GPS data (simplified)
                sensorReadings.gpsData.fix = true;
                // Placeholder values - implement actual parsing
                sensorReadings.gpsData.latitude = 0.0;
                sensorReadings.gpsData.longitude = 0.0;
                sensorReadings.gpsData.altitude = 0.0;
            }
        }
    }

    // Read day/night status from LDR
    void readDayNight() {
        int lightLevel = analogRead(DAYNIGHT_PIN);
        float percentage = (lightLevel / 4095.0) * 100.0;  // Convert to percentage
        
        if (percentage < DAYNIGHT_THRESHOLD) {
            sensorReadings.dayNightStatus = "night";
        } else if (percentage > DAYNIGHT_THRESHOLD + 10) {  // Add hysteresis
            sensorReadings.dayNightStatus = "day";
        } else {
            sensorReadings.dayNightStatus = "transition";
        }
    }

    // Read and monitor battery level
    void readBatteryLevel() {
        float batteryVoltage = (analogRead(BATTERY_PIN) / 4095.0) * 3.3 * 2; // Voltage divider
        powerState.batteryLevel = batteryVoltage;
        
        if (batteryVoltage < CRIT_BATTERY_THRESHOLD) {
            handleAlert("CRITICAL", "Battery critically low");
            enterLowPowerMode();
        } else if (batteryVoltage < LOW_BATTERY_THRESHOLD) {
            handleAlert("WARNING", "Battery low");
        }
    }

    // Power management functions
    void enterLowPowerMode() {
        // Disable non-essential sensors
        if (sensorConfig.hasGPS) {
            // Disable GPS
            Serial2.end();
        }
        
        // Reduce sensor reading frequency
        // TODO: Implement dynamic task scheduling based on power state
        
        // Adjust mesh network parameters
        mesh.setContainsRoot(false);  // Don't act as root node in low power
        
        powerState.onMainPower = false;
    }

    void updatePowerState() {
        static unsigned long lastPowerCheck = 0;
        const unsigned long POWER_CHECK_INTERVAL = 10000; // 10 seconds
        
        unsigned long now = millis();
        if (now - lastPowerCheck >= POWER_CHECK_INTERVAL) {
            lastPowerCheck = now;
            
            readBatteryLevel();
            
            // If on battery and level is critical, enter deep power save
            if (!powerState.onMainPower && powerState.batteryLevel < CRIT_BATTERY_THRESHOLD) {
                enterDeepPowerSave();
            }
        }
    }
    
    void enterDeepPowerSave() {
        Serial.println("Entering deep power save mode");
        
        // Increase intervals to reduce power consumption
        taskSendData.setInterval(TASK_MINUTE);
        taskReadSensors.setInterval(TASK_MINUTE);
        taskUpdateStatus.setInterval(TASK_MINUTE * 2);
        
        // Disable power-hungry sensors
        if (sensorConfig.hasGPS) {
            Serial2.end();
        }
        
        // Adjust WiFi power
        WiFi.setTxPower(WIFI_POWER_MINUS_1dBm); // Use minimum transmit power
        
        // Flash LED to indicate power save mode
        for (int i = 0; i < 3; i++) {
            digitalWrite(LED, HIGH);
            delay(100);
            digitalWrite(LED, LOW);
            delay(100);
        }
    }

    // Handle sensor alerts
    void handleAlert(const char* level, const char* message) {
        StaticJsonDocument<256> alert;
        alert["type"] = "alert";
        alert["nodeId"] = nodeId;
        alert["nodeName"] = nodeName;
        alert["severity"] = level;
        alert["message"] = message;
        alert["timestamp"] = millis();
        // Optionally include sensor and value if available (future-proof)
        // alert["sensor"] = ...;
        // alert["value"] = ...;
        String alertStr;
        serializeJson(alert, alertStr);
        mesh.sendBroadcast(alertStr);
        if (strcmp(level, "CRITICAL") == 0) {
            // Flash LED rapidly for critical alerts
            for (int i = 0; i < 5; i++) {
                digitalWrite(LED, HIGH);
                delay(100);
                digitalWrite(LED, LOW);
                delay(100);
            }
        }
    }

    // Remove redundant status broadcasts (sendStatusUpdate is enough)
    void updateStatus() {
        status.lastUpdate = millis();
        status.signalStrength = WiFi.RSSI();
        status.memoryUsage = ESP.getFreeHeap();
        // No need to broadcast status here, handled by sendStatusUpdate
    }

    void sendStatusUpdate() {
        if (!mesh.getNodeList().empty()) {
            DynamicJsonDocument doc(256);
            doc["type"] = "status";
            doc["nodeId"] = nodeId;
            doc["nodeName"] = nodeName;
            doc["battery"] = powerState.batteryLevel;
            doc["heap"] = ESP.getFreeHeap();
            String msg;
            serializeJson(doc, msg);
            mesh.sendBroadcast(msg);
        }
    }

    void setupTasks() {
        // Setup sensor reading task
        taskReadSensors.set(SENSOR_READ_INTERVAL, TASK_FOREVER, [this]() {
            this->readSensors();
        });
        userScheduler.addTask(taskReadSensors);
        taskReadSensors.enable();

        // Setup status update task
        taskUpdateStatus.set(STATUS_UPDATE_INTERVAL, TASK_FOREVER, [this]() {
            this->updateStatus();
        });
        userScheduler.addTask(taskUpdateStatus);
        taskUpdateStatus.enable();

        // Setup power monitoring task
        taskCheckPower.set(5000, TASK_FOREVER, [this]() {
            this->readBatteryLevel();
        });
        userScheduler.addTask(taskCheckPower);
        taskCheckPower.enable();

        // Setup periodic status update task
        userScheduler.addTask(taskSendStatus);
        taskSendStatus.enable();

        // Setup periodic sensor data broadcast (CRITICAL for all nodes)
        userScheduler.addTask(taskSendData);
        taskSendData.enable();
    }

    virtual void handleRemoteAlert(uint32_t from, JsonDocument& doc) {
        // Implement alert handling logic here if needed
    }

    virtual void enterPowerSaveMode() {
        // Implement power save logic here if needed
    }
};

// Create sensor node instance
MeshNode node;

void setup() {
    node.init();
}

void loop() {
    node.update();
}
