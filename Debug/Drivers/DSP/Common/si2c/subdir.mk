################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Common/si2c/si2c.c 

OBJS += \
./Drivers/DSP/Common/si2c/si2c.o 

C_DEPS += \
./Drivers/DSP/Common/si2c/si2c.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Common/si2c/%.o Drivers/DSP/Common/si2c/%.su Drivers/DSP/Common/si2c/%.cyclo: ../Drivers/DSP/Common/si2c/%.c Drivers/DSP/Common/si2c/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/DSP/Components/oled -I../Drivers/DSP/Components/sht30 -I../Drivers/DSP/Components/sgp30 -I../Drivers/DSP/Common/si2c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-Common-2f-si2c

clean-Drivers-2f-DSP-2f-Common-2f-si2c:
	-$(RM) ./Drivers/DSP/Common/si2c/si2c.cyclo ./Drivers/DSP/Common/si2c/si2c.d ./Drivers/DSP/Common/si2c/si2c.o ./Drivers/DSP/Common/si2c/si2c.su

.PHONY: clean-Drivers-2f-DSP-2f-Common-2f-si2c

