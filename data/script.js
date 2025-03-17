let relayIPs = {
    relay1: "192.168.4.2",
    relay2: "192.168.4.3"
};

const updateInterval = 5000;

document.addEventListener('DOMContentLoaded', function() {
    loadSettings();
    
    checkRelaysStatus();
    
    setInterval(checkRelaysStatus, updateInterval);
    
    document.getElementById('relay1-ip').value = relayIPs.relay1;
    document.getElementById('relay2-ip').value = relayIPs.relay2;
    
    logMessage("Sistema inicializado e verificando status dos relays...");
});

function controlRelay(relay, action) {
    const ip = relayIPs[relay];
    logMessage(`Enviando comando ${action} para ${relay} (${ip})...`);
    
    fetch(`http://${ip}/${action}`)
        .then(response => {
            if (response.ok) {
                return response.text();
            }
            throw new Error(`Falha na requisição: ${response.status}`);
        })
        .then(data => {
            logMessage(`Resposta do ${relay}: ${data}`);
            setTimeout(() => {
                checkRelayStatus(relay);
            }, 500);
        })
        .catch(error => {
            logMessage(`Erro ao controlar ${relay}: ${error.message}`, 'error');
            updateConnectionStatus(relay, false);
        });
}

function checkRelaysStatus() {
    checkRelayStatus('relay1');
    checkRelayStatus('relay2');
}

function checkRelayStatus(relay) {
    const ip = relayIPs[relay];
    
    fetch(`http://${ip}/api`)
        .then(response => {
            if (response.ok) {
                updateConnectionStatus(relay, true);
                return fetch(`http://${ip}/status`);
            }
            throw new Error('Dispositivo offline');
        })
        .then(response => {
            if (response.ok) {
                return response.text();
            }
            throw new Error(`Falha na requisição de status: ${response.status}`);
        })
        .then(data => {

            const statusMatch = data.match(/Status: (ON|OFF)/);
            if (statusMatch && statusMatch[1]) {
                updateRelayStatus(relay, statusMatch[1]);
            }
        })
        .catch(error => {
            updateConnectionStatus(relay, false);
            updateRelayStatus(relay, 'Desconectado');
        });
}

function updateRelayStatus(relay, status) {
    const statusElement = document.getElementById(`${relay}-status`);
    
    if (status === 'ON') {
        statusElement.textContent = 'LIGADO';
        statusElement.className = 'status on';
    } else if (status === 'OFF') {
        statusElement.textContent = 'DESLIGADO';
        statusElement.className = 'status off';
    } else {
        statusElement.textContent = status;
        statusElement.className = 'status';
    }
}

function updateConnectionStatus(relay, isConnected) {
    const connectionElement = document.getElementById(`${relay}-connection`);
    
    if (isConnected) {
        connectionElement.textContent = 'Conectado';
        connectionElement.className = 'connected';
    } else {
        connectionElement.textContent = 'Desconectado - Falha na conexão';
        connectionElement.className = 'disconnected';
    }
}

function saveSettings() {
    const relay1IP = document.getElementById('relay1-ip').value.trim();
    const relay2IP = document.getElementById('relay2-ip').value.trim();

    if (isValidIP(relay1IP) && isValidIP(relay2IP)) {
        relayIPs.relay1 = relay1IP;
        relayIPs.relay2 = relay2IP;
        
        localStorage.setItem('relayIPs', JSON.stringify(relayIPs));
        
        logMessage(`Configurações salvas: Relay1 = ${relay1IP}, Relay2 = ${relay2IP}`);
        checkRelaysStatus(); // Verifica status com os novos IPs
    } else {
        logMessage('Endereços IP inválidos. Por favor, verifique o formato.', 'error');
    }
}

function loadSettings() {
    const savedSettings = localStorage.getItem('relayIPs');
    if (savedSettings) {
        relayIPs = JSON.parse(savedSettings);
        logMessage('Configurações carregadas do armazenamento local.');
    }
}

function isValidIP(ip) {
    const regex = /^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/;
    return regex.test(ip);
}

function logMessage(message, type = 'info') {
    const logElement = document.getElementById('system-log');
    const now = new Date();
    const timestamp = now.toLocaleTimeString();
    
    const logEntry = document.createElement('p');
    logEntry.innerHTML = `<span class="timestamp">[${timestamp}]</span> ${message}`;
    
    if (type === 'error') {
        logEntry.style.color = '#e74c3c';
    }
    
    logElement.appendChild(logEntry);
    logElement.scrollTop = logElement.scrollHeight; // Auto-scroll para a mensagem mais recente
}