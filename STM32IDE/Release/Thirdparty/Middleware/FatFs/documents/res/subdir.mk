################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/documents/res/app1.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/documents/res/app2.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/documents/res/app3.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/documents/res/app4.c 

OBJS += \
./Thirdparty/Middleware/FatFs/documents/res/app1.o \
./Thirdparty/Middleware/FatFs/documents/res/app2.o \
./Thirdparty/Middleware/FatFs/documents/res/app3.o \
./Thirdparty/Middleware/FatFs/documents/res/app4.o 

C_DEPS += \
./Thirdparty/Middleware/FatFs/documents/res/app1.d \
./Thirdparty/Middleware/FatFs/documents/res/app2.d \
./Thirdparty/Middleware/FatFs/documents/res/app3.d \
./Thirdparty/Middleware/FatFs/documents/res/app4.d 


# Each subdirectory must supply rules for building sources it contributes
Thirdparty/Middleware/FatFs/documents/res/app1.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/documents/res/app1.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/documents/res/app1.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/Middleware/FatFs/documents/res/app2.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/documents/res/app2.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/documents/res/app2.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/Middleware/FatFs/documents/res/app3.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/documents/res/app3.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/documents/res/app3.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/Middleware/FatFs/documents/res/app4.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/documents/res/app4.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/documents/res/app4.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

