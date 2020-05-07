################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/option/cc932.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/option/cc936.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/option/cc949.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/option/cc950.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/option/ccsbcs.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/option/syscall.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/option/unicode.c 

OBJS += \
./Thirdparty/Middleware/FatFs/option/cc932.o \
./Thirdparty/Middleware/FatFs/option/cc936.o \
./Thirdparty/Middleware/FatFs/option/cc949.o \
./Thirdparty/Middleware/FatFs/option/cc950.o \
./Thirdparty/Middleware/FatFs/option/ccsbcs.o \
./Thirdparty/Middleware/FatFs/option/syscall.o \
./Thirdparty/Middleware/FatFs/option/unicode.o 

C_DEPS += \
./Thirdparty/Middleware/FatFs/option/cc932.d \
./Thirdparty/Middleware/FatFs/option/cc936.d \
./Thirdparty/Middleware/FatFs/option/cc949.d \
./Thirdparty/Middleware/FatFs/option/cc950.d \
./Thirdparty/Middleware/FatFs/option/ccsbcs.d \
./Thirdparty/Middleware/FatFs/option/syscall.d \
./Thirdparty/Middleware/FatFs/option/unicode.d 


# Each subdirectory must supply rules for building sources it contributes
Thirdparty/Middleware/FatFs/option/cc932.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/option/cc932.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/option/cc932.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/Middleware/FatFs/option/cc936.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/option/cc936.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/option/cc936.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/Middleware/FatFs/option/cc949.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/option/cc949.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/option/cc949.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/Middleware/FatFs/option/cc950.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/option/cc950.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/option/cc950.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/Middleware/FatFs/option/ccsbcs.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/option/ccsbcs.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/option/ccsbcs.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/Middleware/FatFs/option/syscall.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/option/syscall.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/option/syscall.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/Middleware/FatFs/option/unicode.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/option/unicode.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/option/unicode.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

