const char* FOOTER = R"rawliteral(
<footer class="footer">
  <div class="footer-content">
    <div class="footer-section">
      <h3>About</h3>
      <ul>
        <li>ESP32 Mesh Network Dashboard</li>
        <li>Open Source Project</li>
      </ul>
    </div>
    <div class="footer-section">
      <h3>Links</h3>
      <ul>
        <li><a href="/">Dashboard</a></li>
        <li><a href="/chatlog">Chat Log</a></li>
        <li><a href="/nodestack">Node Stack</a></li>
        <li><a href="/scada">SCADA</a></li>
        <li><a href="/disaster">Disaster Management</a></li>
      </ul>
    </div>
    <div class="footer-section">
      <h3>Contact</h3>
      <ul>
        <li>Email: raj.astitv03@gmail.com.com</li>
      </ul>
    </div>
    <div class="footer-section">
      <h3>Creators</h3>
      <ul>
        <li>Astitv Raj Chouhan</li>
        <li>Pankaj Kumar Verma</li>
      </ul>
    </div>
  </div>
  <div class="footer-bottom">
    &copy; 2024 ESP32 Mesh Project
  </div>
</footer>
)rawliteral";

const char* DASHBOARD_HTML = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 Mesh Network</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
    /* Begin COMMON_STYLES */
    :root {
        --primary-color: #0077ff;
        --background-light: #f4f4f4;
        --text-light: #333;
        --card-bg: #ffffff;
        --border-color: #dee2e6;
    }
    :root[data-theme='dark'] {
        --primary-color: #1a8fff;
        --background-light: #1a1a1a;
        --text-light: #ffffff;
        --card-bg: #2d2d2d;
        --border-color: #404040;
    }
    body {
        font-family: Arial, sans-serif;
        margin: 0;
        padding: 20px;
        background: var(--background-light);
        color: var(--text-light);
        transition: background-color 0.3s, color 0.3s;
    }
    .nav-bar {
        background: var(--primary-color);
        padding: 15px;
        margin-bottom: 20px;
        border-radius: 10px;
        display: flex;
        gap: 15px;
        align-items: center;
        justify-content: space-between;
    }
    .nav-links {
        display: flex;
        gap: 15px;
    }
    .nav-right {
        display: flex;
        align-items: center;
        gap: 15px;
    }
    .nav-link {
        color: white;
        text-decoration: none;
        padding: 8px 16px;
        border-radius: 5px;
        transition: background 0.3s;
    }
    .nav-link:hover {
        background: rgba(255, 255, 255, 0.2);
    }
    .nav-link.active {
        background: rgba(255, 255, 255, 0.3);
    }
    .settings-menu {
        position: relative;
        display: inline-block;
    }
    .settings-btn {
        background: none;
        border: none;
        color: white;
        font-size: 24px;
        cursor: pointer;
        padding: 8px;
        border-radius: 5px;
        transition: background 0.3s;
    }
    .settings-btn:hover {
        background: rgba(255, 255, 255, 0.2);
    }
    .settings-dropdown {
        position: absolute;
        right: 0;
        top: 100%;
        background: var(--card-bg);
        border: 1px solid var(--border-color);
        border-radius: 5px;
        padding: 10px;
        min-width: 200px;
        box-shadow: 0 2px 10px rgba(0,0,0,0.1);
        display: none;
        z-index: 1000;
    }
    .settings-dropdown.show {
        display: block;
    }
    .settings-item {
        padding: 8px 12px;
        display: flex;
        align-items: center;
        justify-content: space-between;
        border-radius: 5px;
        cursor: pointer;
        color: var(--text-light);
    }
    .settings-item:hover {
        background: var(--background-light);
    }
    .settings-divider {
        height: 1px;
        background: var(--border-color);
        margin: 8px 0;
    }
    .theme-switch {
        position: relative;
        display: inline-block;
        width: 50px;
        height: 24px;
    }
    .theme-switch input {
        opacity: 0;
        width: 0;
        height: 0;
    }
    .slider {
        position: absolute;
        cursor: pointer;
        top: 0;
        left: 0;
        right: 0;
        bottom: 0;
        background-color: #ccc;
        transition: .4s;
        border-radius: 24px;
    }
    .slider:before {
        position: absolute;
        content: "";
        height: 16px;
        width: 16px;
        left: 4px;
        bottom: 4px;
        background-color: white;
        transition: .4s;
        border-radius: 50%;
    }
    input:checked + .slider {
        background-color: var(--primary-color);
    }
    input:checked + .slider:before {
        transform: translateX(26px);
    }
    .footer {
        margin-top: 40px;
        padding: 20px;
        background: var(--card-bg);
        border-top: 1px solid var(--border-color);
        text-align: center;
        font-size: 0.9em;
        color: var(--text-light);
    }
    .footer-content {
        max-width: 1200px;
        margin: 0 auto;
        display: grid;
        grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
        gap: 20px;
        padding: 20px 0;
    }
    .footer-section {
        text-align: left;
    }
    .footer-section h3 {
        color: var(--primary-color);
        margin-bottom: 15px;
    }
    .footer-section ul {
        list-style: none;
        padding: 0;
        margin: 0;
    }
    .footer-section ul li {
        margin-bottom: 8px;
    }
    .footer-section a {
        color: var(--text-light);
        text-decoration: none;
        transition: color 0.3s;
    }
    .footer-section a:hover {
        color: var(--primary-color);
    }
    .footer-bottom {
        margin-top: 20px;
        padding-top: 20px;
        border-top: 1px solid var(--border-color);
        font-size: 0.8em;
    }
    .sensor-group {
        background: var(--background-light);
        padding: 10px;
        margin: 5px 0;
        border-radius: 5px;
    }
    .sensor-group h4 {
        margin: 0 0 5px 0;
        color: var(--primary-color);
    }
    .sensor-group p {
        margin: 3px 0;
    }
    .sensor-warning {
        color: #ffc107;
    }
    .sensor-critical {
        color: #dc3545;
    }
    .day-night-indicator {
        display: inline-block;
        width: 24px;
        height: 24px;
        border-radius: 50%;
        margin-left: 8px;
        vertical-align: middle;
    }
    .day-night-indicator.day {
        background: #ffd700;
        box-shadow: 0 0 10px rgba(255, 215, 0, 0.5);
    }
    .day-night-indicator.night {
        background: #1a237e;
        box-shadow: 0 0 10px rgba(26, 35, 126, 0.5);
    }
    .day-night-indicator.transition {
        background: linear-gradient(135deg, #ffd700 50%, #1a237e 50%);
    }
    .stat-item {
        text-align: center;
        padding: 15px;
        background: #f8f9fa;
        border-radius: 8px;
    }
    .stat-value {
        font-size: 24px;
        font-weight: bold;
        color: var(--primary-color);
    }
    .stat-label {
        font-size: 14px;
        color: #666;
        margin-top: 5px;
    }
    .node {
        position: absolute;
        width: 40px;
        height: 40px;
        border-radius: 50%;
        background: var(--primary-color);
        transform: translate(-50%, -50%);
        display: flex;
        align-items: center;
        justify-content: center;
        color: white;
        font-size: 12px;
        cursor: pointer;
        transition: all 0.3s ease;
    }
    .node:hover {
        transform: translate(-50%, -50%) scale(1.1);
        box-shadow: 0 0 10px rgba(0,119,255,0.5);
    }
    .node.root {
        background: #28a745;
        width: 50px;
        height: 50px;
        font-size: 14px;
    }
    .connection {
        position: absolute;
        height: 2px;
        background: rgba(0,119,255,0.3);
        transform-origin: left center;
        pointer-events: none;
    }
    .node-info {
        position: absolute;
        background: var(--card-bg);
        padding: 10px;
        border-radius: 5px;
        box-shadow: 0 2px 4px rgba(0,0,0,0.1);
        display: none;
        z-index: 10;
    }
    .node-info.show {
        display: block;
    }
    .dashboard-grid {
        display: flex;
        flex-wrap: wrap;
        gap: 24px;
        margin-bottom: 24px;
    }
    .card {
        background: var(--card-bg);
        border-radius: 12px;
        box-shadow: 0 2px 8px rgba(0,0,0,0.05);
        padding: 24px;
        flex: 1 1 350px;
        min-width: 350px;
        min-height: 350px;
        max-width: 600px;
        box-sizing: border-box;
        margin-bottom: 0;
    }
    .topology-view {
        min-width: 400px;
        max-width: 600px;
        min-height: 400px;
        height: 420px;
        position: relative;
        overflow: visible;
        margin-right: 0;
    }
    #topology-container {
        position: relative;
        width: 100%;
        height: 340px;
        min-height: 340px;
        background: #f0f6ff;
        border-radius: 10px;
        border: 1px solid var(--border-color);
        margin-top: 12px;
        margin-bottom: 0;
        overflow: visible;
    }
    #node-info {
        z-index: 20;
    }
    .node {
        position: absolute;
        width: 48px;
        height: 48px;
        border-radius: 50%;
        background: linear-gradient(135deg, var(--primary-color) 60%, #4fc3f7 100%);
        box-shadow: 0 2px 8px rgba(0,119,255,0.10), 0 0 0 4px rgba(0,119,255,0.08);
        transform: translate(-50%, -50%);
        display: flex;
        align-items: center;
        justify-content: center;
        color: #fff;
        font-size: 13px;
        font-weight: bold;
        cursor: pointer;
        transition: box-shadow 0.2s, transform 0.2s;
        border: 2px solid #fff;
        user-select: none;
        text-align: center;
        line-height: 1.2;
        letter-spacing: 0.5px;
    }
    .node:hover {
        transform: translate(-50%, -50%) scale(1.13);
        box-shadow: 0 0 18px 4px rgba(0,119,255,0.18);
        z-index: 10;
        border-color: #ffd700;
    }
    .node.root {
        background: linear-gradient(135deg, #28a745 60%, #b9f6ca 100%);
        width: 60px;
        height: 60px;
        font-size: 15px;
        border: 3px solid #fff;
        box-shadow: 0 4px 16px rgba(40,167,69,0.18);
    }
    .connection {
        position: absolute;
        height: 4px;
        background: linear-gradient(90deg, var(--primary-color), #b3e5fc);
        transform-origin: left center;
        pointer-events: none;
        border-radius: 2px;
        z-index: 1;
        opacity: 0.7;
    }
    .node-info {
        position: absolute;
        background: var(--card-bg);
        padding: 10px;
        border-radius: 5px;
        box-shadow: 0 2px 4px rgba(0,0,0,0.1);
        display: none;
        z-index: 30;
        min-width: 180px;
        max-width: 260px;
        font-size: 0.98em;
    }
    .node-info.show {
        display: block;
    }
    /* End COMMON_STYLES */
    /* Sensor icons */
    .sensor-icon {
        display: inline-block;
        width: 18px;
        height: 18px;
        margin: 2px 2px 0 2px;
        vertical-align: middle;
        border-radius: 4px;
        background: #fff;
        border: 1.5px solid var(--primary-color);
        box-shadow: 0 1px 3px rgba(0,119,255,0.08);
        text-align: center;
        font-size: 13px;
        color: var(--primary-color);
        line-height: 18px;
        font-weight: bold;
        cursor: default;
    }
    .sensor-icon[data-type="tempHumidity"]::after { content: "🌡️"; }
    .sensor-icon[data-type="pressure"]::after { content: "⏲️"; }
    .sensor-icon[data-type="airQuality"]::after { content: "🫧"; }
    .sensor-icon[data-type="gps"]::after { content: "📍"; }
    .sensor-icon[data-type="dayNight"]::after { content: "🌗"; }
    .sensor-icon[data-type="unknown"]::after { content: "?"; }
    </style>
</head>
<body>
    <div class="nav-bar">
        <div class="nav-links">
            <a href="/" class="nav-link" id="nav-dashboard">Dashboard</a>
            <a href="/chatlog" class="nav-link" id="nav-chatlog">Chat Log</a>
            <a href="/nodestack" class="nav-link" id="nav-nodestack">Node Stack</a>
            <a href="/scada" class="nav-link" id="nav-scada">SCADA</a>
            <a href="/disaster" class="nav-link" id="nav-disaster">Disaster Management</a>
        </div>
        <div class="nav-right">
            <div class="settings-menu">
                <button class="settings-btn">&#9881;</button>
                <div class="settings-dropdown">
                    <div class="settings-item">
                        <span>Dark Mode</span>
                        <label class="theme-switch">
                            <input type="checkbox" id="theme-toggle">
                            <span class="slider"></span>
                        </label>
                    </div>
                    <div class="settings-divider"></div>
                    <div class="settings-item">
                        <span>Refresh Rate</span>
                        <select id="refresh-rate">
                            <option value="1000">1s</option>
                            <option value="3000" selected>3s</option>
                            <option value="5000">5s</option>
                        </select>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <h2 class="page-title">Network Dashboard</h2>
    <div class="dashboard-grid">
        <div class="card topology-view">
            <h2>Network Topology</h2>
            <div id="topology-container" style="height: 100%;"></div>
            <div id="node-info" class="node-info"></div>
        </div>
        <div class="card">
            <h2>Network Statistics</h2>
            <div class="stats-view" id="stats-container"></div>
        </div>
    </div>
    ${FOOTER}
    <script>

        let nodePositions = new Map();
        let selectedNode = null;

        // --- Settings dropdown toggle logic ---
        document.addEventListener('DOMContentLoaded', function() {
            const settingsBtn = document.querySelector('.settings-btn');
            const settingsDropdown = document.querySelector('.settings-dropdown');
            if (settingsBtn && settingsDropdown) {
                settingsBtn.addEventListener('click', function(e) {
                    e.stopPropagation();
                    settingsDropdown.classList.toggle('show');
                });
                document.addEventListener('click', function(e) {
                    if (!settingsDropdown.contains(e.target) && !settingsBtn.contains(e.target)) {
                        settingsDropdown.classList.remove('show');
                    }
                });
            }
        });

        function updateDashboard() {
            Promise.all([
                fetch('/topology').then(response => response.json()),
                fetch('/stats').then(response => response.json()),
                fetch('/node-data').then(response => response.json())
            ]).then(([topology, stats, nodeData]) => {
                updateTopology(topology, nodeData);
                updateStats(stats);
            });
        }

        function updateTopology(topology, nodeData) {
            const container = document.getElementById('topology-container');
            container.innerHTML = '';
            
            // Calculate node positions if not already set
            if (nodePositions.size === 0) {
                calculateNodePositions(topology.nodes);
            }
            
            // Draw connections first
            topology.links.forEach(link => {
                const sourcePos = nodePositions.get(link.source);
                const targetPos = nodePositions.get(link.target);
                if (sourcePos && targetPos) {
                    drawConnection(container, sourcePos, targetPos, link.rssi);
                }
            });
            
            // Then draw nodes
            topology.nodes.forEach(node => {
                const pos = nodePositions.get(node.id);
                if (pos) {
                    const nodeEl = createNodeElement(node, nodeData.nodes.find(n => n.id === node.id));
                    nodeEl.style.left = pos.x + '%';
                    nodeEl.style.top = pos.y + '%';
                    container.appendChild(nodeEl);
                }
            });
        }

        function calculateNodePositions(nodes) {
            const centerX = 50;
            const centerY = 50;
            const radius = 35;
            
            // Position root node in center
            nodePositions.set(nodes[0].id, { x: centerX, y: centerY });
            
            // Position other nodes in a circle
            const angleStep = (2 * Math.PI) / (nodes.length - 1);
            nodes.slice(1).forEach((node, i) => {
                const angle = i * angleStep;
                nodePositions.set(node.id, {
                    x: centerX + radius * Math.cos(angle),
                    y: centerY + radius * Math.sin(angle)
                });
            });
        }

        function createNodeElement(node, nodeData) {
            const el = document.createElement('div');
            el.className = `node${node.type === 'root' ? ' root' : ''}`;
            let label = `<div>${node.type === 'root' ? 'Root' : 'Node'}<br><span style="font-size:11px;font-weight:normal;">${node.id}</span></div>`;

            // Add sensor icons if nodeData has sensorData
            if (nodeData && nodeData.sensorData) {
                label += '<div>';
                const sensors = nodeData.sensorData;
                for (const key in sensors) {
                    let type = key;
                    // For tempHumidity, show both temp and humidity as one icon
                    if (key === "tempHumidity") {
                        label += `<span class="sensor-icon" title="Temperature & Humidity" data-type="tempHumidity"></span>`;
                    } else if (key === "pressure") {
                        label += `<span class="sensor-icon" title="Pressure" data-type="pressure"></span>`;
                    } else if (key === "airQuality") {
                        label += `<span class="sensor-icon" title="Air Quality" data-type="airQuality"></span>`;
                    } else if (key === "gps") {
                        label += `<span class="sensor-icon" title="GPS" data-type="gps"></span>`;
                    } else if (key === "dayNight") {
                        label += `<span class="sensor-icon" title="Day/Night" data-type="dayNight"></span>`;
                    } else {
                        label += `<span class="sensor-icon" title="${key}" data-type="unknown"></span>`;
                    }
                }
                label += '</div>';
            }

            el.innerHTML = label;
            el.dataset.id = node.id;

            el.addEventListener('click', () => showNodeInfo(node, nodeData));
            el.addEventListener('mouseover', () => highlightConnections(node.id));
            el.addEventListener('mouseout', () => unhighlightConnections());

            return el;
        }

        function drawConnection(container, source, target, rssi) {
            const connection = document.createElement('div');
            connection.className = 'connection';
            
            const dx = target.x - source.x;
            const dy = target.y - source.y;
            const angle = Math.atan2(dy, dx);
            const length = Math.sqrt(dx * dx + dy * dy);
            
            connection.style.width = length + '%';
            connection.style.left = source.x + '%';
            connection.style.top = source.y + '%';
            connection.style.transform = `rotate(${angle}rad)`;
            
            // Add RSSI indicator
            connection.style.opacity = mapRSSIToOpacity(rssi);
            
            container.appendChild(connection);
        }

        function mapRSSIToOpacity(rssi) {
            // Map RSSI (-90 to -30) to opacity (0.2 to 1)
            return 0.2 + ((-rssi - 90) / (-30 - -90)) * 0.8;
        }

        function showNodeInfo(node, nodeData) {
            const info = document.getElementById('node-info');
            const pos = nodePositions.get(node.id);
            
            if (nodeData) {
                info.innerHTML = `
                    <h3>${node.type === 'root' ? 'Root Node' : 'Node'} ${node.id}</h3>
                    <p>Status: ${nodeData.isOnline ? 'Online' : 'Offline'}</p>
                    <p>Signal: ${nodeData.signalStrength} dBm</p>
                    <p>Last Seen: ${formatTimeDiff(nodeData.lastSeen)}</p>
                    ${nodeData.sensorData ? formatSensorInfo(nodeData.sensorData) : ''}
                `;
                
                info.style.left = `calc(${pos.x}% + 30px)`;
                info.style.top = `${pos.y}%`;
                info.classList.add('show');
                
                selectedNode = node.id;
            }
        }

        function formatSensorInfo(sensorData) {
            let info = '';
            
            // Format temperature and humidity
            if (sensorData.tempHumidity) {
                info += `
                    <div class="sensor-group">
                        <h4>Temperature & Humidity</h4>
                        <p>Temperature: ${sensorData.tempHumidity.temperature.toFixed(1)}°C</p>
                        <p>Humidity: ${sensorData.tempHumidity.humidity.toFixed(1)}%</p>
                    </div>`;
            }
            
            // Format pressure
            if (sensorData.pressure) {
                info += `
                    <div class="sensor-group">
                        <h4>Pressure</h4>
                        <p>${sensorData.pressure.toFixed(1)} hPa</p>
                    </div>`;
            }
            
            // Format day/night status
            if (sensorData.dayNight) {
                info += `
                    <div class="sensor-group">
                        <h4>Lighting</h4>
                        <p>Status: ${sensorData.dayNight}</p>
                    </div>`;
            }
            
            // Format air quality
            if (sensorData.airQuality) {
                info += `
                    <div class="sensor-group">
                        <h4>Air Quality</h4>
                        <p>${sensorData.airQuality} ppm</p>
                    </div>`;
            }
            
            // Format GPS data
            if (sensorData.gps) {
                info += `
                    <div class="sensor-group">
                        <h4>GPS Location</h4>
                        <p>Lat: ${sensorData.gps.latitude.toFixed(6)}</p>
                        <p>Lon: ${sensorData.gps.longitude.toFixed(6)}</p>
                        <p>Alt: ${sensorData.gps.altitude.toFixed(1)}m</p>
                    </div>`;
            }
            
            return info || '<p>No sensor data available</p>';
        }

        function formatTimeDiff(timestamp) {
            const diff = Date.now() - timestamp;
            if (diff < 1000) return 'Just now';
            if (diff < 60000) return Math.floor(diff/1000) + 's ago';
            if (diff < 3600000) return Math.floor(diff/60000) + 'm ago';
            return Math.floor(diff/3600000) + 'h ago';
        }

        function updateStats(data) {
            document.getElementById('stats-container').innerHTML = `
                <div class="stat-item">
                    <div class="stat-value">${data.connectedNodes}</div>
                    <div class="stat-label">Connected Nodes</div>
                </div>
                <div class="stat-item">
                    <div class="stat-value">${data.networkHealth}%</div>
                    <div class="stat-label">Network Health</div>
                </div>
                <div class="stat-item">
                    <div class="stat-value">${data.messageCount}</div>
                    <div class="stat-label">Messages</div>
                </div>
                <div class="stat-item">
                    <div class="stat-value">${Math.floor(data.uptime / 60)}</div>
                    <div class="stat-label">Uptime (min)</div>
                </div>
                <div class="stat-item">
                    <div class="stat-value" id="batteryAvg">N/A</div>
                    <div class="stat-label">Avg. Battery (%)</div>
                </div>
            `;
        }

        // Update every 3 seconds
        setInterval(updateDashboard, 3000);
        updateDashboard();
    </script>
</body>
</html>
)rawliteral";

const char* CHATLOG_HTML = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 Mesh Network - Chat Log</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        /* Begin COMMON_STYLES */
        :root {
            --primary-color: #0077ff;
            --background-light: #f4f4f4;
            --text-light: #333;
            --card-bg: #ffffff;
            --border-color: #dee2e6;
        }
        :root[data-theme='dark'] {
            --primary-color: #1a8fff;
            --background-light: #1a1a1a;
            --text-light: #ffffff;
            --card-bg: #2d2d2d;
            --border-color: #404040;
        }
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 20px;
            background: var(--background-light);
            color: var(--text-light);
            transition: background-color 0.3s, color 0.3s;
        }
        .nav-bar {
            background: var(--primary-color);
            padding: 15px;
            margin-bottom: 20px;
            border-radius: 10px;
            display: flex;
            gap: 15px;
            align-items: center;
            justify-content: space-between;
        }
        .nav-links {
            display: flex;
            gap: 15px;
        }
        .nav-right {
            display: flex;
            align-items: center;
            gap: 15px;
        }
        .nav-link {
            color: white;
            text-decoration: none;
            padding: 8px 16px;
            border-radius: 5px;
            transition: background 0.3s;
        }
        .nav-link:hover {
            background: rgba(255, 255, 255, 0.2);
        }
        .nav-link.active {
            background: rgba(255, 255, 255, 0.3);
        }
        .settings-menu {
            position: relative;
            display: inline-block;
        }
        .settings-btn {
            background: none;
            border: none;
            color: white;
            font-size: 24px;
            cursor: pointer;
            padding: 8px;
            border-radius: 5px;
            transition: background 0.3s;
        }
        .settings-btn:hover {
            background: rgba(255, 255, 255, 0.2);
        }
        .settings-dropdown {
            position: absolute;
            right: 0;
            top: 100%;
            background: var(--card-bg);
            border: 1px solid var(--border-color);
            border-radius: 5px;
            padding: 10px;
            min-width: 200px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
            display: none;
            z-index: 1000;
        }
        .settings-dropdown.show {
            display: block;
        }
        .settings-item {
            padding: 8px 12px;
            display: flex;
            align-items: center;
            justify-content: space-between;
            border-radius: 5px;
            cursor: pointer;
            color: var(--text-light);
        }
        .settings-item:hover {
            background: var(--background-light);
        }
        .settings-divider {
            height: 1px;
            background: var(--border-color);
            margin: 8px 0;
        }
        .theme-switch {
            position: relative;
            display: inline-block;
            width: 50px;
            height: 24px;
        }
        .theme-switch input {
            opacity: 0;
            width: 0;
            height: 0;
        }
        .slider {
            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background-color: #ccc;
            transition: .4s;
            border-radius: 24px;
        }
        .slider:before {
            position: absolute;
            content: "";
            height: 16px;
            width: 16px;
            left: 4px;
            bottom: 4px;
            background-color: white;
            transition: .4s;
            border-radius: 50%;
        }
        input:checked + .slider {
            background-color: var(--primary-color);
        }
        input:checked + .slider:before {
            transform: translateX(26px);
        }
        .footer {
            margin-top: 40px;
            padding: 20px;
            background: var(--card-bg);
            border-top: 1px solid var(--border-color);
            text-align: center;
            font-size: 0.9em;
            color: var(--text-light);
        }
        .footer-content {
            max-width: 1200px;
            margin: 0 auto;
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 20px;
            padding: 20px 0;
        }
        .footer-section {
            text-align: left;
        }
        .footer-section h3 {
            color: var(--primary-color);
            margin-bottom: 15px;
        }
        .footer-section ul {
            list-style: none;
            padding: 0;
            margin: 0;
        }
        .footer-section ul li {
            margin-bottom: 8px;
        }
        .footer-section a {
            color: var(--text-light);
            text-decoration: none;
            transition: color 0.3s;
        }
        .footer-section a:hover {
            color: var(--primary-color);
        }
        .footer-bottom {
            margin-top: 20px;
            padding-top: 20px;
            border-top: 1px solid var(--border-color);
            font-size: 0.8em;
        }
        .sensor-group {
            background: var(--background-light);
            padding: 10px;
            margin: 5px 0;
            border-radius: 5px;
        }
        .sensor-group h4 {
            margin: 0 0 5px 0;
            color: var(--primary-color);
        }
        .sensor-group p {
            margin: 3px 0;
        }
        .sensor-warning {
            color: #ffc107;
        }
        .sensor-critical {
            color: #dc3545;
        }
        .day-night-indicator {
            display: inline-block;
            width: 24px;
            height: 24px;
            border-radius: 50%;
            margin-left: 8px;
            vertical-align: middle;
        }
        .day-night-indicator.day {
            background: #ffd700;
            box-shadow: 0 0 10px rgba(255, 215, 0, 0.5);
        }
        .day-night-indicator.night {
            background: #1a237e;
            box-shadow: 0 0 10px rgba(26, 35, 126, 0.5);
        }
        .day-night-indicator.transition {
            background: linear-gradient(135deg, #ffd700 50%, #1a237e 50%);
        }
        .stat-item {
            text-align: center;
            padding: 15px;
            background: #f8f9fa;
            border-radius: 8px;
        }
        .stat-value {
            font-size: 24px;
            font-weight: bold;
            color: var(--primary-color);
        }
        .stat-label {
            font-size: 14px;
            color: #666;
            margin-top: 5px;
        }
        .node {
            position: absolute;
            width: 40px;
            height: 40px;
            border-radius: 50%;
            background: var(--primary-color);
            transform: translate(-50%, -50%);
            display: flex;
            align-items: center;
            justify-content: center;
            color: white;
            font-size: 12px;
            cursor: pointer;
            transition: all 0.3s ease;
        }
        .node:hover {
            transform: translate(-50%, -50%) scale(1.1);
            box-shadow: 0 0 10px rgba(0,119,255,0.5);
        }
        .node.root {
            background: #28a745;
            width: 50px;
            height: 50px;
            font-size: 14px;
        }
        .connection {
            position: absolute;
            height: 2px;
            background: rgba(0,119,255,0.3);
            transform-origin: left center;
            pointer-events: none;
        }
        .node-info {
            position: absolute;
            background: var(--card-bg);
            padding: 10px;
            border-radius: 5px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
            display: none;
            z-index: 10;
        }
        .node-info.show {
            display: block;
        }
        /* End COMMON_STYLES */
        .chat-container {
            max-width: 800px;
            margin: 0 auto;
            background: var(--card-bg);
            border-radius: 10px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
            overflow: hidden;
        }
        .messages {
            padding: 20px;
            max-height: 500px;
            overflow-y: auto;
        }
        .message {
            margin-bottom: 15px;
            padding: 10px 15px;
            border-radius: 8px;
            max-width: 80%;
        }
        .message.system {
            background: #fff3cd;
            color: #856404;
            margin-left: auto;
            margin-right: auto;
            text-align: center;
        }
        .message.node {
            background: #e9ecef;
            margin-right: auto;
        }
        .message-header {
            font-size: 0.8em;
            color: #666;
            margin-bottom: 5px;
        }
        .input-container {
            padding: 20px;
            background: #f8f9fa;
            border-top: 1px solid var(--border-color);
            display: flex;
            gap: 10px;
        }
        input[type="text"] {
            flex: 1;
            padding: 10px;
            border: 1px solid var(--border-color);
            border-radius: 5px;
            font-size: 16px;
        }
        button {
            padding: 10px 20px;
            background: var(--primary-color);
            color: white;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }
        button:hover {
            opacity: 0.9;
        }
        .system-toggle {
            display: flex;
            align-items: center;
            gap: 5px;
        }
    </style>
</head>
<body>
    <div class="nav-bar">
        <div class="nav-links">
            <a href="/" class="nav-link" id="nav-dashboard">Dashboard</a>
            <a href="/chatlog" class="nav-link" id="nav-chatlog">Chat Log</a>
            <a href="/nodestack" class="nav-link" id="nav-nodestack">Node Stack</a>
            <a href="/scada" class="nav-link" id="nav-scada">SCADA</a>
            <a href="/disaster" class="nav-link" id="nav-disaster">Disaster Management</a>
        </div>
        <div class="nav-right">
            <div class="settings-menu">
                <button class="settings-btn">&#9881;</button>
                <div class="settings-dropdown">
                    <div class="settings-item">
                        <span>Dark Mode</span>
                        <label class="theme-switch">
                            <input type="checkbox" id="theme-toggle">
                            <span class="slider"></span>
                        </label>
                    </div>
                    <div class="settings-divider"></div>
                    <div class="settings-item">
                        <span>Refresh Rate</span>
                        <select id="refresh-rate">
                            <option value="1000">1s</option>
                            <option value="3000" selected>3s</option>
                            <option value="5000">5s</option>
                        </select>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <h2 class="page-title">Chat Log</h2>
    <div class="chat-container">
        <div class="messages" id="messages"></div>
        <div class="input-container">
            <input type="text" id="message-input" placeholder="Type a message...">
            <div class="system-toggle">
                <input type="checkbox" id="system-message">
                <label for="system-message">System Message</label>
            </div>
            <button onclick="sendMessage()">Send</button>
        </div>
    </div>
    ${FOOTER}
    <script>

        // --- Settings dropdown toggle logic ---
        document.addEventListener('DOMContentLoaded', function() {
            const settingsBtn = document.querySelector('.settings-btn');
            const settingsDropdown = document.querySelector('.settings-dropdown');
            if (settingsBtn && settingsDropdown) {
                settingsBtn.addEventListener('click', function(e) {
                    e.stopPropagation();
                    settingsDropdown.classList.toggle('show');
                });
                document.addEventListener('click', function(e) {
                    if (!settingsDropdown.contains(e.target) && !settingsBtn.contains(e.target)) {
                        settingsDropdown.classList.remove('show');
                    }
                });
            }
        });

        function updateMessages() {
            fetch('/messages')
                .then(response => response.json())
                .then(messages => {
                    const container = document.getElementById('messages');
                    container.innerHTML = (messages.messages || []).map(msg => `
                        <div class="message ${msg.isSystem ? 'system' : 'node'}">
                            <div class="message-header">
                                ${msg.isSystem ? 'System Message' : 'Node ' + msg.nodeId}
                                - ${formatTimeDiff(msg.timestamp)}
                            </div>
                            ${msg.message}
                        </div>
                    `).join('');
                    container.scrollTop = container.scrollHeight;
                });
        }

        function sendMessage() {
            const input = document.getElementById('message-input');
            const isSystem = document.getElementById('system-message').checked;
            const message = input.value.trim();
            
            if (message) {
                fetch('/send-message', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/x-www-form-urlencoded',
                    },
                    body: `message=${encodeURIComponent(message)}&isSystem=${isSystem}`
                }).then(() => {
                    input.value = '';
                    updateMessages();
                });
            }
        }

        function formatTimeDiff(timestamp) {
            const diff = Date.now() - timestamp;
            if (diff < 1000) return 'Just now';
            if (diff < 60000) return Math.floor(diff/1000) + 's ago';
            if (diff < 3600000) return Math.floor(diff/60000) + 'm ago';
            return Math.floor(diff/3600000) + 'h ago';
        }

        // Enter key to send message
        document.getElementById('message-input').addEventListener('keypress', (e) => {
            if (e.key === 'Enter') {
                sendMessage();
            }
        });

        // Update every 2 seconds
        setInterval(updateMessages, 2000);
        updateMessages();
    </script>
