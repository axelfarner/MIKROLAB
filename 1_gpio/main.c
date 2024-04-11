#include <stdint.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;


/*

Button 1 (normally high) -> P0.13
Button 2 (normally high) -> P0.14 


*/

int main(){
	// Configure LED Matrix
	for(int i = 0; i <= 3; i++){
		GPIO->DIRSET = (1 << i);
		}

	GPIO->PIN_CNF[13] = 0;
	GPIO->PIN_CNF[14] = 0;

	int sleep = 0;

	while(1){
		if(!((GPIO->IN | 0b11111111111110111111111111111111)==0b11111111111111111111111111111111)){
				//setter høy
				GPIO->OUT |= 0b00000000000000000111100000000000;
				//setter lav
				GPIO->OUT &= 0b11111111111111111000011111111111;
			}
		

		if(!((GPIO->IN | 0b11111111111111011111111111111111)==0b11111111111111111111111111111111)){
				//setter lav
				GPIO->OUT &= 0b11111111111111111000011111111111;
				//setter høy
				GPIO->OUT |= 0b00000000000000000111100000000000;
			}
		

		sleep = 10000;
		while(--sleep); // Delay
	}
	return 0;
}
