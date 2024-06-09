################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SHT30/sht30.c 

OBJS += \
./Drivers/SHT30/sht30.o 

C_DEPS += \
./Drivers/SHT30/sht30.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SHT30/%.o Drivers/SHT30/%.su Drivers/SHT30/%.cyclo: ../Drivers/SHT30/%.c Drivers/SHT30/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/SI2C -I../Drivers/OLED -I../Drivers/SHT30 -I../Drivers/SGP30 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-SHT30

clean-Drivers-2f-SHT30:
	-$(RM) ./Drivers/SHT30/sht30.cyclo ./Drivers/SHT30/sht30.d ./Drivers/SHT30/sht30.o ./Drivers/SHT30/sht30.su

.PHONY: clean-Drivers-2f-SHT30

