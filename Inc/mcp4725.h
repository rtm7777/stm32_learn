#ifndef _MCP4725_H_
#define _MCP4725_H_

#include "stm32f1xx_hal.h"

void mcp4725SetVoltage( uint16_t output, char writeEEPROM );
void mcp4725ReadConfig( uint8_t *status, uint16_t *value );

#endif