</body>
</html>
)rawliteral";

const char* NODESTACK_HTML = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32MESH - Node Stack</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
        /* Begin COMMON_STYLES */
        :root {
            --primary-color: #0077ff;
            --background-light: #f4f4f4;
            --text-light: #333;
            --card-bg: #ffffff;
            --border-color: #dee2e6;
        }
        :root[data-theme='dark'] {
            --primary-color: #1a8fff;
            --background-light: #1a1a1a;
            --text-light: #ffffff;
            --card-bg: #2d2d2d;
            --border-color: #404040;
        }
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 20px;
            background: var(--background-light);
            color: var(--text-light);
            transition: background-color 0.3s, color 0.3s;
        }
        .nav-bar {
            background: var(--primary-color);
            padding: 15px;
            margin-bottom: 20px;
            border-radius: 10px;
            display: flex;
            gap: 15px;
            align-items: center;
            justify-content: space-between;
        }
        .nav-links {
            display: flex;
            gap: 15px;
        }
        .nav-right {
            display: flex;
            align-items: center;
            gap: 15px;
        }
        .nav-link {
            color: white;
            text-decoration: none;
            padding: 8px 16px;
            border-radius: 5px;
            transition: background 0.3s;
        }
        .nav-link:hover {
            background: rgba(255, 255, 255, 0.2);
        }
        .nav-link.active {
            background: rgba(255, 255, 255, 0.3);
        }
        .settings-menu {
            position: relative;
            display: inline-block;
        }
        .settings-btn {
            background: none;
            border: none;
            color: white;
            font-size: 24px;
            cursor: pointer;
            padding: 8px;
            border-radius: 5px;
            transition: background 0.3s;
        }
        .settings-btn:hover {
            background: rgba(255, 255, 255, 0.2);
        }
        .settings-dropdown {
            position: absolute;
            right: 0;
            top: 100%;
            background: var(--card-bg);
            border: 1px solid var(--border-color);
            border-radius: 5px;
            padding: 10px;
            min-width: 200px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
            display: none;
            z-index: 1000;
        }
        .settings-dropdown.show {
            display: block;
        }
        .settings-item {
            padding: 8px 12px;
            display: flex;
            align-items: center;
            justify-content: space-between;
            border-radius: 5px;
            cursor: pointer;
            color: var(--text-light);
        }
        .settings-item:hover {
            background: var(--background-light);
        }
        .settings-divider {
            height: 1px;
            background: var(--border-color);
            margin: 8px 0;
        }
        .theme-switch {
            position: relative;
            display: inline-block;
            width: 50px;
            height: 24px;
        }
        .theme-switch input {
            opacity: 0;
            width: 0;
            height: 0;
        }
        .slider {
            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background-color: #ccc;
            transition: .4s;
            border-radius: 24px;
        }
        .slider:before {
            position: absolute;
            content: "";
            height: 16px;
            width: 16px;
            left: 4px;
            bottom: 4px;
            background-color: white;
            transition: .4s;
            border-radius: 50%;
        }
        input:checked + .slider {
            background-color: var(--primary-color);
        }
        input:checked + .slider:before {
            transform: translateX(26px);
        }
        .footer {
            margin-top: 40px;
            padding: 20px;
            background: var(--card-bg);
            border-top: 1px solid var(--border-color);
            text-align: center;
            font-size: 0.9em;
            color: var(--text-light);
        }
        .footer-content {
            max-width: 1200px;
            margin: 0 auto;
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 20px;
            padding: 20px 0;
        }
        .footer-section {
            text-align: left;
        }
        .footer-section h3 {
            color: var(--primary-color);
            margin-bottom: 15px;
        }
        .footer-section ul {
            list-style: none;
            padding: 0;
            margin: 0;
        }
        .footer-section ul li {
            margin-bottom: 8px;
        }
        .footer-section a {
            color: var(--text-light);
            text-decoration: none;
            transition: color 0.3s;
        }
        .footer-section a:hover {
            color: var(--primary-color);
        }
        .footer-bottom {
            margin-top: 20px;
            padding-top: 20px;
            border-top: 1px solid var(--border-color);
            font-size: 0.8em;
        }
        .sensor-group {
            background: var(--background-light);
            padding: 10px;
            margin: 5px 0;
            border-radius: 5px;
        }
        .sensor-group h4 {
            margin: 0 0 5px 0;
            color: var(--primary-color);
        }
        .sensor-group p {
            margin: 3px 0;
        }
        .sensor-warning {
            color: #ffc107;
        }
        .sensor-critical {
            color: #dc3545;
        }
        .day-night-indicator {
            display: inline-block;
            width: 24px;
            height: 24px;
            border-radius: 50%;
            margin-left: 8px;
            vertical-align: middle;
        }
        .day-night-indicator.day {
            background: #ffd700;
            box-shadow: 0 0 10px rgba(255, 215, 0, 0.5);
        }
        .day-night-indicator.night {
            background: #1a237e;
            box-shadow: 0 0 10px rgba(26, 35, 126, 0.5);
        }
        .day-night-indicator.transition {
            background: linear-gradient(135deg, #ffd700 50%, #1a237e 50%);
        }
        .stat-item {
            text-align: center;
            padding: 15px;
            background: #f8f9fa;
            border-radius: 8px;
        }
        .stat-value {
            font-size: 24px;
            font-weight: bold;
            color: var(--primary-color);
        }
        .stat-label {
            font-size: 14px;
            color: #666;
            margin-top: 5px;
        }
        .node {
            position: absolute;
            width: 40px;
            height: 40px;
            border-radius: 50%;
            background: var(--primary-color);
            transform: translate(-50%, -50%);
            display: flex;
            align-items: center;
            justify-content: center;
            color: white;
            font-size: 12px;
            cursor: pointer;
            transition: all 0.3s ease;
        }
        .node:hover {
            transform: translate(-50%, -50%) scale(1.1);
            box-shadow: 0 0 10px rgba(0,119,255,0.5);
        }
        .node.root {
            background: #28a745;
            width: 50px;
            height: 50px;
            font-size: 14px;
        }
        .connection {
            position: absolute;
            height: 2px;
            background: rgba(0,119,255,0.3);
            transform-origin: left center;
            pointer-events: none;
        }
        .node-info {
            position: absolute;
            background: var(--card-bg);
            padding: 10px;
            border-radius: 5px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
            display: none;
            z-index: 10;
        }
        .node-info.show {
            display: block;
        }
        /* End COMMON_STYLES */
        .node-grid {
            display: grid;
            grid-template-columns: repeat(auto-fill, minmax(300px, 1fr));
            gap: 20px;
            margin-top: 20px;
        }
        .node-card {
            background: var(--card-bg);
            border-radius: 10px;
            padding: 20px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
        }
        .node-header {
            display: flex;
            align-items: center;
            gap: 10px;
            margin-bottom: 15px;
        }
        .status-indicator {
            width: 12px;
            height: 12px;
            border-radius: 50%;
        }
        .status-indicator.online {
            background: #28a745;
            box-shadow: 0 0 5px #28a745;
        }
        .status-indicator.offline {
            background: #dc3545;
            box-shadow: 0 0 5px #dc3545;
        }
        .node-title {
            font-size: 1.2em;
            font-weight: bold;
        }
        .metric-grid {
            display: grid;
            grid-template-columns: repeat(2, 1fr);
            gap: 10px;
            margin-bottom: 15px;
        }
        .metric {
            background: #f8f9fa;
            padding: 10px;
            border-radius: 5px;
        }
        .metric-label {
            font-size: 0.9em;
            color: #666;
        }
        .metric-value {
            font-size: 1.1em;
            font-weight: bold;
            color: var(--primary-color);
        }
        .sensor-data {
            margin-top: 15px;
            padding-top: 15px;
            border-top: 1px solid var(--border-color);
        }
        .sensor-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 10px;
        }
        .sensor-value {
            display: flex;
            align-items: center;
            gap: 10px;
        }
        .sensor-values {
            display: flex;
            gap: 20px;
        }
        .trend-indicator {
            width: 0;
            height: 0;
            border-left: 6px solid transparent;
            border-right: 6px solid transparent;
        }
        .daynight-indicator {
            padding: 5px 10px;
            border-radius: 5px;
            font-weight: bold;
        }
        .daynight-indicator.day {
            background: #ffd700;
            color: #000;
        }
        .daynight-indicator.night {
            background: #1a237e;
            color: #fff;
        }
        .daynight-indicator.transition {
            background: #78909c;
            color: #fff;
        }
        .trend-up {
            border-bottom: 8px solid #28a745;
        }
        .trend-down {
            border-top: 8px solid #dc3545;
        }
        .trend-stable {
            width: 8px;
            height: 2px;
            background: #6c757d;
        }
        .history-chart {
            height: 100px;
            background: rgba(0,119,255,0.1);
            border-radius: 5px;
            margin-top: 10px;
            position: relative;
            overflow: hidden;
        }
        .chart-tooltip {
            position: absolute;
            background: var(--card-bg);
            padding: 5px 10px;
            border-radius: 4px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
            pointer-events: none;
            display: none;
        }
    </style>
