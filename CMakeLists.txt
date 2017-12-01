PROJECT(stm32learn)
cmake_minimum_required(VERSION 2.6)

SET(STM32CubeF1_FW /Users/admin/STM32Cube/Repository/STM32Cube_FW_F1_V1.6.0)

INCLUDE_DIRECTORIES(
    ${STM32CubeF1_FW}/Drivers/CMSIS/Include/
    ${STM32CubeF1_FW}/Drivers/CMSIS/Device/ST/STM32F1xx/Include/
    ${STM32CubeF1_FW}/Drivers/STM32F1xx_HAL_Driver/Inc/
    Inc
    Lib
)
SET(HAL_LIB_SRC ${STM32CubeF1_FW}/Drivers/STM32F1xx_HAL_Driver/Src/)

SET(CMAKE_VERBOSE_MAKEFILE 0)
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_BUILD_TYPE DEBUG)
SET(CMAKE_C_COMPILER "/usr/local/bin/arm-none-eabi-gcc")
SET(CMAKE_LINKER "/usr/local/bin/arm-none-eabi-ld")
SET(CMAKE_OBJCOPY "/usr/local/bin/arm-none-eabi-objcopy")
SET(CMAKE_SIZE "/usr/local/bin/arm-none-eabi-size")

SET(LINK_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F103XB_FLASH.ld)
SET(FAMILY "STM32F103xB")

SET(STARTUP startup_stm32f103xb.s Src/system_stm32f1xx.c)
SET(STARTUP ${STARTUP}
    ${HAL_LIB_SRC}/stm32f1xx_hal.c
    ${HAL_LIB_SRC}/stm32f1xx_hal_cortex.c
    ${HAL_LIB_SRC}/stm32f1xx_hal_dma.c
    ${HAL_LIB_SRC}/stm32f1xx_hal_flash.c
    ${HAL_LIB_SRC}/stm32f1xx_hal_flash_ex.c
    ${HAL_LIB_SRC}/stm32f1xx_hal_gpio.c
    ${HAL_LIB_SRC}/stm32f1xx_hal_i2c.c
    ${HAL_LIB_SRC}/stm32f1xx_hal_rcc.c
    ${HAL_LIB_SRC}/stm32f1xx_hal_spi.c
    ${HAL_LIB_SRC}/stm32f1xx_hal_tim.c
    ${HAL_LIB_SRC}/stm32f1xx_hal_tim_ex.c
    ${HAL_LIB_SRC}/stm32f1xx_hal_uart.c
)
SET_PROPERTY(SOURCE startup_stm32f103xb.s PROPERTY LANGUAGE C)
SET(SRC Src/main.c Src/lcd.c Src/max7219.c Src/eeprom.c Src/stm32f1xx_it.c Src/stm32f1xx_hal_msp.c)

SET(DEBUG_FLAGS "-Og -g")

SET(MCU_FLAGS "-march=armv7-m -mcpu=cortex-m3 -mthumb")
SET(CMAKE_C_FLAGS "${MCU_FLAGS} -fno-common -ffreestanding -fno-builtin -Wall --std=c99  ${DEBUG_FLAGS}")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -nostdlib")
ADD_DEFINITIONS(-D${FAMILY} -DUSE_HAL_DRIVER)
SET(CMAKE_EXE_LINKER_FLAGS "${DEBUG_FLAGS} -nostartfiles -T${LINK_SCRIPT}")
SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")

CMAKE_POLICY(SET CMP0015 NEW)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

ADD_EXECUTABLE(${PROJECT_NAME}.elf ${SRC} ${STARTUP})

ADD_CUSTOM_COMMAND(DEPENDS ${PROJECT_NAME}.elf OUTPUT ${PROJECT_NAME}.hex COMMAND ${CMAKE_OBJCOPY} -Oihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex)
ADD_CUSTOM_COMMAND(DEPENDS ${PROJECT_NAME}.elf OUTPUT ${PROJECT_NAME}.bin COMMAND ${CMAKE_OBJCOPY} -Obinary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)
ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME}.elf POST_BUILD COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf)

ADD_CUSTOM_TARGET(generate_bin ALL DEPENDS ${PROJECT_NAME}.bin)
ADD_CUSTOM_TARGET(generate_hex ALL DEPENDS ${PROJECT_NAME}.hex)

add_custom_target(flash st-flash --reset write ${PROJECT_NAME}.bin 0x8000000)
