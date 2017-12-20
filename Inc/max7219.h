#ifndef MAX7219_H_
#define MAX7219_H_

#include "stm32f1xx_hal.h"

int Symbol(int number);
int SymbolWithDot (int number);
void TickerBar_7219(char line[], int line_lenght, int speed);
void Send_7219 (uint8_t rg, uint8_t dt);
void Clear_7219 (void);
void Number_7219_decoding (volatile long n);
void Number_7219_non_decoding (volatile long n);
void Init_7219 (void);

#endif /* MAX7219_H_ */
