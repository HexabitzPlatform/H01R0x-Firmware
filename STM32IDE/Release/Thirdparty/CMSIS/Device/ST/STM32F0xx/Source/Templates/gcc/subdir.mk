################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f030x6.s \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f030x8.s \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f030xc.s \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f031x6.s \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f038xx.s \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f042x6.s \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f048xx.s \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f051x8.s \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f058xx.s \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f070x6.s \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f070xb.s \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f071xb.s \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f072xb.s \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f078xx.s \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f091xc.s \
C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f098xx.s 

OBJS += \
./Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f030x6.o \
./Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f030x8.o \
./Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f030xc.o \
./Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f031x6.o \
./Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f038xx.o \
./Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f042x6.o \
./Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f048xx.o \
./Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f051x8.o \
./Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f058xx.o \
./Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f070x6.o \
./Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f070xb.o \
./Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f071xb.o \
./Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f072xb.o \
./Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f078xx.o \
./Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f091xc.o \
./Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f098xx.o 


# Each subdirectory must supply rules for building sources it contributes
Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f030x6.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f030x6.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -c -I../ -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f030x8.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f030x8.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -c -I../ -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f030xc.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f030xc.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -c -I../ -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f031x6.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f031x6.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -c -I../ -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f038xx.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f038xx.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -c -I../ -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f042x6.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f042x6.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -c -I../ -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f048xx.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f048xx.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -c -I../ -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f051x8.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f051x8.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -c -I../ -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f058xx.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f058xx.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -c -I../ -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f070x6.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f070x6.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -c -I../ -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f070xb.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f070xb.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -c -I../ -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f071xb.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f071xb.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -c -I../ -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f072xb.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f072xb.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -c -I../ -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f078xx.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f078xx.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -c -I../ -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f091xc.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f091xc.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -c -I../ -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f098xx.o: C:/Hexabitz_Github/Firmware/H01R0x-Firmware/Thirdparty/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f098xx.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -c -I../ -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