</head>
<body>
    <div class="nav-bar">
        <div class="nav-links">
            <a href="/" class="nav-link" id="nav-dashboard">Dashboard</a>
            <a href="/chatlog" class="nav-link" id="nav-chatlog">Chat Log</a>
            <a href="/nodestack" class="nav-link" id="nav-nodestack">Node Stack</a>
            <a href="/scada" class="nav-link" id="nav-scada">SCADA</a>
            <a href="/disaster" class="nav-link" id="nav-disaster">Disaster Management</a>
        </div>
        <div class="nav-right">
            <div class="settings-menu">
                <button class="settings-btn">&#9881;</button>
                <div class="settings-dropdown">
                    <div class="settings-item">
                        <span>Dark Mode</span>
                        <label class="theme-switch">
                            <input type="checkbox" id="theme-toggle">
                            <span class="slider"></span>
                        </label>
                    </div>
                    <div class="settings-divider"></div>
                    <div class="settings-item">
                        <span>Refresh Rate</span>
                        <select id="refresh-rate">
                            <option value="1000">1s</option>
                            <option value="3000" selected>3s</option>
                            <option value="5000">5s</option>
                        </select>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <h2 class="page-title">Node Stack</h2>
    <div class="node-grid" id="node-grid"></div>
    <div id="chart-tooltip" class="chart-tooltip"></div>
    ${FOOTER}
    <script>
        let nodeHistory = {};
        const maxHistoryPoints = 20;

        function updateNodes() {
            fetch('/node-data')
                .then(response => response.json())
                .then(data => {
                    const container = document.getElementById('node-grid');
                    container.innerHTML = data.nodes.map(node => {
                        updateNodeHistory(node);
                        return generateNodeCard(node);
                    }).join('');
                    
                    // Initialize charts after nodes are rendered
                    data.nodes.forEach(node => {
                        if (node.sensorData) {
                            Object.keys(node.sensorData).forEach(sensor => {
                                const chartId = `chart-${node.id}-${sensor}`;
                                const history = nodeHistory[node.id]?.sensors[sensor] || [];
                                drawChart(chartId, history);
                            });
                        }
                    });
                });
        }

        function updateNodeHistory(node) {
            if (!node.sensorData) return;

            if (!nodeHistory[node.id]) {
                nodeHistory[node.id] = {
                    sensors: {},
                    lastUpdate: Date.now()
                };
            }

            // Handle combined temperature/humidity sensor
            if (node.sensorData.tempHumidity) {
                // Track temperature history
                if (!nodeHistory[node.id].sensors.temperature) {
                    nodeHistory[node.id].sensors.temperature = [];
                }
                nodeHistory[node.id].sensors.temperature.push({
                    value: parseFloat(node.sensorData.tempHumidity.temperature),
                    timestamp: Date.now()
                });

                // Track humidity history
                if (!nodeHistory[node.id].sensors.humidity) {
                    nodeHistory[node.id].sensors.humidity = [];
                }
                nodeHistory[node.id].sensors.humidity.push({
                    value: parseFloat(node.sensorData.tempHumidity.humidity),
                    timestamp: Date.now()
                });

                // Maintain history size limits
                if (nodeHistory[node.id].sensors.temperature.length > maxHistoryPoints) {
                    nodeHistory[node.id].sensors.temperature.shift();
                }
                if (nodeHistory[node.id].sensors.humidity.length > maxHistoryPoints) {
                    nodeHistory[node.id].sensors.humidity.shift();
                }
            }

            // Handle other sensors (excluding dayNight as it's state-based)
            Object.entries(node.sensorData).forEach(([sensor, value]) => {
                if (sensor !== 'tempHumidity' && sensor !== 'dayNight') {
                    if (!nodeHistory[node.id].sensors[sensor]) {
                        nodeHistory[node.id].sensors[sensor] = [];
                    }

                    nodeHistory[node.id].sensors[sensor].push({
                        value: parseFloat(value),
                        timestamp: Date.now()
                    });

                    // Keep only the last maxHistoryPoints points
                    if (nodeHistory[node.id].sensors[sensor].length > maxHistoryPoints) {
                        nodeHistory[node.id].sensors[sensor].shift();
                    }
                }
            });
        }

        function generateNodeCard(node) {
            return `
                <div class="node-card">
                    <div class="node-header">
                        <div class="status-indicator ${node.isOnline ? 'online' : 'offline'}"></div>
                        <div class="node-title">
                            ${node.type === 'root' ? 'Root Node' : 'Node'} ${node.id}
                            ${node.nodeName ? `<span style='font-size:0.9em; color:#888; margin-left:8px;'>("${node.nodeName}")</span>` : ''}
                        </div>
                    </div>
                    <div class="metric-grid">
                        <div class="metric">
                            <div class="metric-label">Signal Strength</div>
                            <div class="metric-value">${node.signalStrength} dBm</div>
                        </div>
                        <div class="metric">
                            <div class="metric-label">Last Seen</div>
                            <div class="metric-value">${formatTimeDiff(node.lastSeen)}</div>
                        </div>
                    </div>
                    ${node.sensorData ? generateSensorSection(node) : ''}
                </div>
            `;
        }

        function generateSensorSection(node) {
            const sensorSections = [];
            
            // Handle tempHumidity combined sensor
            if (node.sensorData.tempHumidity) {
                const tempHistory = nodeHistory[node.id]?.sensors?.temperature || [];
                const humidityHistory = nodeHistory[node.id]?.sensors?.humidity || [];
                const tempTrend = calculateTrend(tempHistory);
                const humidityTrend = calculateTrend(humidityHistory);
                
                sensorSections.push(`
                    <div class="sensor-data">
                        <div class="sensor-header">
                            <h3>Temperature & Humidity</h3>
                            <div class="sensor-values">
                                <div class="sensor-value">
                                    <div class="trend-indicator ${tempTrend}"></div>
                                    <span>${node.sensorData.tempHumidity.temperature}°C</span>
                                </div>
                                <div class="sensor-value">
                                    <div class="trend-indicator ${humidityTrend}"></div>
                                    <span>${node.sensorData.tempHumidity.humidity}%</span>
                                </div>
                            </div>
                        </div>
                        <div class="history-chart" id="chart-${node.id}-temphumidity"></div>
                    </div>
                `);
            }

            // Handle dayNight sensor
            if (node.sensorData.dayNight) {
                sensorSections.push(`
                    <div class="sensor-data">
                        <div class="sensor-header">
                            <h3>Day/Night Status</h3>
                            <div class="sensor-value">
                                <span class="daynight-indicator ${node.sensorData.dayNight.toLowerCase()}">
                                    ${node.sensorData.dayNight}
                                </span>
                            </div>
                        </div>
                    </div>
                `);
            }

            // Handle other sensors
            Object.entries(node.sensorData).forEach(([sensor, value]) => {
                if (sensor !== 'tempHumidity' && sensor !== 'dayNight') {
                    const history = nodeHistory[node.id]?.sensors[sensor] || [];
                    const trend = calculateTrend(history);
                    
                    sensorSections.push(`
                        <div class="sensor-data">
                            <div class="sensor-header">
                                <h3>${formatSensorName(sensor)}</h3>
                                <div class="sensor-value">
                                    <div class="trend-indicator ${trend}"></div>
                                    <span>${value}</span>
                                </div>
                            </div>
                            <div class="history-chart" id="chart-${node.id}-${sensor}"></div>
                        </div>
                    `);
                }
            });

            return sensorSections.join('');
        }

        function formatSensorName(sensor) {
            return sensor.split('_')
                .map(word => word.charAt(0).toUpperCase() + word.slice(1))
                .join(' ');
        }

        function calculateTrend(history) {
            if (history.length < 2) return 'trend-stable';
            const last = history[history.length - 1].value;
            const prev = history[history.length - 2].value;
            const diff = last - prev;
            if (Math.abs(diff) < 0.1) return 'trend-stable';
            return diff > 0 ? 'trend-up' : 'trend-down';
        }

        function drawChart(chartId, history) {
            const container = document.getElementById(chartId);
            if (!container || history.length < 2) return;

            const values = history.map(h => h.value);
            const min = Math.min(...values);
            const max = Math.max(...values);
            const range = max - min || 1;
            
            const points = history.map((h, i) => {
                const x = (i / (history.length - 1)) * 100;
                const y = 100 - ((h.value - min) / range * 100);
                return `${x},${y}`;
            }).join(' ');

            const svg = `
                <svg width="100%" height="100%" preserveAspectRatio="none">
                    <polyline
                        points="${points}"
                        fill="none"
                        stroke="var(--primary-color)"
                        stroke-width="2"
                    />
                </svg>
            `;

            container.innerHTML = svg;

            // Add hover effect
            container.addEventListener('mousemove', (e) => {
                const rect = container.getBoundingClientRect();
                const x = (e.clientX - rect.left) / rect.width;
                const index = Math.floor(x * (history.length - 1));
                
                if (index >= 0 && index < history.length) {
                    const tooltip = document.getElementById('chart-tooltip');
                    tooltip.style.display = 'block';
                    tooltip.style.left = `${e.clientX + 10}px`;
                    tooltip.style.top = `${e.clientY + 10}px`;
                    tooltip.textContent = `${history[index].value}`;
                }
            });

            container.addEventListener('mouseleave', () => {
                document.getElementById('chart-tooltip').style.display = 'none';
            });
        }

        function formatTimeDiff(timestamp) {
            const diff = Date.now() - timestamp;
            if (diff < 1000) return 'Just now';
            if (diff < 60000) return Math.floor(diff/1000) + 's ago';
            if (diff < 3600000) return Math.floor(diff/60000) + 'm ago';
            return Math.floor(diff/3600000) + 'h ago';
        }

        // Update every 3 seconds
        setInterval(updateNodes, 3000);
        // Initial update
        updateNodes();
    </script>
