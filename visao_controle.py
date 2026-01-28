import cv2
from cvzone.HandTrackingModule import HandDetector
import serial
import time

# --- CONFIGURAÇÃO DA PORTA SERIAL ---
PORTA_COM = 'COM8' 
BAUD_RATE = 115200

try:
    porta_serial = serial.Serial(PORTA_COM, BAUD_RATE, timeout=0.1)
    time.sleep(2) 
    print(f"Conectado à BitDogLab na {PORTA_COM}!")
except Exception as e:
    print(f"ERRO: Verifique se a porta {PORTA_COM} está livre: {e}")
    exit()

# --- CONFIGURAÇÃO DA CÂMERA ---
video = cv2.VideoCapture(0, cv2.CAP_DSHOW)
video.set(3, 640)
video.set(4, 480)

# Detector configurado para 1 mão
detector = HandDetector(detectionCon=0.8, maxHands=1)

print("Sistema iniciado! Pressione ESC para sair.")

while True:
    check, img = video.read()
    if not check: break

    hands, img = detector.findHands(img, draw=True)
    
    if hands:
        hand = hands[0]
        # Lista: [Polegar, Indicador, Médio, Anelar, Mínimo]
        dedos = detector.fingersUp(hand)
        
        # 1. Se a mão estiver totalmente fechada (nenhum dedo levantado)
        if dedos.count(1) == 0:
            porta_serial.write(b'0')
            print("Mão Fechada: Desligando tudo")
        
        else:
            # 2. Dedo Indicador (índice 1) -> LED VERDE
            if dedos[1] == 1:
                porta_serial.write(b'G')
                print("Indicador: Verde ON")
            
            # 3. Dedo Médio (índice 2) -> LED VERMELHO
            if dedos[2] == 1:
                porta_serial.write(b'R')
                print("Médio: Vermelho ON")
            
            # 4. Dedo Anelar (índice 3) -> LED AZUL
            if dedos[3] == 1:
                porta_serial.write(b'B')
                print("Anelar: Azul ON")

    # Mostra a imagem na tela
    cv2.imshow('Controle por Dedos - BitDogLab', cv2.flip(img, 1))
    
    if cv2.waitKey(1) == 27: break

# Encerramento seguro
porta_serial.write(b'0')
video.release()
cv2.destroyAllWindows()
porta_serial.close()