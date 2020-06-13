################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
D:/Hexabitz/Hexabitz\ Modules\ firmware/H01R0xx/H01R0/gcc/startup_stm32f091xc.s 

C_SRCS += \
D:/Hexabitz/Hexabitz\ Modules\ firmware/H01R0xx/H01R0/H01R0.c \
D:/Hexabitz/Hexabitz\ Modules\ firmware/H01R0xx/H01R0/H01R0_dma.c \
D:/Hexabitz/Hexabitz\ Modules\ firmware/H01R0xx/H01R0/H01R0_gpio.c \
D:/Hexabitz/Hexabitz\ Modules\ firmware/H01R0xx/H01R0/H01R0_it.c \
D:/Hexabitz/Hexabitz\ Modules\ firmware/H01R0xx/H01R0/H01R0_uart.c 

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
H01R0/H01R0.o: D:/Hexabitz/Hexabitz\ Modules\ firmware/H01R0xx/H01R0/H01R0.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DDEBUG -DSTM32F091xB -DH01R0 -DSTM32F091xC '-D_module=1' -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../H01R0 -I../../BOS -I../../User -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"H01R0/H01R0.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
H01R0/H01R0_dma.o: D:/Hexabitz/Hexabitz\ Modules\ firmware/H01R0xx/H01R0/H01R0_dma.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DDEBUG -DSTM32F091xB -DH01R0 -DSTM32F091xC '-D_module=1' -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../H01R0 -I../../BOS -I../../User -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"H01R0/H01R0_dma.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
H01R0/H01R0_gpio.o: D:/Hexabitz/Hexabitz\ Modules\ firmware/H01R0xx/H01R0/H01R0_gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DDEBUG -DSTM32F091xB -DH01R0 -DSTM32F091xC '-D_module=1' -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../H01R0 -I../../BOS -I../../User -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"H01R0/H01R0_gpio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
H01R0/H01R0_it.o: D:/Hexabitz/Hexabitz\ Modules\ firmware/H01R0xx/H01R0/H01R0_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DDEBUG -DSTM32F091xB -DH01R0 -DSTM32F091xC '-D_module=1' -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../H01R0 -I../../BOS -I../../User -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"H01R0/H01R0_it.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
H01R0/H01R0_uart.o: D:/Hexabitz/Hexabitz\ Modules\ firmware/H01R0xx/H01R0/H01R0_uart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DDEBUG -DSTM32F091xB -DH01R0 -DSTM32F091xC '-D_module=1' -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../H01R0 -I../../BOS -I../../User -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"H01R0/H01R0_uart.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
H01R0/startup_stm32f091xc.o: D:/Hexabitz/Hexabitz\ Modules\ firmware/H01R0xx/H01R0/gcc/startup_stm32f091xc.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -g '-D_module=2' -c -I../ -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