</body>
</html>
)rawliteral";

const char* SCADA_HTML = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32MESH - SCADA Control</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
        /* Begin COMMON_STYLES */
        :root {
            --primary-color: #0077ff;
            --background-light: #f4f4f4;
            --text-light: #333;
            --card-bg: #ffffff;
            --border-color: #dee2e6;
        }
        :root[data-theme='dark'] {
            --primary-color: #1a8fff;
            --background-light: #1a1a1a;
            --text-light: #ffffff;
            --card-bg: #2d2d2d;
            --border-color: #404040;
        }
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 20px;
            background: var(--background-light);
            color: var(--text-light);
            transition: background-color 0.3s, color 0.3s;
        }
        .nav-bar {
            background: var(--primary-color);
            padding: 15px;
            margin-bottom: 20px;
            border-radius: 10px;
            display: flex;
            gap: 15px;
            align-items: center;
            justify-content: space-between;
        }
        .nav-links {
            display: flex;
            gap: 15px;
        }
        .nav-right {
            display: flex;
            align-items: center;
            gap: 15px;
        }
        .nav-link {
            color: white;
            text-decoration: none;
            padding: 8px 16px;
            border-radius: 5px;
            transition: background 0.3s;
        }
        .nav-link:hover {
            background: rgba(255, 255, 255, 0.2);
        }
        .nav-link.active {
            background: rgba(255, 255, 255, 0.3);
        }
        .settings-menu {
            position: relative;
            display: inline-block;
        }
        .settings-btn {
            background: none;
            border: none;
            color: white;
            font-size: 24px;
            cursor: pointer;
            padding: 8px;
            border-radius: 5px;
            transition: background 0.3s;
        }
        .settings-btn:hover {
            background: rgba(255, 255, 255, 0.2);
        }
        .settings-dropdown {
            position: absolute;
            right: 0;
            top: 100%;
            background: var(--card-bg);
            border: 1px solid var(--border-color);
            border-radius: 5px;
            padding: 10px;
            min-width: 200px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
            display: none;
            z-index: 1000;
        }
        .settings-dropdown.show {
            display: block;
        }
        .settings-item {
            padding: 8px 12px;
            display: flex;
            align-items: center;
            justify-content: space-between;
            border-radius: 5px;
            cursor: pointer;
            color: var(--text-light);
        }
        .settings-item:hover {
            background: var(--background-light);
        }
        .settings-divider {
            height: 1px;
            background: var(--border-color);
            margin: 8px 0;
        }
        .theme-switch {
            position: relative;
            display: inline-block;
            width: 50px;
            height: 24px;
        }
        .theme-switch input {
            opacity: 0;
            width: 0;
            height: 0;
        }
        .slider {
            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background-color: #ccc;
            transition: .4s;
            border-radius: 24px;
        }
        .slider:before {
            position: absolute;
            content: "";
            height: 16px;
            width: 16px;
            left: 4px;
            bottom: 4px;
            background-color: white;
            transition: .4s;
            border-radius: 50%;
        }
        input:checked + .slider {
            background-color: var(--primary-color);
        }
        input:checked + .slider:before {
            transform: translateX(26px);
        }
        .footer {
            margin-top: 40px;
            padding: 20px;
            background: var(--card-bg);
            border-top: 1px solid var(--border-color);
            text-align: center;
            font-size: 0.9em;
            color: var(--text-light);
        }
        .footer-content {
            max-width: 1200px;
            margin: 0 auto;
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 20px;
            padding: 20px 0;
        }
        .footer-section {
            text-align: left;
        }
        .footer-section h3 {
            color: var(--primary-color);
            margin-bottom: 15px;
        }
        .footer-section ul {
            list-style: none;
            padding: 0;
            margin: 0;
        }
        .footer-section ul li {
            margin-bottom: 8px;
        }
        .footer-section a {
            color: var(--text-light);
            text-decoration: none;
            transition: color 0.3s;
        }
        .footer-section a:hover {
            color: var(--primary-color);
        }
        .footer-bottom {
            margin-top: 20px;
            padding-top: 20px;
            border-top: 1px solid var(--border-color);
            font-size: 0.8em;
        }
        .sensor-group {
            background: var(--background-light);
            padding: 10px;
            margin: 5px 0;
            border-radius: 5px;
        }
        .sensor-group h4 {
            margin: 0 0 5px 0;
            color: var(--primary-color);
        }
        .sensor-group p {
            margin: 3px 0;
        }
        .sensor-warning {
            color: #ffc107;
        }
        .sensor-critical {
            color: #dc3545;
        }
        .day-night-indicator {
            display: inline-block;
            width: 24px;
            height: 24px;
            border-radius: 50%;
            margin-left: 8px;
            vertical-align: middle;
        }
        .day-night-indicator.day {
            background: #ffd700;
            box-shadow: 0 0 10px rgba(255, 215, 0, 0.5);
        }
        .day-night-indicator.night {
            background: #1a237e;
            box-shadow: 0 0 10px rgba(26, 35, 126, 0.5);
        }
        .day-night-indicator.transition {
            background: linear-gradient(135deg, #ffd700 50%, #1a237e 50%);
        }
        .stat-item {
            text-align: center;
            padding: 15px;
            background: #f8f9fa;
            border-radius: 8px;
        }
        .stat-value {
            font-size: 24px;
            font-weight: bold;
            color: var(--primary-color);
        }
        .stat-label {
            font-size: 14px;
            color: #666;
            margin-top: 5px;
        }
        .node {
            position: absolute;
            width: 40px;
            height: 40px;
            border-radius: 50%;
            background: var(--primary-color);
            transform: translate(-50%, -50%);
            display: flex;
            align-items: center;
            justify-content: center;
            color: white;
            font-size: 12px;
            cursor: pointer;
            transition: all 0.3s ease;
        }
        .node:hover {
            transform: translate(-50%, -50%) scale(1.1);
            box-shadow: 0 0 10px rgba(0,119,255,0.5);
        }
        .node.root {
            background: #28a745;
            width: 50px;
            height: 50px;
            font-size: 14px;
        }
        .connection {
            position: absolute;
            height: 2px;
            background: rgba(0,119,255,0.3);
            transform-origin: left center;
            pointer-events: none;
        }
        .node-info {
            position: absolute;
            background: var(--card-bg);
            padding: 10px;
            border-radius: 5px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
            display: none;
            z-index: 10;
        }
        .node-info.show {
            display: block;
        }
        /* End COMMON_STYLES */
        .scada-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(400px, 1fr));
            gap: 20px;
            margin-top: 20px;
        }
        .scada-panel {
            background: var(--card-bg);
            border-radius: 10px;
            padding: 20px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
        }
        .control-panel {
            display: grid;
            grid-template-columns: repeat(2, 1fr);
            gap: 15px;
        }
        .control-item {
            padding: 15px;
            background: #f8f9fa;
            border-radius: 8px;
            text-align: center;
        }
        .control-value {
            font-size: 24px;
            font-weight: bold;
            margin: 10px 0;
        }
        .control-label {
            color: #666;
            font-size: 14px;
        }
        .control-slider {
            width: 100%;
            margin: 10px 0;
        }
        .status-indicator {
            display: inline-block;
            width: 12px;
            height: 12px;
            border-radius: 50%;
            margin-right: 8px;
        }
        .status-normal { background: #28a745; }
        .status-warning { background: #ffc107; }
        .status-critical { background: #dc3545; }
        .trend-chart {
            height: 200px;
            margin-top: 20px;
            background: rgba(0,119,255,0.1);
            border-radius: 5px;
        }
        .process-diagram {
            position: relative;
            width: 100%;
            height: 400px;
            background: #f8f9fa;
            border-radius: 10px;
            margin: 20px 0;
            overflow: hidden;
        }
        .component {
            position: absolute;
            width: 60px;
            height: 60px;
            background: var(--card-bg);
            border-radius: 10px;
            display: flex;
            align-items: center;
            justify-content: center;
            cursor: pointer;
            transition: transform 0.3s;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
        }
        .component:hover {
            transform: scale(1.1);
        }
        .component.active {
            border: 2px solid var(--primary-color);
        }
        .component.warning {
            border: 2px solid #ffc107;
        }
        .component.error {
            border: 2px solid #dc3545;
        }
        .connection {
            position: absolute;
            height: 2px;
            background: #666;
            transform-origin: left center;
        }
        .flow-indicator {
            position: absolute;
            width: 10px;
            height: 10px;
            background: var(--primary-color);
            border-radius: 50%;
            animation: flow 2s linear infinite;
        }
        .component-details {
            position: fixed;
            right: 20px;
            top: 100px;
            background: var(--card-bg);
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0 2px 8px rgba(0,0,0,0.2);
            min-width: 300px;
            z-index: 1000;
        }
        .chart-container {
            height: 200px;
            margin: 10px 0;
        }
        .control-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(150px, 1fr));
            gap: 10px;
            margin: 10px 0;
        }
        .control-item {
            padding: 10px;
            background: #f8f9fa;
            border-radius: 5px;
            text-align: center;
        }
        .simulation-speed {
            position: fixed;
            right: 20px;
            bottom: 20px;
            background: var(--card-bg);
            padding: 10px;
            border-radius: 5px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
        }
        @keyframes flow {
            0% { transform: translateX(0); opacity: 1; }
            100% { transform: translateX(100px); opacity: 0; }
        }
    </style>
</head>
<body>
    <div class="nav-bar">
        <div class="nav-links">
            <a href="/" class="nav-link" id="nav-dashboard">Dashboard</a>
            <a href="/chatlog" class="nav-link" id="nav-chatlog">Chat Log</a>
            <a href="/nodestack" class="nav-link" id="nav-nodestack">Node Stack</a>
            <a href="/scada" class="nav-link" id="nav-scada">SCADA</a>
            <a href="/disaster" class="nav-link" id="nav-disaster">Disaster Management</a>
        </div>
        <div class="nav-right">
            <div class="settings-menu">
                <button class="settings-btn">&#9881;</button>
                <div class="settings-dropdown">
                    <div class="settings-item">
                        <span>Dark Mode</span>
                        <label class="theme-switch">
                            <input type="checkbox" id="theme-toggle">
                            <span class="slider"></span>
                        </label>
                    </div>
                    <div class="settings-divider"></div>
                    <div class="settings-item">
                        <span>Refresh Rate</span>
                        <select id="refresh-rate">
                            <option value="1000">1s</option>
                            <option value="3000" selected>3s</option>
                            <option value="5000">5s</option>
                        </select>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <h2 class="page-title">SCADA Control Panel</h2>
    <div class="scada-grid">
        <div class="scada-panel">
            <h2>System Overview</h2>
            <div class="control-panel" id="system-overview">
                <!-- Will be populated dynamically -->
            </div>
        </div>
        <div class="scada-panel">
            <h2>Sensor Controls</h2>
            <div class="control-panel" id="sensor-controls">
                <!-- Will be populated dynamically -->
            </div>
        </div>
        <div class="scada-panel">
            <h2>Real-time Monitoring</h2>
            <div class="trend-chart" id="realtime-chart"></div>
        </div>
        <div class="process-diagram" id="processDiagram">
            <!-- Components will be added dynamically -->
        </div>
        <div class="component-details" id="componentDetails" style="display: none;">
            <h3 id="componentName">Component Details</h3>
            <div class="chart-container" id="componentChart"></div>
            <div class="control-grid" id="componentControls"></div>
            <button class="sim-button" onclick="toggleComponent()">Toggle Component</button>
            <button class="sim-button" onclick="optimizeComponent()">Optimize</button>
        </div>
        <div class="simulation-speed">
            <label>Simulation Speed: </label>
            <select id="scadaSpeed">
                <option value="0.5">0.5x</option>
                <option value="1" selected>1x</option>
                <option value="2">2x</option>
                <option value="5">5x</option>
            </select>
        </div>
    </div>
    ${FOOTER}
    <script>
        class ScadaSimulator {
            constructor() {
                this.components = new Map();
                this.connections = [];
                this.selectedComponent = null;
                this.isRunning = false;
                this.speed = 1;
                this.setupComponents();
                this.setupEventListeners();
                this.startSimulation();
            }

            setupComponents() {
                // Add components
                this.addComponent('pump1', 'Pump 1', 50, 50);
                this.addComponent('pump2', 'Pump 2', 50, 200);
                this.addComponent('tank1', 'Tank 1', 200, 125);
                this.addComponent('valve1', 'Valve 1', 350, 125);
                this.addComponent('sensor1', 'Sensor 1', 500, 125);

                // Add connections
                this.addConnection('pump1', 'tank1');
                this.addConnection('pump2', 'tank1');
                this.addConnection('tank1', 'valve1');
                this.addConnection('valve1', 'sensor1');
            }

            addComponent(id, name, x, y) {
                const component = {
                    id,
                    name,
                    x,
                    y,
                    status: 'active',
                    efficiency: 100,
                    temperature: 25,
                    pressure: 100,
                    flow: 50,
                    history: {
                        efficiency: [],
                        temperature: [],
                        pressure: [],
                        flow: []
                    }
                };

                const el = document.createElement('div');
                el.className = 'component';
                el.id = id;
                el.style.left = x + 'px';
                el.style.top = y + 'px';
                el.innerHTML = name;
                el.onclick = () => this.selectComponent(id);

                document.getElementById('processDiagram').appendChild(el);
                this.components.set(id, component);
            }

            addConnection(from, to) {
                const fromComp = this.components.get(from);
                const toComp = this.components.get(to);

                const dx = toComp.x - fromComp.x;
                const dy = toComp.y - fromComp.y;
                const angle = Math.atan2(dy, dx);
                const length = Math.sqrt(dx * dx + dy * dy);

                const connection = document.createElement('div');
                connection.className = 'connection';
                connection.style.left = (fromComp.x + 30) + 'px';
                connection.style.top = (fromComp.y + 30) + 'px';
                connection.style.width = length + 'px';
                connection.style.transform = `rotate(${angle}rad)`;

                document.getElementById('processDiagram').appendChild(connection);
                this.connections.push({ from, to, element: connection });
            }

            selectComponent(id) {
                this.selectedComponent = id;
                const component = this.components.get(id);
                
                document.getElementById('componentName').textContent = component.name;
                document.getElementById('componentDetails').style.display = 'block';
                
                this.updateComponentDetails(component);
            }

            updateComponentDetails(component) {
                const controls = document.getElementById('componentControls');
                controls.innerHTML = `
                    <div class="control-item">
                        <div>Efficiency</div>
                        <div class="control-value">${component.efficiency}%</div>
                    </div>
                    <div class="control-item">
                        <div>Temperature</div>
                        <div class="control-value">${component.temperature}°C</div>
                    </div>
                    <div class="control-item">
                        <div>Pressure</div>
                        <div class="control-value">${component.pressure} kPa</div>
                    </div>
                    <div class="control-item">
                        <div>Flow Rate</div>
                        <div class="control-value">${component.flow} L/min</div>
                    </div>
                `;

                this.updateComponentChart(component);
            }

            updateComponentChart(component) {
                // Update chart with historical data
                const chartContainer = document.getElementById('componentChart');
                // ... implement chart drawing logic ...
            }

            startSimulation() {
                this.isRunning = true;
                this.animate();
            }

            animate() {
                if (!this.isRunning) return;

                this.updateComponents();
                this.updateFlowIndicators();

                requestAnimationFrame(() => this.animate());
            }

            updateComponents() {
                for (const [id, component] of this.components) {
                    // Update component values with some random variation
                    component.efficiency += (Math.random() - 0.5) * this.speed;
                    component.temperature += (Math.random() - 0.5) * this.speed;
                    component.pressure += (Math.random() - 0.5) * this.speed * 2;
                    component.flow += (Math.random() - 0.5) * this.speed * 3;

                    // Keep values within reasonable ranges
                    component.efficiency = Math.max(0, Math.min(100, component.efficiency));
                    component.temperature = Math.max(0, Math.min(100, component.temperature));
                    component.pressure = Math.max(0, Math.min(200, component.pressure));
                    component.flow = Math.max(0, Math.min(100, component.flow));

                    // Update component status
                    this.updateComponentStatus(id, component);

                    // Store historical data
                    this.updateComponentHistory(component);

                    // Update display if this is the selected component
                    if (id === this.selectedComponent) {
                        this.updateComponentDetails(component);
                    }
                }
            }

            updateComponentStatus(id, component) {
                const el = document.getElementById(id);
                el.classList.remove('active', 'warning', 'error');

                if (component.efficiency < 60) {
                    el.classList.add('error');
                    this.triggerAlert(component.name + ' efficiency critical');
                } else if (component.efficiency < 80) {
                    el.classList.add('warning');
                } else {
                    el.classList.add('active');
                }
            }

            updateComponentHistory(component) {
                const maxHistory = 100;
                component.history.efficiency.push(component.efficiency);
                component.history.temperature.push(component.temperature);
                component.history.pressure.push(component.pressure);
                component.history.flow.push(component.flow);

                if (component.history.efficiency.length > maxHistory) {
                    component.history.efficiency.shift();
                    component.history.temperature.shift();
                    component.history.pressure.shift();
                    component.history.flow.shift();
                }
            }

            updateFlowIndicators() {
                // Remove existing flow indicators
                const oldIndicators = document.querySelectorAll('.flow-indicator');
                oldIndicators.forEach(indicator => indicator.remove());

                // Add new flow indicators for each connection
                this.connections.forEach(conn => {
                    const fromComp = this.components.get(conn.from);
                    const flow = fromComp.flow;

                    if (flow > 0) {
                        const indicator = document.createElement('div');
                        indicator.className = 'flow-indicator';
                        indicator.style.left = (fromComp.x + 30) + 'px';
                        indicator.style.top = (fromComp.y + 30) + 'px';
                        document.getElementById('processDiagram').appendChild(indicator);
                    }
                });
            }

            triggerAlert(message) {
                const alerts = document.getElementById('alerts');
                const alert = document.createElement('div');
                alert.className = 'alert-item alert-warning';
                alert.innerHTML = `
                    <div>${message}</div>
                    <div>${new Date().toLocaleTimeString()}</div>
                `;
                alerts.prepend(alert);

                // Remove old alerts
                if (alerts.children.length > 5) {
                    alerts.removeChild(alerts.lastChild);
                }
            }

            toggleComponent() {
                if (this.selectedComponent) {
                    const component = this.components.get(this.selectedComponent);
                    component.efficiency = component.efficiency < 50 ? 100 : 0;
                    this.updateComponentDetails(component);
                }
            }

            optimizeComponent() {
                if (this.selectedComponent) {
                    const component = this.components.get(this.selectedComponent);
                    component.efficiency = 100;
                    component.temperature = 25;
                    component.pressure = 100;
                    component.flow = 50;
                    this.updateComponentDetails(component);
                }
            }

            setSpeed(speed) {
                this.speed = speed;
            }
        }

        // Initialize SCADA simulator
        const scadaSim = new ScadaSimulator();

        // Setup speed control
        document.getElementById('scadaSpeed').addEventListener('change', (e) => {
            scadaSim.setSpeed(parseFloat(e.target.value));
        });

        function toggleComponent() {
            scadaSim.toggleComponent();
        }

        function optimizeComponent() {
            scadaSim.optimizeComponent();
        }
    </script>
    ${FOOTER}
</body>
</html>
)rawliteral";

