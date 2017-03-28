################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/syscalls.c \
../src/system_stm32f0xx.c 

CPP_SRCS += \
../src/Hbridge.cpp 

OBJS += \
./src/Hbridge.o \
./src/main.o \
./src/syscalls.o \
./src/system_stm32f0xx.o 

C_DEPS += \
./src/main.d \
./src/syscalls.d \
./src/system_stm32f0xx.d 

CPP_DEPS += \
./src/Hbridge.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo %cd%
	arm-none-eabi-g++ -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DSTM32F0 -DSTM32F030CCTx -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F030xC -I"C:/Users/Michal/workspace/2WD_mobile_robot_V1/inc" -I"C:/Users/Michal/workspace/2WD_mobile_robot_V1/CMSIS/core" -I"C:/Users/Michal/workspace/2WD_mobile_robot_V1/CMSIS/device" -I"C:/Users/Michal/workspace/2WD_mobile_robot_V1/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DSTM32F0 -DSTM32F030CCTx -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F030xC -I"C:/Users/Michal/workspace/2WD_mobile_robot_V1/inc" -I"C:/Users/Michal/workspace/2WD_mobile_robot_V1/CMSIS/core" -I"C:/Users/Michal/workspace/2WD_mobile_robot_V1/CMSIS/device" -I"C:/Users/Michal/workspace/2WD_mobile_robot_V1/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


