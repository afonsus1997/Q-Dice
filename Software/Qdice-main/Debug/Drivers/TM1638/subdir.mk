################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/TM1638/example.c \
../Drivers/TM1638/tm1638lib.c 

C_DEPS += \
./Drivers/TM1638/example.d \
./Drivers/TM1638/tm1638lib.d 

OBJS += \
./Drivers/TM1638/example.o \
./Drivers/TM1638/tm1638lib.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/TM1638/example.o: ../Drivers/TM1638/example.c Drivers/TM1638/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L053xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I../Drivers/TM1638 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/TM1638/example.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/TM1638/tm1638lib.o: ../Drivers/TM1638/tm1638lib.c Drivers/TM1638/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L053xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I../Drivers/TM1638 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/TM1638/tm1638lib.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

