#include <Arduino.h>
#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  unsigned long t = millis();
  while (!Serial && millis() - t < 2000);

  Serial.println("\n Iniciando WiFi");

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Iniciando a busca...");
}

String traduzirEncriptacao(wifi_auth_mode_t encryptionType) {
  switch (encryptionType) {
    case WIFI_AUTH_OPEN: return "Aberta";
    case WIFI_AUTH_WEP: return "WEP";
    case WIFI_AUTH_WPA_PSK: return "WPA";
    case WIFI_AUTH_WPA2_PSK: return "WPA2";
    case WIFI_AUTH_WPA_WPA2_PSK: return "WPA/WPA2";
    case WIFI_AUTH_WPA3_PSK: return "WPA3";
    case WIFI_AUTH_WPA2_ENTERPRISE: return "WPA2-E";
    default: return "Desconhecido";
  }
}

void loop() {
  Serial.println("\n Escaneando redes..");

  int n = WiFi.scanNetworks();

  Serial.println("Busca finalizada");

  if (n == 0) {
    Serial.println("Nenhuma rede encontrada");
  } else {
    Serial.printf("%d redes encontradas:\n\n", n);

    Serial.println("   | SSID (Nome)                    | Sinal (dBm) | Segurança    |");
    Serial.println("   |--------------------------------|-------------|--------------|");

    for (int i = 0; i < n; ++i) {
      String ssid = WiFi.SSID(i);
      int32_t rssi = WiFi.RSSI(i);
      String seguranca = traduzirEncriptacao(WiFi.encryptionType(i));
      Serial.printf("   | %-30s | %4d dBm   | %-12s |\n", 
                    ssid.c_str(), 
                    rssi, 
                    seguranca.c_str());
      
      delay(10);
    }
    Serial.println("   --------------------------------------------------------------");
  }
  WiFi.scanDelete();

  delay(5000);
}