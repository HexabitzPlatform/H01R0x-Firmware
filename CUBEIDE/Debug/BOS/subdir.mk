################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/BOS/BOS.c \
D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/BOS/BOS_CLI.c \
D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/BOS/BOS_dma.c \
D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/BOS/BOS_eeprom.c \
D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/BOS/BOS_freertos.c 

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
BOS/BOS.o: D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/BOS/BOS.c
	arm-none-eabi-gcc "$<" -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F091xC -DH01R0 '-D_module=1' -DSTM32F091RCx -DSTM32 -DSTM32F0xx -c -I"D:/Hexabitz Modules for testing 2/H01R0x/BOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/portable/RVDS/ARM_CM0" -I"D:/Hexabitz Modules for testing 2/H01R0x/H01R0" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy" -I"D:/Hexabitz Modules for testing 2/H01R0x/User" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Device/ST/STM32F0xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"BOS/BOS.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
BOS/BOS_CLI.o: D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/BOS/BOS_CLI.c
	arm-none-eabi-gcc "$<" -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F091xC -DH01R0 '-D_module=1' -DSTM32F091RCx -DSTM32 -DSTM32F0xx -c -I"D:/Hexabitz Modules for testing 2/H01R0x/BOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/portable/RVDS/ARM_CM0" -I"D:/Hexabitz Modules for testing 2/H01R0x/H01R0" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy" -I"D:/Hexabitz Modules for testing 2/H01R0x/User" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Device/ST/STM32F0xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"BOS/BOS_CLI.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
BOS/BOS_dma.o: D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/BOS/BOS_dma.c
	arm-none-eabi-gcc "$<" -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F091xC -DH01R0 '-D_module=1' -DSTM32F091RCx -DSTM32 -DSTM32F0xx -c -I"D:/Hexabitz Modules for testing 2/H01R0x/BOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/portable/RVDS/ARM_CM0" -I"D:/Hexabitz Modules for testing 2/H01R0x/H01R0" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy" -I"D:/Hexabitz Modules for testing 2/H01R0x/User" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Device/ST/STM32F0xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"BOS/BOS_dma.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
BOS/BOS_eeprom.o: D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/BOS/BOS_eeprom.c
	arm-none-eabi-gcc "$<" -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F091xC -DH01R0 '-D_module=1' -DSTM32F091RCx -DSTM32 -DSTM32F0xx -c -I"D:/Hexabitz Modules for testing 2/H01R0x/BOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/portable/RVDS/ARM_CM0" -I"D:/Hexabitz Modules for testing 2/H01R0x/H01R0" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy" -I"D:/Hexabitz Modules for testing 2/H01R0x/User" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Device/ST/STM32F0xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"BOS/BOS_eeprom.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
BOS/BOS_freertos.o: D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/BOS/BOS_freertos.c
	arm-none-eabi-gcc "$<" -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F091xC -DH01R0 '-D_module=1' -DSTM32F091RCx -DSTM32 -DSTM32F0xx -c -I"D:/Hexabitz Modules for testing 2/H01R0x/BOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/portable/RVDS/ARM_CM0" -I"D:/Hexabitz Modules for testing 2/H01R0x/H01R0" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy" -I"D:/Hexabitz Modules for testing 2/H01R0x/User" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Device/ST/STM32F0xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"BOS/BOS_freertos.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

