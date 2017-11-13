#include "max7219.h"

uint8_t aTxBuf[1]={0};
extern SPI_HandleTypeDef hspi1;
char dg=5;

char symbols[]={
  0x7e, // 0
  0x30, // 1
  0x6d, // 2
  0x79, // 3
  0x33, // 4
  0x5b, // 5
  0x5f, // 6
  0x70, // 7
  0x7f, // 8
  0x7b, // 9
  0x01, // -
  0x00, // ""

  0x77, // A
  0x1F, // b
  0x4E, // C
  0x3D, // d
  0x4F, // E
  0x47, // F
  0x5e, // G
  0x37, // H
  0x06, // I
  0x3C, // J
  0x0E, // L
  0x15, // n
  0x1D, // o
  0x67, // P
  0x73, // q
  0x05, // r
  0x5B, // S
  0x0F, // t
  0x3E, // U
  0x3B, // Y
};

#define cs_set() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
#define cs_reset() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)

int Symbol(int number)
{
  return symbols[number];
}

int SymbolWithDot(int symbol)
{
  return symbol |= 1 << 7;
}

void Send_7219 (uint8_t rg, uint8_t dt)
{
  cs_set();
  aTxBuf[0]=rg;
  HAL_SPI_Transmit (&hspi1, (uint8_t*)aTxBuf, 1, 5000);
  aTxBuf[0]=dt;
  HAL_SPI_Transmit (&hspi1, (uint8_t*)aTxBuf, 1, 5000);
  cs_reset();
}
//------------------------------------------------------
void Clear_7219(void)
{
  uint8_t i=dg;
  do
  {
    Send_7219(i,0x00); //for non decoding mode
    // Send_7219(i,0xF); //for decoding mode
  } while (--i);
}
//------------------------------------------------------
void Number_7219(volatile long n)
{
  uint8_t ng=0;
  if(n<0)
  {
    ng=1;
    n*=-1;
  }
  uint8_t i=0;
  do
  {
    Send_7219(++i, n%10);
    n/=10;
  } while(n);
  if(ng)
  {
    Send_7219(i+1, 0x0A);
  }
}

void TickerBar_7219(char line[], int line_lenght, int speed)
{
  Clear_7219();
  int full_length = line_lenght + dg;
  for (int i = 1; i < full_length; i++)
  {
    for (int j = 0; j < dg+1; ++j)
    {
      if (j > i || i - j >= line_lenght)
      {
        Send_7219(j, 0x00);
      }
      else
      {
        Send_7219(j, line[i-j]);
      }
    }
    HAL_Delay(speed);
  }
  Clear_7219();
}
//-------------------------------------------------------
void Init_7219(void)
{
  Send_7219(0x09, 0x00); // decoding mode
  Send_7219(0x0B, dg-1); // number of used digits
  Send_7219(0x0A, 0x05); // light intensity
  Send_7219(0x0C, 0x01);
  Clear_7219();
}
