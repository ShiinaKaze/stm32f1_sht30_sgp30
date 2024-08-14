################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Components/oled/oled.c \
../Drivers/DSP/Components/oled/oled_font.c 

OBJS += \
./Drivers/DSP/Components/oled/oled.o \
./Drivers/DSP/Components/oled/oled_font.o 

C_DEPS += \
./Drivers/DSP/Components/oled/oled.d \
./Drivers/DSP/Components/oled/oled_font.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Components/oled/%.o Drivers/DSP/Components/oled/%.su Drivers/DSP/Components/oled/%.cyclo: ../Drivers/DSP/Components/oled/%.c Drivers/DSP/Components/oled/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/DSP/Components/oled -I../Drivers/DSP/Components/sht30 -I../Drivers/DSP/Components/sgp30 -I../Drivers/DSP/Common/sw_i2c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-Components-2f-oled

clean-Drivers-2f-DSP-2f-Components-2f-oled:
	-$(RM) ./Drivers/DSP/Components/oled/oled.cyclo ./Drivers/DSP/Components/oled/oled.d ./Drivers/DSP/Components/oled/oled.o ./Drivers/DSP/Components/oled/oled.su ./Drivers/DSP/Components/oled/oled_font.cyclo ./Drivers/DSP/Components/oled/oled_font.d ./Drivers/DSP/Components/oled/oled_font.o ./Drivers/DSP/Components/oled/oled_font.su

.PHONY: clean-Drivers-2f-DSP-2f-Components-2f-oled

