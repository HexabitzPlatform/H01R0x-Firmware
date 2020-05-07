################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/source/diskio.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/source/ff.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/source/ffsystem.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/source/ffsystemFreeRTOS.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/source/ffunicode.c 

OBJS += \
./Thirdparty/Middleware/FatFs/source/diskio.o \
./Thirdparty/Middleware/FatFs/source/ff.o \
./Thirdparty/Middleware/FatFs/source/ffsystem.o \
./Thirdparty/Middleware/FatFs/source/ffsystemFreeRTOS.o \
./Thirdparty/Middleware/FatFs/source/ffunicode.o 

C_DEPS += \
./Thirdparty/Middleware/FatFs/source/diskio.d \
./Thirdparty/Middleware/FatFs/source/ff.d \
./Thirdparty/Middleware/FatFs/source/ffsystem.d \
./Thirdparty/Middleware/FatFs/source/ffsystemFreeRTOS.d \
./Thirdparty/Middleware/FatFs/source/ffunicode.d 


# Each subdirectory must supply rules for building sources it contributes
Thirdparty/Middleware/FatFs/source/diskio.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/source/diskio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/source/diskio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/Middleware/FatFs/source/ff.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/source/ff.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/source/ff.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/Middleware/FatFs/source/ffsystem.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/source/ffsystem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/source/ffsystem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/Middleware/FatFs/source/ffsystemFreeRTOS.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/source/ffsystemFreeRTOS.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/source/ffsystemFreeRTOS.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/Middleware/FatFs/source/ffunicode.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/source/ffunicode.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/source/ffunicode.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

