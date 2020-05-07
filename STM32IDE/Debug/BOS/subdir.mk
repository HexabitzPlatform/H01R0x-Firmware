################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/BOS/BOS.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/BOS/BOS_CLI.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/BOS/BOS_dma.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/BOS/BOS_eeprom.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/BOS/BOS_freertos.c 

OBJS += \
./BOS/BOS.o \
./BOS/BOS_CLI.o \
./BOS/BOS_dma.o \
./BOS/BOS_eeprom.o \
./BOS/BOS_freertos.o 

C_DEPS += \
./BOS/BOS.d \
./BOS/BOS_CLI.d \
./BOS/BOS_dma.d \
./BOS/BOS_eeprom.d \
./BOS/BOS_freertos.d 


# Each subdirectory must supply rules for building sources it contributes
BOS/BOS.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/BOS/BOS.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DDEBUG -DSTM32F091xB -DH01R0 '-D_module=1' -DSTM32F091xC -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../H01R0 -I../../BOS -I../../User -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"BOS/BOS.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
BOS/BOS_CLI.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/BOS/BOS_CLI.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DDEBUG -DSTM32F091xB -DH01R0 '-D_module=1' -DSTM32F091xC -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../H01R0 -I../../BOS -I../../User -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"BOS/BOS_CLI.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
BOS/BOS_dma.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/BOS/BOS_dma.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DDEBUG -DSTM32F091xB -DH01R0 '-D_module=1' -DSTM32F091xC -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../H01R0 -I../../BOS -I../../User -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"BOS/BOS_dma.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
BOS/BOS_eeprom.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/BOS/BOS_eeprom.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DDEBUG -DSTM32F091xB -DH01R0 '-D_module=1' -DSTM32F091xC -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../H01R0 -I../../BOS -I../../User -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"BOS/BOS_eeprom.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
BOS/BOS_freertos.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/BOS/BOS_freertos.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DDEBUG -DSTM32F091xB -DH01R0 '-D_module=1' -DSTM32F091xC -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../H01R0 -I../../BOS -I../../User -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"BOS/BOS_freertos.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

