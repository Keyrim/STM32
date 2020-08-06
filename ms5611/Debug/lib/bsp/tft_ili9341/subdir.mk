################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/bsp/tft_ili9341/stm32f1_fonts.c \
../lib/bsp/tft_ili9341/stm32f1_ili9341.c \
../lib/bsp/tft_ili9341/stm32f1_xpt2046.c 

OBJS += \
./lib/bsp/tft_ili9341/stm32f1_fonts.o \
./lib/bsp/tft_ili9341/stm32f1_ili9341.o \
./lib/bsp/tft_ili9341/stm32f1_xpt2046.o 

C_DEPS += \
./lib/bsp/tft_ili9341/stm32f1_fonts.d \
./lib/bsp/tft_ili9341/stm32f1_ili9341.d \
./lib/bsp/tft_ili9341/stm32f1_xpt2046.d 


# Each subdirectory must supply rules for building sources it contributes
lib/bsp/tft_ili9341/%.o: ../lib/bsp/tft_ili9341/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32F1 -DNUCLEO_F103RB -DSTM32F103RBTx -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -I"D:/Git Hub/STM32/ms5611/lib/bsp" -I"D:/Git Hub/STM32/ms5611/lib/bsp/VL53L0X" -I"D:/Git Hub/STM32/ms5611/lib/bsp/MPU6050" -I"D:/Git Hub/STM32/ms5611/lib/bsp/iks01a1" -I"D:/Git Hub/STM32/ms5611/lib/bsp/iks01a1/Common" -I"D:/Git Hub/STM32/ms5611/lib/bsp/iks01a1/hts221" -I"D:/Git Hub/STM32/ms5611/lib/bsp/iks01a1/lis3mdl" -I"D:/Git Hub/STM32/ms5611/lib/bsp/iks01a1/lps22hb" -I"D:/Git Hub/STM32/ms5611/lib/bsp/iks01a1/lps25hb" -I"D:/Git Hub/STM32/ms5611/lib/bsp/iks01a1/lsm6ds0" -I"D:/Git Hub/STM32/ms5611/lib/bsp/iks01a1/lsm6ds3" -I"D:/Git Hub/STM32/ms5611/lib/bsp/tft_ili9341" -I"D:/Git Hub/STM32/ms5611/lib/bsp/tft_pcd8544" -I"D:/Git Hub/STM32/ms5611/lib/bsp/MCP23S17" -I"D:/Git Hub/STM32/ms5611/lib/hal/inc" -I"D:/Git Hub/STM32/ms5611/lib/bsp/Common" -I"D:/Git Hub/STM32/ms5611/lib/bsp/lcd2x16" -I"D:/Git Hub/STM32/ms5611/lib/bsp/MLX90614" -I"D:/Git Hub/STM32/ms5611/lib/bsp/MatrixKeyboard" -I"D:/Git Hub/STM32/ms5611/lib/bsp/MatrixLed" -I"D:/Git Hub/STM32/ms5611/lib/CMSIS/core" -I"D:/Git Hub/STM32/ms5611/lib/CMSIS/device" -I"D:/Git Hub/STM32/ms5611/lib/middleware/FatFs" -I"D:/Git Hub/STM32/ms5611/lib/middleware/FatFs/src" -I"D:/Git Hub/STM32/ms5611/lib/middleware/FatFs/src/drivers" -I"D:/Git Hub/STM32/ms5611/appli"  -Og -g3 -Wall -Wextra -Wconversion -fmessage-length=0 -ffunction-sections -fdata-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


