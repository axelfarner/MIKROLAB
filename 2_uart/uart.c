#include "gpio.h"

// TXD er P0.06 -> pin 8
// RXD er P0.08 -> pin 10

//Trenger pselrxd og pseltxd

//320 - 81
//baudrate, enable, pselrts og pselcts, tasks_starttrx, events_txrdy, events_rxdrdy
#define UART ((NRF_UART_REG*)0x40002000)

typedef struct {
    volatile uint32_t TASKS_STARTRX;
    volatile uint32_t TASKS_STOPRX;
    volatile uint32_t TASKS_STARTTX;
    volatile uint32_t TASKS_STOPTX;
    volatile uint32_t RESEVRED0[3];
    volatile uint32_t EVENTS_RXDRDY;
    volatile uint32_t EVENTS_TXDRDY;    
    volatile uint32_t RESERVED1[988]; // dette var definitivt veldig feil
    volatile uint32_t ENABLE;
    volatile uint32_t PSELRTS;
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELCTS;
    volatile uint32_t PSELRXD;
    volatile uint32_t RXD; // UART_INT_RX
    volatile uint32_t TXD; // UART_INT_TX
    volatile uint32_t BAUDRATE;
    volatile uint32_t CONFIG;
} NRF_UART_REG;

void uart_init() {
    GPIO->PIN_CNF[6] = 1; // output 
    GPIO->PIN_CNF[8] = 0; // input

    UART->ENABLE = 4;

    UART->BAUDRATE = 0x00275000;

    UART->PSELRXD = 6; //try left shift if no work
    UART->PSELTXD = 8; 

    UART->PSELRTS = 0xFFFFFFFF;
    UART->PSELCTS = 0xFFFFFFFF;
    
    UART->TASKS_STARTRX = 1;    
}

void uart_send(char letter) {
    UART->TASKS_STARTTX = 1;
    UART->TXD = letter;
    
    while(UART->EVENTS_TXDRDY == 0){
        continue;
    };

    UART->EVENTS_TXDRDY = 0;
    UART->TASKS_STOPTX = 1;

}

char uart_read() {
    UART->TASKS_STARTRX = 1;
    if (UART->EVENTS_RXDRDY == 1) {
        UART->EVENTS_RXDRDY = 0;
        return UART->RXD;
    }
    
    return '\0';
}