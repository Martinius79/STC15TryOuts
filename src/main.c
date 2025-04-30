#include <stdint.h>
#include <stdio.h>
// #include <reg51.h>

#include "STC15Fxx.h" // Include the STC15Fxx header file
#include "delay.h"
void UART_Init(void) {
    SCON = 0x50;  // UART-Modus 1, 8-Bit UART, REN aktiviert (Empfang erlaubt)
    TMOD |= 0x20; // Timer1 im Modus 2 (8-Bit Auto-Reload)
    TH1 = 0xFD;   // Baudrate 9600 bei 11.0592 MHz
    TL1 = 0xFD;
    TR1 = 1;      // Timer1 starten
    // PCON |= 0x80; // SMOD-Bit setzen, um die Baudrate zu verdoppeln (optional)
}

void UART_SendChar(char c) {
    SBUF = c;          // Zeichen in den UART-Sendepuffer schreiben
    while (!TI);       // Warten, bis das Senden abgeschlossen ist
    TI = 0;            // TI-Flag zurücksetzen
}

void UART_SendString(const char *str) {
    while (*str) {
        UART_SendChar(*str++);
    }
}

// void delay_ms(unsigned int ms) {
//     unsigned int i, j;
//     for (i = 0; i < ms; i++)
//         for (j = 0; j < 123; j++);
// }

void main(void) {
    P1M0 = 0x00;  // Setze P1.0 als Push-Pull-Ausgang
    P1M1 = 0x00;
    UART_Init();       // UART initialisieren
    UART_SendString("UART Initialized\r\n");
    while (1) {
        P1 ^= 0x01;  // Toggle P1.0
        // UART_SendString("Hello, UART!\r\n");
        UART_SendChar('A'); // Sende ein einzelnes Zeichen
        delay_ms(1000);
    }
}