################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include arduino/core/subdir.mk
-include Libraries/arduinounit-master/src/utility/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
arduino.ar \

ELF += \
TestXTable.elf \

EEP += \
TestXTable.eep \

FLASH_IMAGE += \
TestXTable.hex \


# All Target
all: TestXTable

# Tool invocations
TestXTable: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"/opt/arduino-1.6.5/hardware/tools/avr/bin/avr-size" -A "/home/arduinodev/workspace/TestXTable/Release/TestXTable.elf"
	@echo 'Finished building target: $@'
	@echo ' '

arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"/opt/arduino-1.6.5/hardware/tools/avr/bin/avr-ar" rcs  "/home/arduinodev/workspace/TestXTable/Release/arduino.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

TestXTable.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"/opt/arduino-1.6.5/hardware/tools/avr/bin/avr-gcc" -Os -Wl,--gc-sections -mmcu=atmega328p  -o "/home/arduinodev/workspace/TestXTable/Release/TestXTable.elf"   $(LINK_OBJ) $(AR)  "/home/arduinodev/workspace/TestXTable/Release/arduino.ar" "-L/home/arduinodev/workspace/TestXTable/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

TestXTable.eep: $(ELF)
	@echo 'Create eeprom image'
	"/opt/arduino-1.6.5/hardware/tools/avr/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "/home/arduinodev/workspace/TestXTable/Release/TestXTable.elf" "/home/arduinodev/workspace/TestXTable/Release/TestXTable.eep"
	@echo 'Finished building: $@'
	@echo ' '

TestXTable.hex: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"/opt/arduino-1.6.5/hardware/tools/avr/bin/avr-objcopy" -O ihex -R .eeprom  "/home/arduinodev/workspace/TestXTable/Release/TestXTable.elf" "/home/arduinodev/workspace/TestXTable/Release/TestXTable.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_DEPS)$(AR)$(FLASH_IMAGE)$(EEP)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ELF)$(ASM_DEPS)$(CC_DEPS)$(AR_OBJ)$(CPP_DEPS)$(LINK_OBJ)$(C_UPPER_DEPS)$(SIZEDUMMY) TestXTable
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