const char* DISASTER_HTML = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32MESH - Disaster Management</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
        /* Begin COMMON_STYLES */
        :root {
            --primary-color: #0077ff;
            --background-light: #f4f4f4;
            --text-light: #333;
            --card-bg: #ffffff;
            --border-color: #dee2e6;
        }
        :root[data-theme='dark'] {
            --primary-color: #1a8fff;
            --background-light: #1a1a1a;
            --text-light: #ffffff;
            --card-bg: #2d2d2d;
            --border-color: #404040;
        }
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 20px;
            background: var(--background-light);
            color: var(--text-light);
            transition: background-color 0.3s, color 0.3s;
        }
        .nav-bar {
            background: var(--primary-color);
            padding: 15px;
            margin-bottom: 20px;
            border-radius: 10px;
            display: flex;
            gap: 15px;
            align-items: center;
            justify-content: space-between;
        }
        .nav-links {
            display: flex;
            gap: 15px;
        }
        .nav-right {
            display: flex;
            align-items: center;
            gap: 15px;
        }
        .nav-link {
            color: white;
            text-decoration: none;
            padding: 8px 16px;
            border-radius: 5px;
            transition: background 0.3s;
        }
        .nav-link:hover {
            background: rgba(255, 255, 255, 0.2);
        }
        .nav-link.active {
            background: rgba(255, 255, 255, 0.3);
        }
        .settings-menu {
            position: relative;
            display: inline-block;
        }
        .settings-btn {
            background: none;
            border: none;
            color: white;
            font-size: 24px;
            cursor: pointer;
            padding: 8px;
            border-radius: 5px;
            transition: background 0.3s;
        }
        .settings-btn:hover {
            background: rgba(255, 255, 255, 0.2);
        }
        .settings-dropdown {
            position: absolute;
            right: 0;
            top: 100%;
            background: var(--card-bg);
            border: 1px solid var(--border-color);
            border-radius: 5px;
            padding: 10px;
            min-width: 200px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
            display: none;
            z-index: 1000;
        }
        .settings-dropdown.show {
            display: block;
        }
        .settings-item {
            padding: 8px 12px;
            display: flex;
            align-items: center;
            justify-content: space-between;
            border-radius: 5px;
            cursor: pointer;
            color: var(--text-light);
        }
        .settings-item:hover {
            background: var(--background-light);
        }
        .settings-divider {
            height: 1px;
            background: var(--border-color);
            margin: 8px 0;
        }
        .theme-switch {
            position: relative;
            display: inline-block;
            width: 50px;
            height: 24px;
        }
        .theme-switch input {
            opacity: 0;
            width: 0;
            height: 0;
        }
        .slider {
            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background-color: #ccc;
            transition: .4s;
            border-radius: 24px;
        }
        .slider:before {
            position: absolute;
            content: "";
            height: 16px;
            width: 16px;
            left: 4px;
            bottom: 4px;
            background-color: white;
            transition: .4s;
            border-radius: 50%;
        }
        input:checked + .slider {
            background-color: var(--primary-color);
        }
        input:checked + .slider:before {
            transform: translateX(26px);
        }
        .footer {
            margin-top: 40px;
            padding: 20px;
            background: var(--card-bg);
            border-top: 1px solid var(--border-color);
            text-align: center;
            font-size: 0.9em;
            color: var(--text-light);
        }
        .footer-content {
            max-width: 1200px;
            margin: 0 auto;
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 20px;
            padding: 20px 0;
        }
        .footer-section {
            text-align: left;
        }
        .footer-section h3 {
            color: var(--primary-color);
            margin-bottom: 15px;
        }
        .footer-section ul {
            list-style: none;
            padding: 0;
            margin: 0;
        }
        .footer-section ul li {
            margin-bottom: 8px;
        }
        .footer-section a {
            color: var(--text-light);
            text-decoration: none;
            transition: color 0.3s;
        }
        .footer-section a:hover {
            color: var(--primary-color);
        }
        .footer-bottom {
            margin-top: 20px;
            padding-top: 20px;
            border-top: 1px solid var(--border-color);
            font-size: 0.8em;
        }
        .sensor-group {
            background: var(--background-light);
            padding: 10px;
            margin: 5px 0;
            border-radius: 5px;
        }
        .sensor-group h4 {
            margin: 0 0 5px 0;
            color: var(--primary-color);
        }
        .sensor-group p {
            margin: 3px 0;
        }
        .sensor-warning {
            color: #ffc107;
        }
        .sensor-critical {
            color: #dc3545;
        }
        .day-night-indicator {
            display: inline-block;
            width: 24px;
            height: 24px;
            border-radius: 50%;
            margin-left: 8px;
            vertical-align: middle;
        }
        .day-night-indicator.day {
            background: #ffd700;
            box-shadow: 0 0 10px rgba(255, 215, 0, 0.5);
        }
        .day-night-indicator.night {
            background: #1a237e;
            box-shadow: 0 0 10px rgba(26, 35, 126, 0.5);
        }
        .day-night-indicator.transition {
            background: linear-gradient(135deg, #ffd700 50%, #1a237e 50%);
        }
        .stat-item {
            text-align: center;
            padding: 15px;
            background: #f8f9fa;
            border-radius: 8px;
        }
        .stat-value {
            font-size: 24px;
            font-weight: bold;
            color: var(--primary-color);
        }
        .stat-label {
            font-size: 14px;
            color: #666;
            margin-top: 5px;
        }
        .node {
            position: absolute;
            width: 40px;
            height: 40px;
            border-radius: 50%;
            background: var(--primary-color);
            transform: translate(-50%, -50%);
            display: flex;
            align-items: center;
            justify-content: center;
            color: white;
            font-size: 12px;
            cursor: pointer;
            transition: all 0.3s ease;
        }
        .node:hover {
            transform: translate(-50%, -50%) scale(1.1);
            box-shadow: 0 0 10px rgba(0,119,255,0.5);
        }
        .node.root {
            background: #28a745;
            width: 50px;
            height: 50px;
            font-size: 14px;
        }
        .connection {
            position: absolute;
            height: 2px;
            background: rgba(0,119,255,0.3);
            transform-origin: left center;
            pointer-events: none;
        }
        .node-info {
            position: absolute;
            background: var(--card-bg);
            padding: 10px;
            border-radius: 5px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
            display: none;
            z-index: 10;
        }
        .node-info.show {
            display: block;
        }
        /* End COMMON_STYLES */
        .disaster-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(350px, 1fr));
            gap: 20px;
            margin-top: 20px;
        }
        .disaster-panel {
            background: var(--card-bg);
            border-radius: 10px;
            padding: 20px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
        }
        .alert-list {
            max-height: 300px;
            overflow-y: auto;
        }
        .alert-item {
            padding: 15px;
            margin-bottom: 10px;
            border-radius: 5px;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        .alert-critical {
            background: #dc3545;
            color: white;
        }
        .alert-warning {
            background: #ffc107;
            color: black;
        }
        .alert-info {
            background: #0dcaf0;
            color: white;
        }
        .scenario-button {
            width: 100%;
            padding: 15px;
            margin-bottom: 10px;
            border: none;
            border-radius: 5px;
            background: var(--primary-color);
            color: white;
            cursor: pointer;
            font-size: 16px;
        }
        .scenario-button:hover {
            opacity: 0.9;
        }
        .map-container {
            height: 400px;
            background: #f8f9fa;
            border-radius: 5px;
            position: relative;
        }
        .node-marker {
            position: absolute;
            width: 20px;
            height: 20px;
            border-radius: 50%;
            transform: translate(-50%, -50%);
            cursor: pointer;
        }
        .node-marker.alert {
            animation: pulse 1.5s infinite;
        }
        @keyframes pulse {
            0% { transform: translate(-50%, -50%) scale(1); opacity: 1; }
            50% { transform: translate(-50%, -50%) scale(1.5); opacity: 0.5; }
            100% { transform: translate(-50%, -50%) scale(1); opacity: 1; }
        }
        .simulation-controls {
            position: fixed;
            right: 20px;
            top: 100px;
            background: var(--card-bg);
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0 2px 8px rgba(0,0,0,0.2);
            z-index: 1000;
            min-width: 250px;
        }
        .simulation-slider {
            width: 100%;
            margin: 10px 0;
        }
        .parameter-group {
            margin-bottom: 15px;
        }
        .parameter-label {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 5px;
        }
        .parameter-value {
            font-weight: bold;
            color: var(--primary-color);
        }
        .node-details {
            position: fixed;
            left: 20px;
            bottom: 20px;
            background: var(--card-bg);
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0 2px 8px rgba(0,0,0,0.2);
            display: none;
            z-index: 1000;
        }
        .sensor-reading {
            display: flex;
            justify-content: space-between;
            margin: 5px 0;
        }
        .timeline {
            position: fixed;
            bottom: 0;
            left: 0;
            right: 0;
            height: 60px;
            background: rgba(255,255,255,0.9);
            padding: 10px;
            display: flex;
            align-items: center;
            justify-content: space-between;
            z-index: 900;
        }
        .timeline-slider {
            flex: 1;
            margin: 0 20px;
        }
        .animation-speed {
            margin-left: 20px;
        }
        .event-marker {
            position: absolute;
            width: 10px;
            height: 10px;
            background: red;
            border-radius: 50%;
            transform: translate(-50%, -50%);
            cursor: pointer;
        }
        .wave-animation {
            position: absolute;
            border: 2px solid;
            border-radius: 50%;
            animation: wave 2s infinite;
            pointer-events: none;
        }
        @keyframes wave {
            0% { transform: scale(0); opacity: 1; }
            100% { transform: scale(1); opacity: 0; }
        }
        @keyframes rain-fall {
            0% { opacity: 1; top: -10%; }
            100% { opacity: 0; top: 110%; }
        }
        .rain-drop {
            position: absolute;
            width: 2px;
            height: 15px;
            background: #2196f3;
            opacity: 0.5;
            border-radius: 1px;
        }
        .wind-effect {
            position: absolute;
            width: 100%;
            height: 100%;
            background: repeating-linear-gradient(90deg, rgba(33,150,243,0.1) 0 10px, transparent 10px 20px);
            pointer-events: none;
            animation: wind-move 1s linear infinite;
        }
        @keyframes wind-move {
            0% { background-position-x: 0; }
            100% { background-position-x: 40px; }
        }
        @keyframes earthquake {
            0% { transform: translate(0, 0); }
            20% { transform: translate(-2px, 2px); }
            40% { transform: translate(-2px, -2px); }
            60% { transform: translate(2px, 2px); }
            80% { transform: translate(2px, -2px); }
            100% { transform: translate(0, 0); }
        }
    </style>
</head>
<body>
    <div class="nav-bar">
        <div class="nav-links">
            <a href="/" class="nav-link" id="nav-dashboard">Dashboard</a>
            <a href="/chatlog" class="nav-link" id="nav-chatlog">Chat Log</a>
            <a href="/nodestack" class="nav-link" id="nav-nodestack">Node Stack</a>
            <a href="/scada" class="nav-link" id="nav-scada">SCADA</a>
            <a href="/disaster" class="nav-link" id="nav-disaster">Disaster Management</a>
        </div>
        <div class="nav-right">
            <div class="settings-menu">
                <button class="settings-btn">&#9881;</button>
                <div class="settings-dropdown">
                    <div class="settings-item">
                        <span>Dark Mode</span>
                        <label class="theme-switch">
                            <input type="checkbox" id="theme-toggle">
                            <span class="slider"></span>
                        </label>
                    </div>
                    <div class="settings-divider"></div>
                    <div class="settings-item">
                        <span>Refresh Rate</span>
                        <select id="refresh-rate">
                            <option value="1000">1s</option>
                            <option value="3000" selected>3s</option>
                            <option value="5000">5s</option>
                        </select>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <h2 class="page-title">Disaster Management System</h2>
    <div class="disaster-grid">
        <div class="disaster-panel">
            <h2>Active Alerts</h2>
            <div class="alert-list" id="alert-list">
                <!-- Will be populated dynamically -->
            </div>
        </div>
        <div class="disaster-panel">
            <h2>Network Map</h2>
            <div class="map-container" id="network-map">
                <!-- Will be populated dynamically -->
            </div>
        </div>
        <div class="disaster-panel">
            <h2>Disaster Scenarios</h2>
            <button class="scenario-button" onclick="runScenario('flood')">
                Simulate Flood Event
            </button>
            <button class="scenario-button" onclick="runScenario('fire')">
                Simulate Fire Event
            </button>
            <button class="scenario-button" onclick="runScenario('earthquake')">
                Simulate Earthquake Event
            </button>
            <button class="scenario-button" onclick="runScenario('power_outage')">
                Simulate Power Outage
            </button>
        </div>
    </div>
    <div class="simulation-controls">
        <h3>Simulation Parameters</h3>
        <div class="parameter-group">
            <div class="parameter-label">
                <span>Wind Speed</span>
                <span class="parameter-value" id="windSpeed">0 km/h</span>
            </div>
            <input type="range" class="simulation-slider" id="windSpeedControl" min="0" max="200" value="0">
        </div>
        <div class="parameter-group">
            <div class="parameter-label">
                <span>Temperature</span>
                <span class="parameter-value" id="temperature">20°C</span>
            </div>
            <input type="range" class="simulation-slider" id="temperatureControl" min="-20" max="50" value="20">
        </div>
        <div class="parameter-group">
            <div class="parameter-label">
                <span>Rainfall</span>
                <span class="parameter-value" id="rainfall">0 mm/h</span>
            </div>
            <input type="range" class="simulation-slider" id="rainfallControl" min="0" max="100" value="0">
        </div>
        <div class="parameter-group">
            <div class="parameter-label">
                <span>Ground Movement</span>
                <span class="parameter-value" id="groundMovement">0 mg</span>
            </div>
            <input type="range" class="simulation-slider" id="groundMovementControl" min="0" max="100" value="0">
        </div>
        <button class="sim-button" onclick="generateRandomEvent()">Generate Random Event</button>
        <button class="sim-button" onclick="resetSimulation()">Reset Simulation</button>
    </div>
    
    <div class="node-details" id="nodeDetails">
        <h3>Node Details</h3>
        <div id="nodeReadings"></div>
        <div id="nodeActions">
            <button class="sim-button" onclick="evacuateZone()">Evacuate Zone</button>
            <button class="sim-button" onclick="sendAlert()">Send Alert</button>
        </div>
    </div>

    <div class="timeline">
        <span>Timeline</span>
        <input type="range" class="timeline-slider" id="timelineControl" min="0" max="100" value="0">
        <div class="animation-speed">
            <label>Speed: </label>
            <select id="simulationSpeed">
                <option value="0.5">0.5x</option>
                <option value="1" selected>1x</option>
                <option value="2">2x</option>
                <option value="5">5x</option>
            </select>
        </div>
    </div>
    ${FOOTER}
    <script>
        class DisasterSimulator {
            constructor() {
                this.parameters = {
                    windSpeed: 0,
                    temperature: 20,
                    rainfall: 0,
                    groundMovement: 0
                };
                this.events = [];
                this.time = 0;
                this.speed = 1;
                this.isRunning = false;
                this.selectedNode = null;
                this.map = document.getElementById('network-map');
                this.alertList = document.getElementById('alert-list');
                this.timelineControl = document.getElementById('timelineControl');
                this.init = false;
                this.setupEventListeners();
                this.startSimulation();
            }

            setupEventListeners() {
                ['windSpeed', 'temperature', 'rainfall', 'groundMovement'].forEach(param => {
                    document.getElementById(param + 'Control').addEventListener('input', (e) => {
                        this.parameters[param] = parseFloat(e.target.value);
                        this.updateDisplay();
                        this.evaluateConditions();
                    });
                });

                document.getElementById('simulationSpeed').addEventListener('change', (e) => {
                    this.speed = parseFloat(e.target.value);
                });

                this.timelineControl.addEventListener('input', (e) => {
                    this.time = parseFloat(e.target.value);
                    this.updateTimeline();
                });
            }

            startSimulation() {
                if (this.init) return;
                this.isRunning = true;
                this.init = true;
                this.animate();
            }

            animate() {
                if (!this.isRunning) return;
                this.time += 0.1 * this.speed;
                if (this.time > 100) this.time = 0;
                this.timelineControl.value = this.time;
                this.updateTimeline();
                this.updateEnvironmentalEffects();
                requestAnimationFrame(() => this.animate());
            }

            updateDisplay() {
                document.getElementById('windSpeed').textContent = this.parameters.windSpeed + ' km/h';
                document.getElementById('temperature').textContent = this.parameters.temperature + '°C';
                document.getElementById('rainfall').textContent = this.parameters.rainfall + ' mm/h';
                document.getElementById('groundMovement').textContent = this.parameters.groundMovement + ' mg';
            }

            evaluateConditions() {
                if (this.parameters.windSpeed > 150) {
                    this.triggerEvent('Hurricane conditions detected');
                }
                if (this.parameters.temperature > 45) {
                    this.triggerEvent('Extreme heat warning');
                }
                if (this.parameters.rainfall > 80) {
                    this.triggerEvent('Flood warning');
                }
                if (this.parameters.groundMovement > 70) {
                    this.triggerEvent('Earthquake warning');
                }
            }

            triggerEvent(message) {
                const event = {
                    time: this.time,
                    message,
                    position: {
                        x: Math.random() * 100,
                        y: Math.random() * 100
                    }
                };
                this.events.push(event);
                this.createEventMarker(event);
                this.showAlert(message);
            }

            createEventMarker(event) {
                const marker = document.createElement('div');
                marker.className = 'event-marker';
                marker.style.left = event.position.x + '%';
                marker.style.top = event.position.y + '%';
                marker.title = event.message;
                const wave = document.createElement('div');
                wave.className = 'wave-animation';
                wave.style.borderColor = this.getEventColor(event.message);
                marker.appendChild(wave);
                this.map.appendChild(marker);
            }

            getEventColor(message) {
                if (message.includes('Hurricane')) return '#ff4444';
                if (message.includes('heat')) return '#ff8844';
                if (message.includes('Flood')) return '#4444ff';
                if (message.includes('Earthquake')) return '#44ff44';
                return '#ffffff';
            }

            showAlert(message) {
                const alertDiv = document.createElement('div');
                alertDiv.className = 'alert-item alert-critical';
                alertDiv.innerHTML = `
                    <div>
                        <strong>Emergency Alert</strong><br>
                        ${message}
                    </div>
                    <div>
                        ${new Date().toLocaleTimeString()}
                    </div>
                `;
                this.alertList.prepend(alertDiv);
                // Remove old alerts
                while (this.alertList.children.length > 5) {
                    this.alertList.removeChild(this.alertList.lastChild);
                }
            }

            generateRandomEvent() {
                const events = [
                    () => { this.parameters.windSpeed = 160 + Math.random() * 40; },
                    () => { this.parameters.temperature = 46 + Math.random() * 10; },
                    () => { this.parameters.rainfall = 85 + Math.random() * 15; },
                    () => { this.parameters.groundMovement = 75 + Math.random() * 25; }
                ];
                events[Math.floor(Math.random() * events.length)]();
                this.updateControls();
                this.updateDisplay();
                this.evaluateConditions();
            }

            updateControls() {
                for (const [param, value] of Object.entries(this.parameters)) {
                    document.getElementById(param + 'Control').value = value;
                }
            }

            resetSimulation() {
                this.parameters = {
                    windSpeed: 0,
                    temperature: 20,
                    rainfall: 0,
                    groundMovement: 0
                };
                this.updateControls();
                this.updateDisplay();
                // Clear event markers
                const markers = this.map.querySelectorAll('.event-marker');
                markers.forEach(marker => marker.remove());
                // Clear alerts
                this.alertList.innerHTML = '';
                this.events = [];
                this.time = 0;
                this.timelineControl.value = 0;
            }

            updateTimeline() {
                // Update environmental conditions based on timeline
                this.events.forEach(event => {
                    if (Math.abs(event.time - this.time) < 1) {
                        this.showAlert(event.message);
                    }
                });
            }

            updateEnvironmentalEffects() {
                // Add visual effects based on current conditions
                // Clear existing effects
                const effects = this.map.querySelectorAll('.environmental-effect');
                effects.forEach(effect => effect.remove());
                this.map.style.animation = '';
                if (this.parameters.rainfall > 50) {
                    this.addRainEffect(this.map);
                }
                if (this.parameters.windSpeed > 100) {
                    this.addWindEffect(this.map);
                }
                if (this.parameters.groundMovement > 50) {
                    this.addEarthquakeEffect(this.map);
                }
            }

            addRainEffect(container) {
                for (let i = 0; i < 50; i++) {
                    const drop = document.createElement('div');
                    drop.className = 'environmental-effect rain-drop';
                    drop.style.left = Math.random() * 100 + '%';
                    drop.style.top = Math.random() * 100 + '%';
                    drop.style.animation = `rain-fall ${0.5 + Math.random()}s linear infinite`;
                    container.appendChild(drop);
                }
            }

            addWindEffect(container) {
                const wind = document.createElement('div');
                wind.className = 'environmental-effect wind-effect';
                container.appendChild(wind);
            }

            addEarthquakeEffect(container) {
                container.style.animation = 'earthquake 0.5s infinite';
                setTimeout(() => {
                    container.style.animation = '';
                }, 1000);
            }
        }

        // Initialize simulator
        let simulator;
        window.addEventListener('DOMContentLoaded', () => {
            simulator = new DisasterSimulator();
        });

        function generateRandomEvent() {
            simulator.generateRandomEvent();
        }

        function resetSimulation() {
            simulator.resetSimulation();
        }

        function evacuateZone() {
            if (simulator.selectedNode) {
                simulator.triggerEvent(`Evacuation ordered for Zone ${simulator.selectedNode}`);
            }
        }

        function sendAlert() {
            if (simulator.selectedNode) {
                simulator.triggerEvent(`Emergency alert sent to Zone ${simulator.selectedNode}`);
            }
        }
    </script>
</body>
</html>
)rawliteral";

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "painlessMesh.h"
#include <SPIFFS.h>
#include <CircularBuffer.hpp>
#include <ArduinoJson.h>
#include <map>
#include <vector>

