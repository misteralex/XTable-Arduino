################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TestXTable.cpp 

CPP_DEPS += \
./TestXTable.cpp.d 

LINK_OBJ += \
./TestXTable.cpp.o 


# Each subdirectory must supply rules for building sources it contributes
TestXTable.cpp.o: ../TestXTable.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/opt/arduino-1.6.5/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10605 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR     -I"/opt/arduino-1.6.5/hardware/arduino/avr/cores/arduino" -I"/opt/arduino-1.6.5/hardware/arduino/avr/variants/standard" -I"/home/arduinodev/Arduino/libraries/XTable" -I"/home/arduinodev/Arduino/libraries/arduinounit-master" -I"/home/arduinodev/Arduino/libraries/arduinounit-master/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


