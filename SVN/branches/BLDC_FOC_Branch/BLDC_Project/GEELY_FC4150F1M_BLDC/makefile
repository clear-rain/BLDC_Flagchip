################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include RTE/subdir.mk
-include BSW/XCP/subdir.mk
-include BSW/Pdu/Source/subdir.mk
-include BSW/OS/SysView/Sample/FreeRTOSV10.4/Config/Cortex-M/subdir.mk
-include BSW/OS/SysView/Sample/FreeRTOSV10.4/subdir.mk
-include BSW/OS/SysView/SEGGER/Syscalls/subdir.mk
-include BSW/OS/SysView/SEGGER/subdir.mk
-include BSW/OS/FreeRTOS/Sources/portable/MemMang/subdir.mk
-include BSW/OS/FreeRTOS/Sources/portable/GCC/ARM_CM4F/subdir.mk
-include BSW/OS/FreeRTOS/Sources/subdir.mk
-include BSW/NvM/Source/subdir.mk
-include BSW/MCAL/Startup/subdir.mk
-include BSW/MCAL/Driver/Source/subdir.mk
-include BSW/MCAL/Device/FC/fclib/subdir.mk
-include BSW/MCAL/Device/Arm/CMSIS5_590/DSP/subdir.mk
-include BSW/MCAL/BSP/Src/subdir.mk
-include BSW/ECAL/IoHwAb/Src/subdir.mk
-include BSW/CompatibleInfo/subdir.mk
-include BSW/Com/Source/subdir.mk
-include BSW/Can_Hw/Src/subdir.mk
-include BSW/CDD/SBC/Src/subdir.mk
-include BSW/CDD/MotorDriver/motor_lib/subdir.mk
-include BSW/CDD/MotorDriver/MPQ6533/Src/subdir.mk
-include BSW/CDD/MEMS/Src/subdir.mk
-include BSW/AlgorithmLib/subdir.mk
-include ASW/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := BLDC_PDM_BLDC
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
BLDC_PDM_BLDC.hex \

SECONDARY_SIZE += \
BLDC_PDM_BLDC.siz \


# All Target
all: main-build

# Main-build Target
main-build: BLDC_PDM_BLDC.elf secondary-outputs

# Tool invocations
BLDC_PDM_BLDC.elf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU Arm Cross C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Wfloat-equal  -g3 -T "E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\Startup\FC4150_1M_B_flash.ld" -nostartfiles -Xlinker --gc-sections -L"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\Startup" -L"E:\Code\BLDC_POD\SourceCode\branches\BLDC_FOC_Branch\BLDC_Project\BSW\MCAL\_gcc_lib" -Xlinker --print-memory-usage -Wl,-Map,"BLDC_PDM_BLDC.map" --specs=nosys.specs -Xlinker --print-memory-usage -o "BLDC_PDM_BLDC.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

BLDC_PDM_BLDC.hex: BLDC_PDM_BLDC.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU Arm Cross Create Flash Image'
	arm-none-eabi-objcopy -O ihex "BLDC_PDM_BLDC.elf"  "BLDC_PDM_BLDC.hex"
	@echo 'Finished building: $@'
	@echo ' '

BLDC_PDM_BLDC.siz: BLDC_PDM_BLDC.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU Arm Cross Print Size'
	arm-none-eabi-size --format=berkeley "BLDC_PDM_BLDC.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(C_DEPS)$(CPP_DEPS) BLDC_PDM_BLDC.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
