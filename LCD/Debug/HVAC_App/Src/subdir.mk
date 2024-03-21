################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HVAC_App/Src/hvac_ll_driver.c 

OBJS += \
./HVAC_App/Src/hvac_ll_driver.o 

C_DEPS += \
./HVAC_App/Src/hvac_ll_driver.d 


# Each subdirectory must supply rules for building sources it contributes
HVAC_App/Src/%.o HVAC_App/Src/%.su HVAC_App/Src/%.cyclo: ../HVAC_App/Src/%.c HVAC_App/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F407xx -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/TRABAJO/UMAKER/CURSOS/ARM - NUCLEO/ARM_Marzo2024/LCD/Components/lcd" -I"D:/TRABAJO/UMAKER/CURSOS/ARM - NUCLEO/ARM_Marzo2024/LCD/Components/button" -I"D:/TRABAJO/UMAKER/CURSOS/ARM - NUCLEO/ARM_Marzo2024/LCD/Components/delay" -I"D:/TRABAJO/UMAKER/CURSOS/ARM - NUCLEO/ARM_Marzo2024/LCD/HVAC_App/Inc" -I"D:/TRABAJO/UMAKER/CURSOS/ARM - NUCLEO/ARM_Marzo2024/LCD/Drivers/CMSIS/Include" -I"D:/TRABAJO/UMAKER/CURSOS/ARM - NUCLEO/ARM_Marzo2024/LCD/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/TRABAJO/UMAKER/CURSOS/ARM - NUCLEO/ARM_Marzo2024/LCD/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-HVAC_App-2f-Src

clean-HVAC_App-2f-Src:
	-$(RM) ./HVAC_App/Src/hvac_ll_driver.cyclo ./HVAC_App/Src/hvac_ll_driver.d ./HVAC_App/Src/hvac_ll_driver.o ./HVAC_App/Src/hvac_ll_driver.su

.PHONY: clean-HVAC_App-2f-Src
