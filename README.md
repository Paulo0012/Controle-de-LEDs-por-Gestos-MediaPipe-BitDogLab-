# Controle de LEDs por Gestos - MediaPipe & BitDogLab

Projeto de Visão Computacional integrado com Sistemas Embarcados utilizando **Python** e **C**. 
O sistema utiliza o MediaPipe para reconhecer gestos da mão e envia comandos via Serial (USB) 
para uma placa Raspberry Pi Pico W (BitDogLab).

## 🛠️ Tecnologias
- **Visão Computacional:** Python 3.11, MediaPipe, OpenCV, CVZone.
- **Embarcados:** Linguagem C, SDK do Raspberry Pi Pico.
- **Hardware:** BitDogLab (RP2040).

## 🎮 Funcionalidades
- 🖐️ **Mão Fechada:** Desliga todos os LEDs.
- ☝️ **Dedo Indicador:** Liga LED Verde (Pino 11).
- 🖕 **Dedo Médio:** Liga LED Vermelho (Pino 13).
- 💍 **Dedo Anelar:** Liga LED Azul (Pino 12).

## 🚀 Como Executar
1. Compile e carregue o `embarcado_visao.c` na placa via VS Code.
2. Crie o ambiente virtual Python: `py -3.11 -m venv .venv`
3. Instale as dependências: `pip install -r requirements.txt`
4. Ajuste a porta COM no arquivo `visao_controle.py`.
5. Execute: `python visao_controle.py`
