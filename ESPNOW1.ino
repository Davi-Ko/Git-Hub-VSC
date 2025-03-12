#include <ESP8266WiFi.h>
#include <espnow.h>

#define RELAY_PIN 2 // Pino onde o relé está conectado

// MAC Address do dispositivo receptor (substitua pelo MAC do outro ESP)
uint8_t macDestino[] = {0xEC, 0xFA, 0xBC, 0x12, 0x34, 0x56};

void enviarDados(uint8_t *mac, uint8_t status) {
  Serial.print("Status do envio: ");
  Serial.println(status == 0 ? "Sucesso" : "Falha");
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Inicializa o relé desligado

  // Configura o modo de Wi-Fi para ESP-NOW
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Erro ao inicializar ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(macDestino, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  esp_now_register_send_cb(enviarDados);
}

void loop() {
  // Aqui você controla o estado do relé
  bool relayState = digitalRead(RELAY_PIN);
  byte relayStatus = relayState ? 1 : 0; // Envia 1 para ON, 0 para OFF

  // Envia o status do relé
  esp_now_send(macDestino, &relayStatus, sizeof(relayStatus));
  delay(2000); // Envia o status a cada 2 segundos
}
