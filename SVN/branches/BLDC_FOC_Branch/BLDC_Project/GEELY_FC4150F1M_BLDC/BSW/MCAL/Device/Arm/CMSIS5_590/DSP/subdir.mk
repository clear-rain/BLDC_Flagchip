################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSW/MCAL/Device/Arm/CMSIS5_590/DSP/cmsis_dsp.c 

OBJS += \
./BSW/MCAL/Device/Arm/CMSIS5_590/DSP/cmsis_dsp.o 

C_DEPS += \
./BSW/MCAL/Device/Arm/CMSIS5_590/DSP/cmsis_dsp.d 


# Each subdirectory must supply rules for building sources it contributes
BSW/MCAL/Device/Arm/CMSIS5_590/DSP/%.o: ../BSW/MCAL/Device/Arm/CMSIS5_590/DSP/%.c BSW/MCAL/Device/Arm/CMSIS5_590/DSP/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Wfloat-equal  -g3 -DDEBUG -DECU_ADDRESS_PDM_FL -DTRACE -DSTART_FROM_FLASH -DMCU_FC4150_512K=1 -DMCU_FC4150_2M=2 -DMCU_FC4150_1M_A=3 -DMCU_FC4150_1M_B=4 -DMCU_FC4150_1M_S=5 -DDEVICE_TYPE=MCU_FC4150_1M_B -DECU_ADDRESS_BLDC -DIMU_SPI_COMM -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\CDD\MEMS\Inc" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\ASW" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\NvM\Include" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\CompatibleInfo" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\Device" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\Device\Arm\CMSIS5_590\Core\Include" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\Device\Arm\CMSIS5_590\DSP\Include" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\Device\Arm\CMSIS5_590\DSP\PrivateInclude" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\Driver\Include" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\HwA\Include" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\Startup" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\BSP\Inc" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\CDD\SBC\Inc" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\ECAL\IoHwAb\Inc" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\OS\FreeRTOS\Include" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\OS\FreeRTOS\Sources\portable\GCC\ARM_CM4F" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\AlgorithmLib" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\Com\Include" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\RTE" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\Pdu\Include" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\XCP" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\Can_Hw\Inc" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\Device\Arm\cm4" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\OS\SysView\Config" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\OS\SysView\Sample\FreeRTOSV10.4" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\OS\SysView\SEGGER" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\CDD\MotorDriver\MPQ6533\Inc" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\CDD\MotorDriver\motor_lib" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


