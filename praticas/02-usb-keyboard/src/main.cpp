#include <Arduino.h>
#include "USB.h"
#include "USBHIDKeyboard.h"


USBHIDKeyboard Keyboard;


const int BUTTON_PIN = 0; 

void setup() {
  Serial.begin(115200);
  

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Keyboard.begin();
  USB.begin();

  Serial.println("Teclado USB Iniciado!");
  Serial.println("Aperte o botao BOOT da placa para testar.");
}

void loop() {
  
  if (digitalRead(BUTTON_PIN) == LOW) {
    
    
    delay(50); 
    
    if (digitalRead(BUTTON_PIN) == LOW) {
      Serial.println("Botão apertado! Digitando...");

      // --- COMANDOS DO TECLADO ---
      // O println simula a digitação da frase seguida de um "ENTER"
      Keyboard.println("Ola! O ESP32-S3 assumiu o controle do seu teclado.");
      
      // Trava de segurança: Espera você soltar o botão antes de continuar
      while (digitalRead(BUTTON_PIN) == LOW) {
        delay(10);
      }
      
      Serial.println("Botão solto. Aguardando novo aperto.");
    }
  }
}