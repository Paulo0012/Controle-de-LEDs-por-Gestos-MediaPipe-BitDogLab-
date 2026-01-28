#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Definição dos pinos conforme seu hardware e preferências
const uint LED_RED = 13;   // Mapeado para o Dedo Médio no Python
const uint LED_BLUE = 12;  // Mapeado para o Dedo Anelar no Python
const uint LED_GREEN = 11; // Mapeado para o Dedo Indicador no Python

// Função auxiliar para desligar todos os LEDs
void desligar_tudo() {
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_RED, 0);
    gpio_put(LED_BLUE, 0);
}

int main() {
    // Inicializa a comunicação USB Serial para que o Python (COM8) possa falar com a placa
    stdio_init_all();

    // Configuração dos pinos como saída
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    // Garante que o sistema inicie com os LEDs apagados
    desligar_tudo();

    // Mensagem de log para o Serial Monitor (ajuda no debug inicial)
    printf("BitDogLab Pronta! Aguardando gestos via Python na COM8...\n");

    while (true) {
        // Tenta ler um caractere da porta USB sem travar o loop (non-blocking)
        int comando = getchar_timeout_us(0);

        // Se recebeu um dado válido (não houve timeout)
        if (comando != PICO_ERROR_TIMEOUT) {
            
            if (comando == 'G') {
                gpio_put(LED_GREEN, 1);
                printf("LED Verde Ativado (Indicador)\n");
            } 
            else if (comando == 'R') {
                gpio_put(LED_RED, 1);
                printf("LED Vermelho Ativado (Medio)\n");
            }
            else if (comando == 'B') {
                gpio_put(LED_BLUE, 1);
                printf("LED Azul Ativado (Anelar)\n");
            }
            else if (comando == '0') {
                desligar_tudo();
                printf("Mao Fechada: Todos os LEDs desligados\n");
            }
        }

        // Pequeno atraso de 10ms para evitar consumo excessivo de CPU da placa
        sleep_ms(10);
    }

    return 0;
}