// Forward declarations for global callback functions
void onMeshReceived(uint32_t from, String &msg);
void onMeshNewConnection(uint32_t nodeId);
void onMeshChangedConnections();
void onMeshNodeTimeAdjusted(int32_t offset);
void onMeshNodeDelayReceived(uint32_t nodeId, int32_t delay);

// Forward declaration of RootNode class
class RootNode;
extern RootNode* rootNode;  // Declaration of the extern variable

// Network Configuration
#define MESH_PREFIX     "ESP32MeshAP"
#define MESH_PASSWORD   "12345678"
#define MESH_PORT       5555
#define WIFI_CHANNEL    6
#define AP_SSID         "ESP32MeshAP"
#define AP_PASS         "12345678"
#define MAX_CONN        4
#define HOSTNAME        "ESP32_ROOT"
#define NODE_TIMEOUT    6000000  // 6000 seconds

#define LED             2
#define LOG_SIZE        100
#define MAX_MESSAGE_LENGTH 256  // Maximum allowed message length

// Global scheduler
Scheduler userScheduler;

// Forward declarations of structures we'll need
struct ChatMessage {
    uint32_t nodeId;
    String message;
    unsigned long timestamp;
    bool isSystem;
};

struct NodeConnection {
    uint32_t from;
    uint32_t to;
    int rssi;
};

