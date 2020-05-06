################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/H01R0/startup_stm32f091xc.s 

C_SRCS += \
D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/H01R0/H01R0.c \
D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/H01R0/H01R0_dma.c \
D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/H01R0/H01R0_gpio.c \
D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/H01R0/H01R0_it.c \
D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/H01R0/H01R0_uart.c 

OBJS += \
./H01R0/H01R0.o \
./H01R0/H01R0_dma.o \
./H01R0/H01R0_gpio.o \
./H01R0/H01R0_it.o \
./H01R0/H01R0_uart.o \
./H01R0/startup_stm32f091xc.o 

C_DEPS += \
./H01R0/H01R0.d \
./H01R0/H01R0_dma.d \
./H01R0/H01R0_gpio.d \
./H01R0/H01R0_it.d \
./H01R0/H01R0_uart.d 


# Each subdirectory must supply rules for building sources it contributes
H01R0/H01R0.o: D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/H01R0/H01R0.c
	arm-none-eabi-gcc "$<" -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F091xC -DH01R0 '-D_module=1' -DSTM32F091RCx -DSTM32 -DSTM32F0xx -c -I"D:/Hexabitz Modules for testing 2/H01R0x/BOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/portable/RVDS/ARM_CM0" -I"D:/Hexabitz Modules for testing 2/H01R0x/H01R0" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy" -I"D:/Hexabitz Modules for testing 2/H01R0x/User" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Device/ST/STM32F0xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"H01R0/H01R0.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
H01R0/H01R0_dma.o: D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/H01R0/H01R0_dma.c
	arm-none-eabi-gcc "$<" -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F091xC -DH01R0 '-D_module=1' -DSTM32F091RCx -DSTM32 -DSTM32F0xx -c -I"D:/Hexabitz Modules for testing 2/H01R0x/BOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/portable/RVDS/ARM_CM0" -I"D:/Hexabitz Modules for testing 2/H01R0x/H01R0" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy" -I"D:/Hexabitz Modules for testing 2/H01R0x/User" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Device/ST/STM32F0xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"H01R0/H01R0_dma.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
H01R0/H01R0_gpio.o: D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/H01R0/H01R0_gpio.c
	arm-none-eabi-gcc "$<" -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F091xC -DH01R0 '-D_module=1' -DSTM32F091RCx -DSTM32 -DSTM32F0xx -c -I"D:/Hexabitz Modules for testing 2/H01R0x/BOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/portable/RVDS/ARM_CM0" -I"D:/Hexabitz Modules for testing 2/H01R0x/H01R0" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy" -I"D:/Hexabitz Modules for testing 2/H01R0x/User" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Device/ST/STM32F0xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"H01R0/H01R0_gpio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
H01R0/H01R0_it.o: D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/H01R0/H01R0_it.c
	arm-none-eabi-gcc "$<" -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F091xC -DH01R0 '-D_module=1' -DSTM32F091RCx -DSTM32 -DSTM32F0xx -c -I"D:/Hexabitz Modules for testing 2/H01R0x/BOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/portable/RVDS/ARM_CM0" -I"D:/Hexabitz Modules for testing 2/H01R0x/H01R0" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy" -I"D:/Hexabitz Modules for testing 2/H01R0x/User" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Device/ST/STM32F0xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"H01R0/H01R0_it.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
H01R0/H01R0_uart.o: D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/H01R0/H01R0_uart.c
	arm-none-eabi-gcc "$<" -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F091xC -DH01R0 '-D_module=1' -DSTM32F091RCx -DSTM32 -DSTM32F0xx -c -I"D:/Hexabitz Modules for testing 2/H01R0x/BOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/portable/RVDS/ARM_CM0" -I"D:/Hexabitz Modules for testing 2/H01R0x/H01R0" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy" -I"D:/Hexabitz Modules for testing 2/H01R0x/User" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Device/ST/STM32F0xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"H01R0/H01R0_uart.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
H01R0/startup_stm32f091xc.o: D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/H01R0/startup_stm32f091xc.s
	arm-none-eabi-gcc -g3 -c -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

