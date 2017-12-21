#include "mcp4725.h"
//------------------------------------------------
extern I2C_HandleTypeDef hi2c2;

uint8_t mcp4725_address = 0xC0; //0xC4 - other address
uint8_t mcp4725_read = 0x01;
uint8_t mcp4725_dac = 0x40;  // Writes data to the DAC
uint8_t mcp4725_dac_eeprom = 0x60;  // Writes data to the DAC and the EEPROM (persisting the assigned value after reset)

uint8_t buffer[3]={0x00};

//------------------------------------------------
void mcp4725SetVoltage( uint16_t output, char writeEEPROM )
{

  // Clear write bufferfer
  uint32_t i;
  for ( i = 0; i < 3; i++ )
  {
    buffer[i] = 0x00;
  }

  if (writeEEPROM == 1)  // command and config bits  (C2.C1.C0.x.x.PD1.PD0.x)
  {
    buffer[0] = mcp4725_dac_eeprom;
  }
  else
  {
    buffer[0] = mcp4725_dac;
  }
  buffer[1] = (output / 16);       // Upper data bits     (D11.D10.D9.D8.D7.D6.D5.D4)
  buffer[2] = (output % 16) << 4;  // Lower data bits     (D3.D2.D1.D0.x.x.x.x)
  HAL_I2C_Master_Transmit(&hi2c2, mcp4725_address, buffer, 3, 1000);
}
//------------------------------------------------
void mcp4725ReadConfig( uint8_t *status, uint16_t *value )
{
  // if (!_mcp4725Initialised) mcp4725Init();

  // // Clear write buffers
  // uint32_t i;
  // for ( i = 0; i < I2C_BUFSIZE; i++ )
  // {
  //   I2CMasterBuffer[i] = 0x00;
  // }

  // I2CWriteLength = 1;
  // I2CReadLength = 3;
  // I2CMasterBuffer[0] = MCP4725_ADDRESS | MCP4725_READ;
  // i2cEngine();

  // Shift values to create properly formed integers
  // *status = I2CSlaveBuffer[0];
  // *value = ((I2CSlaveBuffer[1] << 4) | (I2CSlaveBuffer[2] >> 4));
}