struct SCADAData {
    float systemHealth;
    float powerConsumption;
    float networkLoad;
    std::map<String, float> sensorReadings;
};

struct DisasterAlert {
    uint32_t nodeId;
    String type;
    String severity;
    String message;
    unsigned long timestamp;
};

struct ScenarioState {
    bool isActive;
    String type;
    unsigned long startTime;
    std::vector<std::pair<uint32_t, String>> nodeStates;
    String scenarioName;
};

struct NodeInfo {
    unsigned long lastUpdate;
    std::map<String, String> sensorData;
    String nodeName;
};

// Complete RootNode class definition
class RootNode {
private:
    AsyncWebServer* server;
    painlessMesh mesh;
    CircularBuffer<ChatMessage, LOG_SIZE> chatMessages;
    CircularBuffer<NodeConnection, LOG_SIZE> connections;
    CircularBuffer<DisasterAlert, LOG_SIZE> alerts;
    std::map<uint32_t, NodeInfo> nodeDataCache;
    SCADAData scadaData;
    ScenarioState currentScenario;
    Task taskUpdateTopology;
    Task taskUpdateStats;
    IPAddress myAPIP;
    bool meshInitialized = false;
    bool apInitialized = false;
    unsigned long lastReconnectAttempt = 0;
    const unsigned long RECONNECT_INTERVAL = 5000; // 5 seconds

public:
    RootNode();
    void init();
    void update();
    void receivedCallback(uint32_t from, String &msg);
    void newConnectionCallback(uint32_t nodeId);
    void changedConnectionCallback();
    void nodeTimeAdjustedCallback(int32_t offset);
    void nodeDelayReceivedCallback(uint32_t nodeId, int32_t delay);

private:
    void initServer();
    void initMesh();
    void initTasks();
    void updateTopology();
    void updateStats();
    void handleMessage(uint32_t from, String& type, JsonDocument& doc);
    float calculateSystemHealth();
    float calculatePowerConsumption();
    float calculateNetworkLoad();
    void startDisasterScenario(const String& type);
    void stopDisasterScenario();
    void sendCommand(uint32_t nodeId, const String& command, const JsonDocument& params);
    void updateSensorThresholds(const JsonDocument& thresholds);
    void checkAndRestartIfNeeded();
};

RootNode::RootNode() : 
    server(new AsyncWebServer(80)),
    taskUpdateTopology(TASK_SECOND * 5, TASK_FOREVER, [this](){ this->updateTopology(); }),
    taskUpdateStats(TASK_SECOND * 2, TASK_FOREVER, [this](){ this->updateStats(); }) {
    
    // Initialize Serial first with higher baud rate
    Serial.begin(115200);
    while (!Serial) delay(100);  // Wait for serial to be ready
    Serial.println("\nInitializing Root Node...");
    
    // Setup LED pin
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);  // Turn on LED during initialization

    // --- WiFi AP Setup: Always use AP mode for dashboard, force 192.168.4.1 ---
    WiFi.mode(WIFI_AP); // Only AP mode for dashboard access
    WiFi.persistent(false);
    WiFi.setAutoReconnect(true);

    IPAddress apIP(192,168,4,1);
    IPAddress gateway(192,168,4,1);
    IPAddress subnet(255,255,255,0);
    WiFi.softAPConfig(apIP, gateway, subnet);

    Serial.println("Setting up Access Point at 192.168.4.1 ...");
    int retries = 3;
    while (retries > 0) {
        if (WiFi.softAP(AP_SSID, AP_PASS, WIFI_CHANNEL, 0, MAX_CONN)) {
            break;
        }
        Serial.printf("AP start failed, retrying... (%d attempts left)\n", --retries);
        delay(1000);
    }
    WiFi.softAPsetHostname(HOSTNAME);
    myAPIP = WiFi.softAPIP();
    Serial.printf("AP started successfully\nSSID: %s\nIP address: %s\n", AP_SSID, myAPIP.toString().c_str());
    digitalWrite(LED, LOW);  // Turn off LED after initialization
}

void RootNode::init() {
    Serial.println("\n=== Starting Root Node Initialization ===");
    
    // Initialize SPIFFS first
    if(!SPIFFS.begin(true)){
        Serial.println("ERROR: SPIFFS initialization failed!");
        return;
    }
    Serial.println("SPIFFS initialized successfully");

    // Initialize web server first to ensure UI availability
    Serial.println("Initializing web server...");
    initServer();
    Serial.println("Web server initialized successfully");
    
    // Initialize mesh network (non-blocking)
    Serial.println("Attempting mesh network initialization...");
    initMesh();
    
    // Initialize tasks
    Serial.println("Initializing tasks...");
    initTasks();
    
    Serial.println("=== Root Node initialization complete ===");
    Serial.printf("Web interface available at: http://%s\n", WiFi.softAPIP().toString().c_str());
    
    // Flash LED to indicate successful initialization
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
}

void RootNode::initMesh() {
    Serial.println("Initializing mesh network...");
    
    // Set debug message types for more visibility
    mesh.setDebugMsgTypes(ERROR | STARTUP | CONNECTION | MESH_STATUS);
    
    try {
        // Mesh can use AP+STA mode for dynamic mesh connections
        mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT, WIFI_AP_STA, WIFI_CHANNEL);
        
        // Configure this node as root
        mesh.setRoot(true);
        mesh.setContainsRoot(true);
        
        // Store AP IP and verify it
        myAPIP = WiFi.softAPIP();
        if (myAPIP != WiFi.softAPIP()) {
            Serial.println("Warning: AP IP mismatch, updating stored IP...");
            myAPIP = WiFi.softAPIP();
        }
        
        // Set callbacks
        mesh.onReceive(&onMeshReceived);
        mesh.onNewConnection(&onMeshNewConnection);
        mesh.onChangedConnections(&onMeshChangedConnections);
        mesh.onNodeTimeAdjusted(&onMeshNodeTimeAdjusted);
        mesh.onNodeDelayReceived(&onMeshNodeDelayReceived);
        
        Serial.println("\n=== Mesh Network Configuration ===");
        Serial.printf("SSID: %s\n", MESH_PREFIX);
        Serial.printf("Password: %s\n", MESH_PASSWORD);
        Serial.printf("Channel: %d\n", WIFI_CHANNEL);
        Serial.printf("AP IP: %s\n", myAPIP.toString().c_str());
        Serial.printf("Mesh Port: %d\n", MESH_PORT);
        Serial.println("================================\n");
        
        // Flash LED to indicate successful mesh initialization
        digitalWrite(LED, HIGH);
        delay(100);
        digitalWrite(LED, LOW);
        
        meshInitialized = true;
        Serial.println("Mesh network initialized successfully");
    } catch (...) {
        Serial.println("Mesh initialization failed - continuing with AP mode only");
        meshInitialized = false;
    }
}

void RootNode::update() {
    static unsigned long lastCheck = 0;
    const unsigned long CHECK_INTERVAL = 30000; // 30 seconds
    
    // Update mesh if it's initialized
    if (meshInitialized) {
        mesh.update();
    }
    
    // Periodic connectivity check
    unsigned long now = millis();
    if (now - lastCheck >= CHECK_INTERVAL) {
        lastCheck = now;
        
        // Update stored AP IP if it changed
        IPAddress currentIP = WiFi.softAPIP();
        if (currentIP != myAPIP) {
            myAPIP = currentIP;
            Serial.printf("AP IP updated to: %s\n", myAPIP.toString().c_str());
        }
        
        // Print status
        if (meshInitialized) {
            auto nodes = mesh.getNodeList();
            Serial.printf("Connected mesh nodes: %d\n", nodes.size());
        }
        Serial.printf("AP Status: %s (IP: %s)\n", 
                     WiFi.softAPgetStationNum() > 0 ? "Connected" : "Waiting for connections",
                     WiFi.softAPIP().toString().c_str());
        Serial.printf("Free heap: %d\n", ESP.getFreeHeap());
    }

    // Run tasks
    userScheduler.execute();
}

void RootNode::receivedCallback(uint32_t from, String &msg) {
    // Flash LED to indicate message received
    digitalWrite(LED, HIGH);
    delay(50);
    digitalWrite(LED, LOW);

    // Parse message
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, msg);
    
    if (error) {
        Serial.printf("Message parsing failed: %s\n", error.c_str());
        return;
    }
    
    // Process message
    if (doc.containsKey("type")) {
        String type = doc["type"].as<String>();
        handleMessage(from, type, doc);
    }
}

void RootNode::newConnectionCallback(uint32_t nodeId) {
    Serial.printf("New node connected: %u\n", nodeId);
    
    // Update topology immediately when a new node connects
    updateTopology();
    
    // Send welcome message
    DynamicJsonDocument doc(256);
    doc["type"] = "system";
    doc["content"] = "Welcome to the network!";
    String msg;
    serializeJson(doc, msg);
    mesh.sendSingle(nodeId, msg);
}

void RootNode::changedConnectionCallback() {
    updateTopology();
}

void RootNode::nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Time adjusted by %d\n", offset);
}

void RootNode::nodeDelayReceivedCallback(uint32_t nodeId, int32_t delay) {
    Serial.printf("Delay to node %u is %d ms\n", nodeId, delay);
}

