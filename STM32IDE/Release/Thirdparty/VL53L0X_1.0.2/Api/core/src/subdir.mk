################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_calibration.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_core.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_ranging.c \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_strings.c 

OBJS += \
./Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api.o \
./Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_calibration.o \
./Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_core.o \
./Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_ranging.o \
./Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_strings.o 

C_DEPS += \
./Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api.d \
./Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_calibration.d \
./Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_core.d \
./Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_ranging.d \
./Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_strings.d 


# Each subdirectory must supply rules for building sources it contributes
Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_calibration.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_calibration.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_calibration.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_core.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_core.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_core.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_ranging.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_ranging.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_ranging.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_strings.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_strings.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DSTM32F091xC -DUSE_HAL_DRIVER -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Thirdparty/VL53L0X_1.0.2/Api/core/src/vl53l0x_api_strings.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

