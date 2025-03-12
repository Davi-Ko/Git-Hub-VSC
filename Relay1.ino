#include <ESP8266WiFi.h>
#include <espnow.h>

#define RELAY_PIN 2 // Pino onde o relé está conectado

// Configuração do AP (Ponto de Acesso)
const char *apSSID = "ESP-AP";
const char *apPassword = "12345678";

// MAC Address do outro ESP (substitua pelo MAC do receptor)
uint8_t macDestino[] = {0xEC, 0xFA, 0xBC, 0x12, 0x34, 0x56};

void enviarDados(uint8_t *mac, uint8_t status) {
  Serial.print("Status do envio: ");
  Serial.println(status == 0 ? "Sucesso" : "Falha");
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Inicializa o relé desligado

  // Configura o modo STA+AP
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(apSSID, apPassword);
  Serial.print("Rede AP iniciada com IP: ");
  Serial.println(WiFi.softAPIP());  // Exibe o IP do AP

  // Conecta-se a outra rede Wi-Fi, caso necessário
  WiFi.begin("MinhaWiFi", "minhaSenha");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado à rede externa!");

  // Inicializa o ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Erro ao inicializar ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(macDestino, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  esp_now_register_send_cb(enviarDados);
}

void loop() {
  bool relayState = digitalRead(RELAY_PIN);
  byte relayStatus = relayState ? 1 : 0; // Envia 1 para ON, 0 para OFF

  // Envia o status do relé
  esp_now_send(macDestino, &relayStatus, sizeof(relayStatus));
  delay(2000); // Envia o status a cada 2 segundos
}
