################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSW/MCAL/BSP/Src/BspAdc.c \
../BSW/MCAL/BSP/Src/BspAontimer.c \
../BSW/MCAL/BSP/Src/BspCan.c \
../BSW/MCAL/BSP/Src/BspClock.c \
../BSW/MCAL/BSP/Src/BspDma.c \
../BSW/MCAL/BSP/Src/BspFlash.c \
../BSW/MCAL/BSP/Src/BspFtuCounter.c \
../BSW/MCAL/BSP/Src/BspFtuIcu.c \
../BSW/MCAL/BSP/Src/BspFtuPwm.c \
../BSW/MCAL/BSP/Src/BspGpio.c \
../BSW/MCAL/BSP/Src/BspIic.c \
../BSW/MCAL/BSP/Src/BspInterrupt.c \
../BSW/MCAL/BSP/Src/BspPtimer.c \
../BSW/MCAL/BSP/Src/BspRtc.c \
../BSW/MCAL/BSP/Src/BspSmc.c \
../BSW/MCAL/BSP/Src/BspSpi.c \
../BSW/MCAL/BSP/Src/BspWdg.c 

OBJS += \
./BSW/MCAL/BSP/Src/BspAdc.o \
./BSW/MCAL/BSP/Src/BspAontimer.o \
./BSW/MCAL/BSP/Src/BspCan.o \
./BSW/MCAL/BSP/Src/BspClock.o \
./BSW/MCAL/BSP/Src/BspDma.o \
./BSW/MCAL/BSP/Src/BspFlash.o \
./BSW/MCAL/BSP/Src/BspFtuCounter.o \
./BSW/MCAL/BSP/Src/BspFtuIcu.o \
./BSW/MCAL/BSP/Src/BspFtuPwm.o \
./BSW/MCAL/BSP/Src/BspGpio.o \
./BSW/MCAL/BSP/Src/BspIic.o \
./BSW/MCAL/BSP/Src/BspInterrupt.o \
./BSW/MCAL/BSP/Src/BspPtimer.o \
./BSW/MCAL/BSP/Src/BspRtc.o \
./BSW/MCAL/BSP/Src/BspSmc.o \
./BSW/MCAL/BSP/Src/BspSpi.o \
./BSW/MCAL/BSP/Src/BspWdg.o 

C_DEPS += \
./BSW/MCAL/BSP/Src/BspAdc.d \
./BSW/MCAL/BSP/Src/BspAontimer.d \
./BSW/MCAL/BSP/Src/BspCan.d \
./BSW/MCAL/BSP/Src/BspClock.d \
./BSW/MCAL/BSP/Src/BspDma.d \
./BSW/MCAL/BSP/Src/BspFlash.d \
./BSW/MCAL/BSP/Src/BspFtuCounter.d \
./BSW/MCAL/BSP/Src/BspFtuIcu.d \
./BSW/MCAL/BSP/Src/BspFtuPwm.d \
./BSW/MCAL/BSP/Src/BspGpio.d \
./BSW/MCAL/BSP/Src/BspIic.d \
./BSW/MCAL/BSP/Src/BspInterrupt.d \
./BSW/MCAL/BSP/Src/BspPtimer.d \
./BSW/MCAL/BSP/Src/BspRtc.d \
./BSW/MCAL/BSP/Src/BspSmc.d \
./BSW/MCAL/BSP/Src/BspSpi.d \
./BSW/MCAL/BSP/Src/BspWdg.d 


# Each subdirectory must supply rules for building sources it contributes
BSW/MCAL/BSP/Src/%.o: ../BSW/MCAL/BSP/Src/%.c BSW/MCAL/BSP/Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Wfloat-equal  -g3 -DDEBUG -DECU_ADDRESS_PDM_FL -DTRACE -DSTART_FROM_FLASH -DMCU_FC4150_512K=1 -DMCU_FC4150_2M=2 -DMCU_FC4150_1M_A=3 -DMCU_FC4150_1M_B=4 -DMCU_FC4150_1M_S=5 -DDEVICE_TYPE=MCU_FC4150_1M_B -DECU_ADDRESS_BLDC -DIMU_SPI_COMM -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\CDD\MEMS\Inc" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\ASW" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\NvM\Include" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\CompatibleInfo" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\Device" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\Device\Arm\CMSIS5_590\Core\Include" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\Device\Arm\CMSIS5_590\DSP\Include" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\Device\Arm\CMSIS5_590\DSP\PrivateInclude" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\Driver\Include" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\HwA\Include" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\Startup" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\BSP\Inc" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\CDD\SBC\Inc" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\ECAL\IoHwAb\Inc" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\OS\FreeRTOS\Include" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\OS\FreeRTOS\Sources\portable\GCC\ARM_CM4F" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\AlgorithmLib" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\Com\Include" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\RTE" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\Pdu\Include" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\XCP" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\Can_Hw\Inc" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\Device\Arm\cm4" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\OS\SysView\Config" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\OS\SysView\Sample\FreeRTOSV10.4" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\OS\SysView\SEGGER" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\CDD\MotorDriver\MPQ6533\Inc" -I"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\CDD\MotorDriver\motor_lib" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


