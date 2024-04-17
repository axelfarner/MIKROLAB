#include "uart.h"
#include "gpio.h"
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h> 

ssize_t _write(int fd, const void *buf, size_t count){
    char * letter = (char *)(buf);
    for (int i = 0; i < count; i++){
            uart_send(*letter);
            letter++;
        }
    return count;
}

int main(){
	// Configure LED Matrix
	for (int i = 0; i <= 3; i++) {
		GPIO->DIRSET = (1 << i);
		}

	GPIO->PIN_CNF[13] = 0;
	GPIO->PIN_CNF[14] = 0;

	int sleep = 0;
    char received = '\0';
    bool lightOn = false;
	while(1) {
		// bit #13 is checked for 
		if (!(GPIO->IN & 1 << 13)) {
				uart_send('A');
			}
		

		if (!(GPIO->IN & 1 << 14)) {
				
                uart_send('A');
			}
		
		sleep = 10000;
		while(--sleep); // Delay
        received = uart_read();

        if (received != '\0') {
            if (lightOn) {
                // light off
                GPIO->OUT &= 0xFFFF87FF;
            } else {
                // light on
                GPIO->OUT |= 0x7800;
            }
            lightOn = !lightOn;
        }
	}
	return 0;
}