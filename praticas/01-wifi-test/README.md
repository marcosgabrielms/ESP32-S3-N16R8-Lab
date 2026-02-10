# 📡 Scanner WiFi (ESP32-S3 N16R8)

Este projeto é uma prática introdutória para testar o rádio WiFi da placa **ESP32-S3 N16R8**.

## 🎯 Objetivo
- Verificar o funcionamento do hardware de rádio.
- Listar as redes disponíveis no ambiente.
- Exibir a potência do sinal (RSSI) e o tipo de segurança de cada rede.
- Validar as configurações de memória (PSRAM/Flash) no `platformio.ini`.

## 🛠️ Hardware Necessário
- Placa ESP32-S3 (Versão N16R8 - 16MB Flash / 8MB PSRAM).
- Cabo USB-C de dados.

## ⚙️ Configuração (PlatformIO)
Certifique-se de usar as flags corretas para N16R8:
- `board_build.arduino.memory_type = qio_opi`
- `board_upload.flash_size = 16MB`
- `board_build.partitions = default_16MB.csv`

## 🚀 Como Executar
1. Conecte a placa via USB.
2. Abra o Monitor Serial (Velocidade: 115200).
3. Faça o upload do código.
4. O resultado aparecerá no terminal listando as redes a cada 5 segundos.

## 📸 Exemplo de Saída
```text
--- INICIANDO SCANNER WIFI (ESP32-S3) ---
3 redes encontradas:

   | SSID (Nome)                    | Sinal (dBm) | Segurança    |
   |--------------------------------|-------------|--------------|
   | MinhaCasa_2G                   |  -45 dBm    | WPA2         |
   | Vizinho_WiFi                   |  -88 dBm    | WPA/WPA2     |
   | Free_WiFi                      |  -90 dBm    | Aberta       |
   --------------------------------------------------------------