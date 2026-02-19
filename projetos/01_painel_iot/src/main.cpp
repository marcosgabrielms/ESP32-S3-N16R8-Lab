#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_NeoPixel.h>
#include "driver/temp_sensor.h" 

const char* ssid = "Sua rede wifi";
const char* password = "Senha do seu wifi";

#define PIN_RGB 48
#define NUM_PIXELS 1


Adafruit_NeoPixel pixels (NUM_PIXELS, PIN_RGB, NEO_GRB + NEO_KHZ800);
WebServer server(80);

bool ledLigado = false;
uint8_t corR = 0, corG = 255, corB = 0;

void aplicarCorLed(uint8_t r, uint8_t g, uint8_t b) {
  pixels.setPixelColor(0, pixels.Color(r, g, b));
  pixels.show();
}

void acenderLed() {
  ledLigado = true;
  aplicarCorLed(corR, corG, corB);
  Serial.println("LED ligado");
}

void apagarLed() {
  ledLigado = false;
  aplicarCorLed(0, 0, 0);
  Serial.println("LED desligado");
}

void mudarCorLed(uint8_t r, uint8_t g, uint8_t b) {
  corR = r;
  corG = g;
  corB = b;
  if (ledLigado) {
    aplicarCorLed(corR, corG, corB);
  }
  Serial.printf("Cor alterada para: R:%d G:%d B:%d\n", r , g, b );
}

void extrairRGBdoHex(String hex, uint8_t &r, uint8_t &g, uint8_t &b) {
  if (hex.startsWith("#")) hex.remove(0, 1);
  long numCor = strtol(hex.c_str(), NULL, 16);
  r = (numCor >> 16) & 0xFF;
  g = (numCor >> 8) & 0xFF;
  b = numCor & 0xFF;
}

// --- FUNÇÃO PARA LER A TEMPERATURA INTERNA ---
float lerTemperaturaInterna() {
  float temp_celsius = 0.0;
  temp_sensor_read_celsius(&temp_celsius);
  return temp_celsius;
}

// HTML da página
String getHTML() {
  
  char hexCorAtual[8];
  sprintf(hexCorAtual, "#%02x%02x%02x", corR, corG, corB);

  // Lê a temperatura no momento em que a página é carregada
  float tempAtual = lerTemperaturaInterna();

  String html = "<!DOCTYPE html><html lang=\"pt-BR\"><head>";
  html += "<meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  html += "<title>Painel ESP32-S3</title>";
  html += "<style>";
  html += "body { font-family: sans-serif; text-align: center; background-color: #2c3e50; color: #fff; margin-top: 30px; }";
  html += ".painel { background: #34495e; padding: 20px; border-radius: 10px; display: inline-block; box-shadow: 0 4px 8px rgba(0,0,0,0.3); }";
  html += ".btn { padding: 15px 30px; font-size: 18px; border: none; border-radius: 8px; cursor: pointer; color: white; margin: 10px; transition: 0.2s; text-decoration: none; display: inline-block; }";
  html += ".btn-on { background-color: #27ae60; } .btn-off { background-color: #e74c3c; }";
  html += "input[type='color'] { width: 60px; height: 40px; border: none; cursor: pointer; background: none; }";
  html += ".temp-box { background-color: #16a085; padding: 15px; border-radius: 8px; margin-top: 20px; font-size: 22px; font-weight: bold; }";
  html += "</style></head><body>";
  
  html += "<h1>Painel de Controle IoT</h1>";
  html += "<div class=\"painel\">";
  
  // Controle de Ligar/Desligar
  html += "<h2>LED RGB</h2>";
  if (ledLigado) {
    html += "<p>Status: <strong>LIGADO</strong></p>";
    html += "<a href=\"/led/off\"><button class=\"btn btn-off\">Desligar</button></a>";
  } else {
    html += "<p>Status: <strong>DESLIGADO</strong></p>";
    html += "<a href=\"/led/on\"><button class=\"btn btn-on\">Ligar</button></a>";
  }

  // Seletor de Cor 
 html += "<h3>Mudar Cor</h3>";
  html += "<form action=\"/led/cor\" method=\"GET\">";
  
  html += "<select name=\"c\" required style=\"padding: 10px; font-size: 16px; border-radius: 5px; border: none; cursor: pointer; margin-bottom: 10px;\">";
  html += "<option value=\"\" disabled selected>Selecione uma cor...</option>";
  html += "<option value=\"#ff0000\">Vermelho</option>";
  html += "<option value=\"#00ff00\">Verde</option>";
  html += "<option value=\"#0000ff\">Azul</option>";
  html += "<option value=\"#ffff00\">Amarelo</option>";
  html += "<option value=\"#ff00ff\">Magenta</option>";
  html += "<option value=\"#00ffff\">Ciano</option>";
  html += "<option value=\"#ffffff\">Branco</option>";
  html += "</select>";
  html += "<br><button type=\"submit\" class=\"btn\" style=\"background:#2980b9;\">Aplicar Cor</button>";
  html += "</form>";

  // Sensor de Temperatura Interna
  html += "<hr style=\"border-color:#7f8c8d; margin: 20px 0;\">";
  html += "<h2>Sensores da Placa</h2>";
  html += "<div class=\"temp-box\">Temperatura da CPU: " + String(tempAtual, 1) + " &deg;C</div>";
  html += "<p style=\"font-size: 12px; color: #bdc3c7;\">Atualize a página para ler novamente.</p>";
  
  html += "</div></body></html>";
  return html;
}

// Rotas
void rotaPrincipal() { server.send(200, "text/html", getHTML()); }

void rotaLigar() { acenderLed(); server.sendHeader("Location", "/"); server.send(303); }

void rotaDesligar() { apagarLed(); server.sendHeader("Location", "/"); server.send(303); }

void rotaMudarCor() {
  if (server.hasArg("c")) {
    uint8_t r, g, b;
    extrairRGBdoHex(server.arg("c"), r, g, b);
    mudarCorLed(r, g, b);
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  
  temp_sensor_config_t temp_sensor = TSENS_CONFIG_DEFAULT();
  temp_sensor_set_config(temp_sensor);
  temp_sensor_start();

  // Inicia Pinos
  pixels.begin();
  pixels.setBrightness(100);
  apagarLed();

  Serial.println("\nConectando ao Wi-Fi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    aplicarCorLed(0, 0, 50); 
    delay(200);
    aplicarCorLed(0, 0, 0);
    delay(200);
    Serial.print(".");
  }

  apagarLed();
  Serial.println("\nWi-Fi Conectado!");
  Serial.print("Acesse: http://");
  Serial.println(WiFi.localIP());

 
  server.on("/", rotaPrincipal);
  server.on("/led/on", rotaLigar);
  server.on("/led/off", rotaDesligar);
  server.on("/led/cor", rotaMudarCor);

  server.begin();
}

void loop() {
  server.handleClient();
  delay(2);
  
  static unsigned long tempoUltimoPrint = 0;
  if (millis() - tempoUltimoPrint > 5000) { 
    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("O seu painel esta online! Acesse: http://");
      Serial.println(WiFi.localIP());
    }
    tempoUltimoPrint = millis();
  }
}