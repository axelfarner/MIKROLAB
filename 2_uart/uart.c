#include "gpio.h"

// TXD er P0.06 -> pin 8
// RXD er P0.08 -> pin 10

//Trenger pselrxd og pseltxd

//320 - 81
//baudrate, enable, pselrts og pselcts, tasks_starttrx, events_txrdy, events_rxdrdy


#define GPIO ((NRF_UART_REG*)0x40002000)

typedef struct{
    volatile uint32_t TASKS_STARTRX;
    volatile uint32_t TASKS_STOPRX;
    volatile uint32_t TASKS_STARTTX;
    volatile uint32_t TASKS_STOPTX;
    volatile uint32_t RESEVRED0[3];
    volatile uint32_t EVENTS_RXDRDY;
    volatile uint32_t EVENTS_TXDRDY;
    volatile uint32_t RESERVED1[239]; // dette er muliges veldig feil
    volatile uint32_t ENABLE;
    volatile uint32_t PSELRTS;
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELCTS;
    volatile uint32_t PSELRXD;
    volatile uint32_t RXD; // UART_INT_RX
    volatile uint32_t TXD; // UART_INT_TX
    volatile uint32_t BAUDRATE;
}NRF_UART_REG;

void uart_init(){

}