void RootNode::initServer() {
    // Set up CORS and content type handlers
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Content-Type");

    // Serve static files from SPIFFS
    server->serveStatic("/", SPIFFS, "/");

    // Root endpoint serving the embedded dashboard
    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        String html = DASHBOARD_HTML;
        html.replace("${FOOTER}", FOOTER);
        request->send(200, "text/html", html);
    });

    // Add endpoints for other HTML pages
    server->on("/chatlog", HTTP_GET, [](AsyncWebServerRequest *request) {
        String html = CHATLOG_HTML;
        html.replace("${FOOTER}", FOOTER);
        request->send(200, "text/html", html);
    });
    server->on("/nodestack", HTTP_GET, [](AsyncWebServerRequest *request) {
        String html = NODESTACK_HTML;
        html.replace("${FOOTER}", FOOTER);
        request->send(200, "text/html", html);
    });
    server->on("/scada", HTTP_GET, [](AsyncWebServerRequest *request) {
        String html = SCADA_HTML;
        html.replace("${FOOTER}", FOOTER);
        request->send(200, "text/html", html);
    });
    server->on("/disaster", HTTP_GET, [](AsyncWebServerRequest *request) {
        String html = DISASTER_HTML;
        html.replace("${FOOTER}", FOOTER);
        request->send(200, "text/html", html);
    });

    // Add a handler for OPTIONS requests (CORS preflight)
    server->on("/*", HTTP_OPTIONS, [](AsyncWebServerRequest *request) {
        request->send(200);
    });

    // Topology endpoint with graceful handling of missing mesh
    server->on("/topology", HTTP_GET, [this](AsyncWebServerRequest *request) {
        DynamicJsonDocument doc(4096);
        JsonArray nodes = doc.createNestedArray("nodes");
        JsonArray links = doc.createNestedArray("links");

        // Always add root node
        JsonObject rootNodeObj = nodes.createNestedObject();
        rootNodeObj["id"] = meshInitialized ? mesh.getNodeId() : 0;
        rootNodeObj["type"] = "root";
        rootNodeObj["status"] = "online";

        // Add mesh nodes if mesh is initialized
        if (meshInitialized) {
            auto nodeList = mesh.getNodeList();
            for (auto nodeId : nodeList) {
                JsonObject node = nodes.createNestedObject();
                node["id"] = nodeId;
                node["type"] = "sensor";
                node["status"] = "online";

                JsonObject link = links.createNestedObject();
                link["source"] = mesh.getNodeId();
                link["target"] = nodeId;
                link["rssi"] = -50;  // Default RSSI value
            }
        }

        String response;
        serializeJson(doc, response);
        request->send(200, "application/json", response);
    });

    // Stats endpoint with default values for missing mesh
    server->on("/stats", HTTP_GET, [this](AsyncWebServerRequest *request) {
        DynamicJsonDocument doc(1024);
        doc["uptime"] = millis() / 1000;
        doc["nodes"] = meshInitialized ? mesh.getNodeList().size() + 1 : 1;
        doc["messages"] = chatMessages.size();
        doc["networkHealth"] = calculateSystemHealth();
        doc["networkLoad"] = calculateNetworkLoad() * 100;
        doc["webClients"] = WiFi.softAPgetStationNum();

        String response;
        serializeJson(doc, response);
        request->send(200, "application/json", response);
    });

    // Messages endpoint
    server->on("/messages", HTTP_GET, [this](AsyncWebServerRequest *request) {
        DynamicJsonDocument doc(4096);
        JsonArray messages = doc.createNestedArray("messages");
        
        for (size_t i = 0; i < chatMessages.size(); i++) {
            JsonObject msgObj = messages.createNestedObject();
            msgObj["nodeId"] = chatMessages[i].nodeId;
            msgObj["message"] = chatMessages[i].message;
            msgObj["timestamp"] = chatMessages[i].timestamp;
            msgObj["isSystem"] = chatMessages[i].isSystem;
        }

        String response;
        serializeJson(doc, response);
        request->send(200, "application/json", response);
    });

    // Node data endpoint with graceful handling of missing nodes
    server->on("/node-data", HTTP_GET, [this](AsyncWebServerRequest *request) {
        DynamicJsonDocument doc(4096);
        JsonArray nodes = doc.createNestedArray("nodes");

        // Add root node data
        uint32_t rootId = meshInitialized ? mesh.getNodeId() : 0;
        JsonObject rootData = nodes.createNestedObject();
        rootData["id"] = rootId;
        rootData["type"] = "root";
        rootData["lastUpdate"] = millis();
        rootData["isOnline"] = true;
        rootData["signalStrength"] = WiFi.RSSI();

        // Add other nodes if mesh is initialized
        if (meshInitialized) {
            for (const auto& pair : nodeDataCache) {
                // Do not include the root node in the non-root list
                if (pair.first == rootId) continue;
                if (millis() - pair.second.lastUpdate <= NODE_TIMEOUT) {
                    JsonObject node = nodes.createNestedObject();
                    node["id"] = pair.first;
                    node["type"] = "node";
                    node["lastSeen"] = pair.second.lastUpdate;
                    node["isOnline"] = true;
                    node["signalStrength"] = -50; // Placeholder, update if you have real RSSI
                    if (!pair.second.nodeName.isEmpty()) {
                        node["nodeName"] = pair.second.nodeName;
                    }

                    // Add sensorData as an object, parsing JSON strings if needed
                    JsonObject sensorData = node.createNestedObject("sensorData");
                    for (const auto& sensor : pair.second.sensorData) {
                        const String& val = sensor.second;
                        // Try to parse as JSON
                        DynamicJsonDocument tmpDoc(256);
                        DeserializationError err = deserializeJson(tmpDoc, val);
                        if (!err) {
                            // If parse succeeds, copy as object/array
                            sensorData[sensor.first] = tmpDoc.as<JsonVariant>();
                        } else {
                            // Try to convert to float, else send as string
                            char* endptr = nullptr;
                            double f = strtod(val.c_str(), &endptr);
                            if (endptr != val.c_str() && *endptr == '\0') {
                                sensorData[sensor.first] = f;
                            } else {
                                sensorData[sensor.first] = val;
                            }
                        }
                    }
                }
            }
        }

        String response;
        serializeJson(doc, response);
        request->send(200, "application/json", response);
    });

    // Send message endpoint
    server->on("/send-message", HTTP_POST, [this](AsyncWebServerRequest *request) {
        if (!request->hasParam("message", true)) {
            request->send(400, "text/plain", "Message parameter required");
            return;
        }

        String message = request->getParam("message", true)->value();
        bool isSystem = request->hasParam("isSystem", true) && 
                       request->getParam("isSystem", true)->value() == "true";

        ChatMessage chatMsg;
        chatMsg.nodeId = meshInitialized ? mesh.getNodeId() : 0;
        chatMsg.message = message;
        chatMsg.timestamp = millis();
        chatMsg.isSystem = isSystem;
        chatMessages.push(chatMsg);

        // Broadcast to mesh if available
        if (meshInitialized && message.length() > 0) {
            DynamicJsonDocument doc(512);
            doc["type"] = isSystem ? "system" : "message";
            doc["content"] = message;
            String msg;
            serializeJson(doc, msg);
            mesh.sendBroadcast(msg);
        }

        request->send(200, "text/plain", "Message sent");
    });

    server->begin();
    Serial.println("Web server started successfully");
    Serial.printf("Dashboard available at: http://%s/\n", WiFi.softAPIP().toString().c_str());
}

void RootNode::initTasks() {
    userScheduler.addTask(taskUpdateTopology);
    userScheduler.addTask(taskUpdateStats);
    taskUpdateTopology.enable();
    taskUpdateStats.enable();
}

void RootNode::updateTopology() {
    auto nodes = mesh.getNodeList();
    connections.clear();
    
    // Add connections from root to direct neighbors
    for (auto nodeId : nodes) {
        NodeConnection conn;
        conn.from = mesh.getNodeId();
        conn.to = nodeId;
        conn.rssi = -50;  // Default RSSI value since we can't get it directly
        connections.push(conn);
    }

    // Request topology updates from nodes
    DynamicJsonDocument doc(128);
    doc["type"] = "request_topology";
    String msg;
    serializeJson(doc, msg);
    mesh.sendBroadcast(msg);
}

void RootNode::updateStats() {
    // Update system metrics
    scadaData.systemHealth = calculateSystemHealth();
    scadaData.powerConsumption = calculatePowerConsumption();
    scadaData.networkLoad = calculateNetworkLoad();

    // Clean up stale node data
    unsigned long now = millis();
    for (auto it = nodeDataCache.begin(); it != nodeDataCache.end();) {
        if (now - it->second.lastUpdate > NODE_TIMEOUT) {
            it = nodeDataCache.erase(it);
        } else {
            ++it;
        }
    }
}

void RootNode::handleMessage(uint32_t from, String& type, JsonDocument& doc) {
    if (type == "sensor_data") {
        NodeInfo& nodeInfo = nodeDataCache[from];
        nodeInfo.lastUpdate = millis();
        if (doc.containsKey("nodeName")) {
    nodeInfo.nodeName = doc["nodeName"].as<String>();
}
        if (doc.containsKey("sensors")) {
            JsonObject sensors = doc["sensors"];
            for (JsonPair kv : sensors) {
                // If value is a primitive, store as string; if object/array, serialize as JSON
                if (kv.value().is<JsonObject>() || kv.value().is<JsonArray>()) {
                    String jsonStr;
                    serializeJson(kv.value(), jsonStr);
                    nodeInfo.sensorData[kv.key().c_str()] = jsonStr;
                } else if (kv.value().is<const char*>()) {
                    nodeInfo.sensorData[kv.key().c_str()] = String(kv.value().as<const char*>());
                } else {
                    nodeInfo.sensorData[kv.key().c_str()] = String(kv.value().as<String>());
                }
            }
        }
    }
    else if (type == "alert") {
        DisasterAlert alert;
        alert.nodeId = from;
        alert.type = doc["alertType"].as<String>();
        alert.severity = doc["severity"].as<String>();
        alert.message = doc["message"].as<String>();
        alert.timestamp = millis();
        alerts.push(alert);

        // Flash LED for alerts
        digitalWrite(LED, HIGH);
        delay(200); // Longer flash for alerts
        digitalWrite(LED, LOW);
    }
    else if (type == "topology_response") {
        if (doc.containsKey("connections")) {
            JsonArray conns = doc["connections"];
            for (JsonObject conn : conns) {
                NodeConnection newConn;
                newConn.from = from;
                newConn.to = conn["to"].as<uint32_t>();
                newConn.rssi = conn["rssi"] | -50; // Use default if not provided
                connections.push(newConn);
            }
        }
    }
    else if (type == "command_response") {
        // Handle command responses if needed
        String command = doc["command"];
        bool success = doc["success"];
        String response = doc["response"].as<String>();
        
        // Log command response
        ChatMessage chatMsg;
        chatMsg.nodeId = from;
        chatMsg.message = "Command '" + command + "' " + (success ? "succeeded" : "failed") + ": " + response;
        chatMsg.timestamp = millis();
        chatMsg.isSystem = true;
        chatMessages.push(chatMsg);
    }
}

float RootNode::calculateSystemHealth() {
    float health = 1.0;
    
    if (!meshInitialized) {
        // If mesh is not initialized, base health on AP status
        return WiFi.softAPgetStationNum() > 0 ? 1.0 : 0.8;
    }
    
    // With mesh, calculate based on active nodes
    unsigned long now = millis();
    int totalNodes = mesh.getNodeList().size() + 1; // Include root node
    int activeNodes = 1; // Start with 1 for root node
    
    // Check node health based on last update time
    for (const auto& pair : nodeDataCache) {
        if (now - pair.second.lastUpdate < NODE_TIMEOUT) {
            activeNodes++;
        }
    }
    
    // Calculate health as ratio of active to total nodes
    health = (float)activeNodes / totalNodes;
    
    return health;
}

float RootNode::calculatePowerConsumption() {
    // For now, return a simulated value between 0 and 1
    // In a real implementation, this would aggregate power usage data from nodes
    return (float)random(50, 100) / 100.0;
}

float RootNode::calculateNetworkLoad() {
    if (!meshInitialized) {
        // Without mesh, base load on web clients
        return (float)WiFi.softAPgetStationNum() / MAX_CONN;
    }
    
    // With mesh, use message frequency and node count
    int messageCount = chatMessages.size();
    float nodeLoad = (float)mesh.getNodeList().size() / MAX_CONN;
    float messageLoad = (float)messageCount / LOG_SIZE;
    
    return min((messageLoad + nodeLoad) / 2, 1.0f);
}

void RootNode::startDisasterScenario(const String& type) {
    if (currentScenario.isActive) {
        stopDisasterScenario();
    }
    
    currentScenario.isActive = true;
    currentScenario.type = type;
    currentScenario.startTime = millis();
    currentScenario.scenarioName = type;
    currentScenario.nodeStates.clear();
    
    // Send scenario start command to all nodes
    DynamicJsonDocument doc(512);
    doc["type"] = "command";
    doc["command"] = "start_scenario";
    doc["scenarioType"] = type;
    
    String msg;
    serializeJson(doc, msg);
    mesh.sendBroadcast(msg);
    
    // Log scenario start
    ChatMessage chatMsg;
    chatMsg.nodeId = mesh.getNodeId();
    chatMsg.message = "Started disaster scenario: " + type;
    chatMsg.timestamp = millis();
    chatMsg.isSystem = true;
    chatMessages.push(chatMsg);
}

void RootNode::stopDisasterScenario() {
    if (!currentScenario.isActive) return;
    
    // Send scenario stop command to all nodes
    DynamicJsonDocument doc(256);
    doc["type"] = "command";
    doc["command"] = "stop_scenario";
    
    String msg;
    serializeJson(doc, msg);
    mesh.sendBroadcast(msg);
    
    // Log scenario stop
    ChatMessage chatMsg;
    chatMsg.nodeId = mesh.getNodeId();
    chatMsg.message = "Stopped disaster scenario: " + currentScenario.type;
    chatMsg.timestamp = millis();
    chatMsg.isSystem = true;
    chatMessages.push(chatMsg);
    
    currentScenario.isActive = false;
    currentScenario.nodeStates.clear();
}

void RootNode::sendCommand(uint32_t nodeId, const String& command, const JsonDocument& params) {
    DynamicJsonDocument doc(512);
    doc["type"] = "command";
    doc["command"] = command;
    
    // Add command parameters
    JsonObjectConst sourceParams = params.as<JsonObjectConst>();
    if (!sourceParams.isNull()) {
        JsonObject parameters = doc.createNestedObject("parameters");
        for (JsonPairConst kv : sourceParams) {
            parameters[kv.key()] = kv.value();
        }
    }
    
    String msg;
    serializeJson(doc, msg);
    
    if (nodeId == 0) {
        // Broadcast to all nodes
        mesh.sendBroadcast(msg);
    } else {
        // Send to specific node
        mesh.sendSingle(nodeId, msg);
    }
}

void RootNode::updateSensorThresholds(const JsonDocument& thresholds) {
    DynamicJsonDocument doc(512);
    doc["type"] = "command";
    doc["command"] = "update_thresholds";
    JsonObject params = doc.createNestedObject("parameters");
    
    // Copy thresholds
    JsonObjectConst sourceThresholds = thresholds.as<JsonObjectConst>();
    if (!sourceThresholds.isNull()) {
        for (JsonPairConst kv : sourceThresholds) {
            params[kv.key()] = kv.value();
        }
    }
    
    String msg;
    serializeJson(doc, msg);
    mesh.sendBroadcast(msg);
}

void RootNode::checkAndRestartIfNeeded() {
    static unsigned long lastRestartCheck = 0;
    const unsigned long RESTART_CHECK_INTERVAL = 3600000; // 1 hour
    const size_t MIN_FREE_HEAP = 20000; // 20KB minimum free heap
    
    unsigned long now = millis();
    if (now - lastRestartCheck >= RESTART_CHECK_INTERVAL) {
        lastRestartCheck = now;
        
        // Check heap fragmentation and free memory
        if (ESP.getFreeHeap() < MIN_FREE_HEAP) {
            Serial.println("Low memory detected, restarting...");
            ESP.restart();
        }
    }
}

// Support for range-based for loops with CircularBuffer
namespace std {
    template<typename T, size_t S>
    typename CircularBuffer<T,S>::iterator begin(CircularBuffer<T,S>& buf) {
        return buf.begin();
    }

    template<typename T, size_t S>
    typename CircularBuffer<T,S>::iterator end(CircularBuffer<T,S>& buf) {
        return buf.end();
    }
}

// Global mesh callback functions that forward to the root node
void onMeshReceived(uint32_t from, String &msg) {
    if (rootNode) rootNode->receivedCallback(from, msg);
}

void onMeshNewConnection(uint32_t nodeId) {
    if (rootNode) rootNode->newConnectionCallback(nodeId);
}

void onMeshChangedConnections() {
    if (rootNode) rootNode->changedConnectionCallback();
}

void onMeshNodeTimeAdjusted(int32_t offset) {
    Serial.printf("Time adjusted: %d\n", offset);
    if (rootNode) rootNode->nodeTimeAdjustedCallback(offset);
}

void onMeshNodeDelayReceived(uint32_t nodeId, int32_t delay) {
    Serial.printf("Delay to node %u: %d ms\n", nodeId, delay);
    if (rootNode) rootNode->nodeDelayReceivedCallback(nodeId, delay);
}
// Global instance
RootNode* rootNode = nullptr;  // Definition of the global variable

void setup() {
    rootNode = new RootNode();
    rootNode->init();
}

void loop() {
    if (rootNode) {
        rootNode->update();
    }
    userScheduler.execute();
}