################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SI2C/si2c.c 

OBJS += \
./Drivers/SI2C/si2c.o 

C_DEPS += \
./Drivers/SI2C/si2c.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SI2C/%.o Drivers/SI2C/%.su Drivers/SI2C/%.cyclo: ../Drivers/SI2C/%.c Drivers/SI2C/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/SI2C -I../Drivers/OLED -I../Drivers/SHT30 -I../Drivers/SGP30 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-SI2C

clean-Drivers-2f-SI2C:
	-$(RM) ./Drivers/SI2C/si2c.cyclo ./Drivers/SI2C/si2c.d ./Drivers/SI2C/si2c.o ./Drivers/SI2C/si2c.su

.PHONY: clean-Drivers-2f-SI2C

