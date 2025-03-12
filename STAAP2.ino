#include <ESP8266WiFi.h>
#include <espnow.h>

#define RELAY_PIN 2 // Pino onde o relé está conectado

void receberDados(uint8_t *mac, uint8_t *dados, uint8_t len) {
  bool relayState = *dados; // Recebe o estado (1 ou 0)
  if (relayState == 1) {
    digitalWrite(RELAY_PIN, HIGH);  // Aciona o relé (liga)
  } else {
    digitalWrite(RELAY_PIN, LOW);   // Desliga o relé
  }
  Serial.print("Estado recebido: ");
  Serial.println(relayState ? "Ligado" : "Desligado");
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Inicializa o relé desligado

  // Configura o Wi-Fi para STA+AP
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("ESP-AP", "12345678"); // AP com mesmo nome e senha do outro ESP
  Serial.print("Rede AP iniciada com IP: ");
  Serial.println(WiFi.softAPIP());  // IP do AP

  // Conecta-se à rede Wi-Fi do primeiro ESP (STA)
  WiFi.begin("ESP-AP", "12345678");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado ao AP!");

  // Inicializa o ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Erro ao inicializar ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(receberDados);
}

void loop() {
  // O código principal está na função de recepção
}
