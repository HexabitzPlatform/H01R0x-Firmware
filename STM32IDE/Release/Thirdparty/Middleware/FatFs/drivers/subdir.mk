################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/drivers/ff_gen_drv.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/drivers/sd_diskio.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/drivers/sdram_diskio.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/drivers/sram_diskio.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/drivers/usbh_diskio.c 

OBJS += \
./Thirdparty/Middleware/FatFs/drivers/ff_gen_drv.o \
./Thirdparty/Middleware/FatFs/drivers/sd_diskio.o \
./Thirdparty/Middleware/FatFs/drivers/sdram_diskio.o \
./Thirdparty/Middleware/FatFs/drivers/sram_diskio.o \
./Thirdparty/Middleware/FatFs/drivers/usbh_diskio.o 

C_DEPS += \
./Thirdparty/Middleware/FatFs/drivers/ff_gen_drv.d \
./Thirdparty/Middleware/FatFs/drivers/sd_diskio.d \
./Thirdparty/Middleware/FatFs/drivers/sdram_diskio.d \
./Thirdparty/Middleware/FatFs/drivers/sram_diskio.d \
./Thirdparty/Middleware/FatFs/drivers/usbh_diskio.d 


# Each subdirectory must supply rules for building sources it contributes
Thirdparty/Middleware/FatFs/drivers/ff_gen_drv.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/drivers/ff_gen_drv.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/drivers/ff_gen_drv.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/Middleware/FatFs/drivers/sd_diskio.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/drivers/sd_diskio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/drivers/sd_diskio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/Middleware/FatFs/drivers/sdram_diskio.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/drivers/sdram_diskio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/drivers/sdram_diskio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/Middleware/FatFs/drivers/sram_diskio.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/drivers/sram_diskio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/drivers/sram_diskio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/Middleware/FatFs/drivers/usbh_diskio.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/Middleware/FatFs/drivers/usbh_diskio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/Middleware/FatFs/drivers/usbh_diskio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

