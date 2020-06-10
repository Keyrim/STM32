################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/hal/src/Legacy/stm32f1xx_hal_can.c 

OBJS += \
./lib/hal/src/Legacy/stm32f1xx_hal_can.o 

C_DEPS += \
./lib/hal/src/Legacy/stm32f1xx_hal_can.d 


# Each subdirectory must supply rules for building sources it contributes
lib/hal/src/Legacy/%.o: ../lib/hal/src/Legacy/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32F1 -DNUCLEO_F103RB -DSTM32F103RBTx -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/bsp" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/bsp/VL53L0X" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/bsp/MPU6050" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/bsp/iks01a1" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/bsp/iks01a1/Common" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/bsp/iks01a1/hts221" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/bsp/iks01a1/lis3mdl" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/bsp/iks01a1/lps22hb" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/bsp/iks01a1/lps25hb" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/bsp/iks01a1/lsm6ds0" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/bsp/iks01a1/lsm6ds3" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/bsp/tft_ili9341" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/bsp/tft_pcd8544" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/bsp/MCP23S17" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/hal/inc" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/bsp/Common" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/bsp/lcd2x16" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/bsp/MLX90614" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/bsp/MatrixKeyboard" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/bsp/MatrixLed" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/CMSIS/core" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/CMSIS/device" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/middleware/FatFs" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/middleware/FatFs/src" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/lib/middleware/FatFs/src/drivers" -I"C:/Users/Theo/Documents/STM32/projet-f103_lecture_ppm/appli"  -Og -g3 -Wall -Wextra -Wconversion -fmessage-length=0 -ffunction-sections -fdata-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

