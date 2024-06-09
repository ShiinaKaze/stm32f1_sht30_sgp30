################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/OLED/oled.c \
../Drivers/OLED/oled_font.c 

OBJS += \
./Drivers/OLED/oled.o \
./Drivers/OLED/oled_font.o 

C_DEPS += \
./Drivers/OLED/oled.d \
./Drivers/OLED/oled_font.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/OLED/%.o Drivers/OLED/%.su Drivers/OLED/%.cyclo: ../Drivers/OLED/%.c Drivers/OLED/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/SI2C -I../Drivers/OLED -I../Drivers/SHT30 -I../Drivers/SGP30 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-OLED

clean-Drivers-2f-OLED:
	-$(RM) ./Drivers/OLED/oled.cyclo ./Drivers/OLED/oled.d ./Drivers/OLED/oled.o ./Drivers/OLED/oled.su ./Drivers/OLED/oled_font.cyclo ./Drivers/OLED/oled_font.d ./Drivers/OLED/oled_font.o ./Drivers/OLED/oled_font.su

.PHONY: clean-Drivers-2f-OLED

