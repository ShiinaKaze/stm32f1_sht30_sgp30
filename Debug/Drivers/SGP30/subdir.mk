################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SGP30/sgp30.c 

OBJS += \
./Drivers/SGP30/sgp30.o 

C_DEPS += \
./Drivers/SGP30/sgp30.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SGP30/%.o Drivers/SGP30/%.su Drivers/SGP30/%.cyclo: ../Drivers/SGP30/%.c Drivers/SGP30/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/SI2C -I../Drivers/OLED -I../Drivers/SHT30 -I../Drivers/SGP30 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-SGP30

clean-Drivers-2f-SGP30:
	-$(RM) ./Drivers/SGP30/sgp30.cyclo ./Drivers/SGP30/sgp30.d ./Drivers/SGP30/sgp30.o ./Drivers/SGP30/sgp30.su

.PHONY: clean-Drivers-2f-SGP30

