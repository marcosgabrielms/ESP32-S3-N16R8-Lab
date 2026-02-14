# ⌨️ Teclado USB Nativo (ESP32-S3)

Este projeto transforma a placa ESP32-S3 em um teclado USB (Dispositivo HID) utilizando a sua porta USB nativa. Ao pressionar o botão `BOOT` (GPIO 0) integrado na placa, o microcontrolador digita automaticamente uma frase pré-programada no computador.

## ⚠️ Aviso Importante sobre os Testes

**Não teste este código com o Monitor Serial do VS Code aberto!**

Como ativamos a biblioteca `USBHIDKeyboard`, a placa passa a atuar como um Dispositivo USB Composto (Teclado + Porta Serial). Quando o botão é pressionado para enviar o texto, o sistema operacional (Windows) dá prioridade extrema à interface de teclado. Isso faz com que a conexão da porta COM no Monitor Serial caia ou fique em um loop de desconexão (tentando abrir e fechar a porta `COM1` ou similar).

**Onde testar para ver o resultado:**
- Bloco de Notas (Notepad)
- WhatsApp Web
- Barra de pesquisa do navegador
- Qualquer outro campo de texto do seu sistema operacional.

## 🚀 Como Executar
1. Conecte o cabo do PC na porta marcada como **USB** (porta nativa) da placa.
2. Faça o Upload do código usando o PlatformIO.
3. Feche o Monitor Serial do VS Code (clicando no ícone da lixeira no painel inferior).
4. Abra o Bloco de Notas ou clique em um chat do WhatsApp Web.
5. Pressione o botão **BOOT** na placa e veja o texto sendo digitado sozinho!