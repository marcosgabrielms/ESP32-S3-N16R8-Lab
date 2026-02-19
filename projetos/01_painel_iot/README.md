# 🌐 Painel de Controle IoT - ESP32-S3

Este projeto é um servidor web leve, responsivo e autônomo rodando diretamente em um microcontrolador **ESP32-S3 (N16R8)**. Ele permite o controle de atuadores nativos e a leitura de sensores da placa através de qualquer navegador web (celular ou PC) conectado à mesma rede Wi-Fi.

## ✨ Funcionalidades

* **Controle de LED RGB Endereçável (WS2812):** Ligar, desligar e alterar a cor do LED nativo (Pino 48) através de um menu dropdown intuitivo na interface web.
* **Monitoramento de Temperatura:** Leitura em tempo real do sensor de temperatura interno da CPU do ESP32-S3.
* **Design Monolítico e Simples:** Toda a lógica de rede (Wi-Fi), roteamento HTTP (WebServer), interface HTML/CSS e controle de hardware está consolidada de forma limpa em um único arquivo (`src/main.cpp`).

## 🛠️ Hardware Necessário

* Placa de desenvolvimento ESP32-S3 (Testado no modelo N16R8 com USB Nativa).
* Cabo USB-C.
* *Nenhum componente externo é necessário!* O projeto utiliza exclusivamente o hardware já soldado na placa.

## 💻 Dependências e Ambiente

Este projeto foi construído utilizando a extensão **PlatformIO** no VS Code.

* **Framework:** Arduino
* **Bibliotecas Externas:**
  * `Adafruit NeoPixel` (Para controle do LED RGB)
* **Bibliotecas Nativas Utilizadas:**
  * `WiFi.h` e `WebServer.h` (Para comunicação e servidor)
  * `driver/temp_sensor.h` (Para leitura de temperatura da CPU)

## ⚠️ Observação para Git Clone / Pull

Como pastas de configuração (como `.vscode` e `.pio`) estão no `.gitignore` para manter o repositório limpo, ao baixar este projeto em um novo PC via `git clone` ou `git pull`, o PlatformIO pode não reconhecer o projeto de imediato e acusar erro nas bibliotecas.

Para resolver:
1. No VS Code, vá no menu superior em **File > Add Folder to Workspace...** e selecione a pasta raiz deste projeto (`01_painel_iot`).
2. Clique no ícone de **Build** (o `✓` na barra azul inferior). O PlatformIO fará o download automático das dependências e reconfigurará os caminhos do C/C++ (IntelliSense).

## 🚀 Como Usar

1. **Abra o projeto** no VS Code com a extensão PlatformIO instalada (e adicione ao Workspace, se necessário).
2. **Configure sua Rede:** No arquivo `src/main.cpp`, altere as seguintes variáveis nas primeiras linhas de código para as credenciais do seu roteador:
   ```cpp
   const char* ssid = "NOME_DO_SEU_WIFI";
   const char* password = "SENHA_DO_SEU_WIFI";
   ```
3. **Upload:** Conecte a placa na porta **USB** (nativa) e clique em **Upload** (`→`) na barra inferior do PlatformIO.
4. **Descubra o IP:** Abra o **Monitor Serial** (ícone de tomada). Aguarde a placa conectar à rede e ela imprimirá o endereço IP local (ex: `http://192.168.0.15`).
5. **Acesse o Painel:** Digite o IP fornecido no navegador do seu smartphone ou computador.

## 📂 Estrutura do Projeto

Para manter a simplicidade e facilitar o aprendizado, a estrutura visual foi reduzida ao essencial:

```text
01_painel_iot/
├── src/
│   └── main.cpp        # Lógica centralizada (Wi-Fi, Servidor, HTML e Hardware)
├── platformio.ini      # Configurações de memória, portas e bibliotecas
└── README.md           # Documentação do projeto
```