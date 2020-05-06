################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/User/main.c 

OBJS += \
./User/main.o 

C_DEPS += \
./User/main.d 


# Each subdirectory must supply rules for building sources it contributes
User/main.o: D:/Hexabitz\ Modules\ for\ testing\ 2/H01R0x/User/main.c
	arm-none-eabi-gcc "$<" -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F091xC -DH01R0 '-D_module=1' -DSTM32F091RCx -DSTM32 -DSTM32F0xx -c -I"D:/Hexabitz Modules for testing 2/H01R0x/BOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/Middleware/FreeRTOS/Source/portable/RVDS/ARM_CM0" -I"D:/Hexabitz Modules for testing 2/H01R0x/H01R0" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy" -I"D:/Hexabitz Modules for testing 2/H01R0x/User" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/STM32F0xx_HAL_Driver/Inc" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Include" -I"D:/Hexabitz Modules for testing 2/H01R0x/Thirdparty/CMSIS/Device/ST/STM32F0xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"User/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

