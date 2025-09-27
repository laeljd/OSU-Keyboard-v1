# ESP32 OSU! Keyboard

Este projeto tem como objetivo criar um teclado customizado para o jogo OSU! utilizando uma placa ESP32-C3. O teclado terá 4 botões mecânicos conectados ao ESP32, funcionando como um periférico reconhecido pelo computador.

## Funcionalidades
- 4 botões mecânicos para jogar OSU!
- Comunicação com o PC via USB
- Funcionamento como um dispositivo de teclado (HID)

## Por que usar HID?
O protocolo HID (Human Interface Device) permite que o ESP32 seja reconhecido como um teclado padrão pelo computador, sem necessidade de drivers adicionais. Isso garante compatibilidade com o jogo OSU! e outros softwares.

## Componentes necessários
- 1x ESP32-C3
- 4x botões mecânicos
- Cabos e protoboard ou PCB

## Como funciona
Cada botão será mapeado para uma tecla específica do teclado (por exemplo: Z, X, C, V). Ao pressionar um botão, o ESP32 envia o comando correspondente para o computador via USB, simulando um teclado real.

## Próximos passos
- Montar o circuito com os botões e o ESP32-C3
- Programar o ESP32 para funcionar como HID
- Testar no jogo OSU!
