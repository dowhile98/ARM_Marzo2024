################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Components/button/button.c 

OBJS += \
./Components/button/button.o 

C_DEPS += \
./Components/button/button.d 


# Each subdirectory must supply rules for building sources it contributes
Components/button/%.o Components/button/%.su Components/button/%.cyclo: ../Components/button/%.c Components/button/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F407xx -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/TRABAJO/UMAKER/CURSOS/ARM - NUCLEO/ARM_Marzo2024/LCD/Components/lcd" -I"D:/TRABAJO/UMAKER/CURSOS/ARM - NUCLEO/ARM_Marzo2024/LCD/Components/button" -I"D:/TRABAJO/UMAKER/CURSOS/ARM - NUCLEO/ARM_Marzo2024/LCD/Components/delay" -I"D:/TRABAJO/UMAKER/CURSOS/ARM - NUCLEO/ARM_Marzo2024/LCD/HVAC_App/Inc" -I"D:/TRABAJO/UMAKER/CURSOS/ARM - NUCLEO/ARM_Marzo2024/LCD/Drivers/CMSIS/Include" -I"D:/TRABAJO/UMAKER/CURSOS/ARM - NUCLEO/ARM_Marzo2024/LCD/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/TRABAJO/UMAKER/CURSOS/ARM - NUCLEO/ARM_Marzo2024/LCD/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Components-2f-button

clean-Components-2f-button:
	-$(RM) ./Components/button/button.cyclo ./Components/button/button.d ./Components/button/button.o ./Components/button/button.su

.PHONY: clean-Components-2f-button

