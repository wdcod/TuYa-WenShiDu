################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/User_Lib/Src/Hard.c \
../Core/User_Lib/Src/mcu_api.c \
../Core/User_Lib/Src/oled.c \
../Core/User_Lib/Src/protocol.c \
../Core/User_Lib/Src/system.c 

OBJS += \
./Core/User_Lib/Src/Hard.o \
./Core/User_Lib/Src/mcu_api.o \
./Core/User_Lib/Src/oled.o \
./Core/User_Lib/Src/protocol.o \
./Core/User_Lib/Src/system.o 

C_DEPS += \
./Core/User_Lib/Src/Hard.d \
./Core/User_Lib/Src/mcu_api.d \
./Core/User_Lib/Src/oled.d \
./Core/User_Lib/Src/protocol.d \
./Core/User_Lib/Src/system.d 


# Each subdirectory must supply rules for building sources it contributes
Core/User_Lib/Src/Hard.o: ../Core/User_Lib/Src/Hard.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x6 -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/User_Lib/Inc -I../Core/User_Lib/Src -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/User_Lib/Src/Hard.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/User_Lib/Src/mcu_api.o: ../Core/User_Lib/Src/mcu_api.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x6 -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/User_Lib/Inc -I../Core/User_Lib/Src -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/User_Lib/Src/mcu_api.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/User_Lib/Src/oled.o: ../Core/User_Lib/Src/oled.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x6 -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/User_Lib/Inc -I../Core/User_Lib/Src -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/User_Lib/Src/oled.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/User_Lib/Src/protocol.o: ../Core/User_Lib/Src/protocol.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x6 -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/User_Lib/Inc -I../Core/User_Lib/Src -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/User_Lib/Src/protocol.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/User_Lib/Src/system.o: ../Core/User_Lib/Src/system.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x6 -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/User_Lib/Inc -I../Core/User_Lib/Src -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/User_Lib/Src/system.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

