#include "uart.h"
#include "gpio.h"
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdio.h>

ssize_t _write(int fd, const void *buf, size_t count){
    char * letter = (char *)(buf);
    for (int i = 0; i < count; i++){
            uart_send(*letter);
            letter++;
        }
    return count;
}

  int main() {
	// Configure LED Matrix
	for (int i = 17; i <= 20; i++) {
		GPIO->DIRSET = (1 << i);
	}

	GPIO->PIN_CNF[13] = (3 << 2);
	GPIO->PIN_CNF[14] = (3 << 2);
    GPIO->PIN_CNF[15] = (3 << 2);



	int sleep = 0;
    char received = '\0';
    
    // turn lights off
    GPIO->OUTSET |= ((1 << 17) | (1 << 18) | (1 << 19) | (1 << 20));
    bool lightOn = false;

    uart_init();


	while(1) {
        
		// bit #13 is checked for 
		if (!(GPIO->IN & 1 << 13)) {
                
                GPIO->OUTCLR |= ((1 << 18));

				uart_send('A');
			}

		if (!(GPIO->IN & 1 << 14)) {
                uart_send('B');
			}
        
        if (!(GPIO->IN & 1 << 15)) {
                
                GPIO->OUTCLR |= ((1 << 18));

                iprintf("The average grade in TTK%d was in %d was: %c\n\r",4235,2022,'B');
			}

		
        received = uart_read();

        if (received != '\0') {
            if (lightOn) {
                // light off
				GPIO->OUTSET |= ((1 << 17) | (1 << 18) | (1 << 19) | (1 << 20));
            } else {
                // light on
				GPIO->OUTCLR |= ((1 << 17) | (1 << 18) | (1 << 19) | (1 << 20));
                
            }
            lightOn = !lightOn;
        }

		sleep = 10000;
		while(--sleep); // Delay
	}
	return 0;
}
