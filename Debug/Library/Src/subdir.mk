################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/Src/dht.c \
../Library/Src/i2c-lcd.c \
../Library/Src/i2c_lcd_driver.c \
../Library/Src/uart_drv.c 

OBJS += \
./Library/Src/dht.o \
./Library/Src/i2c-lcd.o \
./Library/Src/i2c_lcd_driver.o \
./Library/Src/uart_drv.o 

C_DEPS += \
./Library/Src/dht.d \
./Library/Src/i2c-lcd.d \
./Library/Src/i2c_lcd_driver.d \
./Library/Src/uart_drv.d 


# Each subdirectory must supply rules for building sources it contributes
Library/Src/%.o Library/Src/%.su Library/Src/%.cyclo: ../Library/Src/%.c Library/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/hp/Desktop/AK_DRIVERs/Library" -I"C:/Users/hp/Desktop/AK_DRIVERs/Library/Src" -I"C:/Users/hp/Desktop/AK_DRIVERs/Library/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Library-2f-Src

clean-Library-2f-Src:
	-$(RM) ./Library/Src/dht.cyclo ./Library/Src/dht.d ./Library/Src/dht.o ./Library/Src/dht.su ./Library/Src/i2c-lcd.cyclo ./Library/Src/i2c-lcd.d ./Library/Src/i2c-lcd.o ./Library/Src/i2c-lcd.su ./Library/Src/i2c_lcd_driver.cyclo ./Library/Src/i2c_lcd_driver.d ./Library/Src/i2c_lcd_driver.o ./Library/Src/i2c_lcd_driver.su ./Library/Src/uart_drv.cyclo ./Library/Src/uart_drv.d ./Library/Src/uart_drv.o ./Library/Src/uart_drv.su

.PHONY: clean-Library-2f-Src

