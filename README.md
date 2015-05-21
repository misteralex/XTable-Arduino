# XTable-Arduino
XTable class is designed both for Arduino sketches and C++ projects but it aims to be used also for generic embedded C++ based boards. It supports short set of informations, typically for configuration purpose, with CRUD API approach (Create, Read, Update and Delete).

It implements a short table (database) oriented to generic structured items through an efficient storage using an circular buffer EEPROM and volatile SRAM for dynamic memory allocation. Circular buffer (O-Buffer) prevent wear out of the EEPROM. Since it is only guaranteed to endure 100k erase/write/cycles the O-Buffer increase until to twice the number of times that a configuration (collection of parameters) can be stored.

This embedded library is designed considering an Atmel Application Note (AVR101: High Endurance EEPROM Storage) to improve EEPROM management and currently is available on Arduino context to support the XDAQ virtual appliance for research purposes.

Please refer to the XDAQ Guide to know more details about it. The guide is available at www.embeddedrevolution.info Home Page.


## XTable Resources

1. XTable Arduino Library and examples (available at XTable-Arduino/XTable)
2. XEEPROM Arduino Library and examples (available at XTable-Arduino/XEEPROM)
3. TestXTable Project to test all expected functionality through ArduinoUnit test library (available at XTable-Arduino/TestXTable)
4. BlinkingLEDs Project a complete demo application using Firmata protocol (available at XTable-Arduino/BlinkingLEDs)
   This application is available both from console and GUI mode. The demo is available through standard serial port access (e.g. cutecom, putty) and through an openFrameworks demo application.


### From source
- Download the latest release
- Or clone it from Github using the command `git clone git@github.com:misteralex/XTable-Arduino.git`
- Check the XDAQ Guide and this readme about usage options.


## Requirements
You need to have Debianinux, XDAQ or equivalent environment that include Arduino IDE or Eclipse C++ IDE.
