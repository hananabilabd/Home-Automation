################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
FLASH_IMAGE += \
Atmega32_SPI-Receiver_UART-Transmiter_I2C-Receiver.hex \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: Atmega32_SPI-Receiver_UART-Transmiter_I2C-Receiver.elf secondary-outputs

# Tool invocations
Atmega32_SPI-Receiver_UART-Transmiter_I2C-Receiver.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Atmega32_SPI-Receiver_UART-Transmiter_I2C-Receiver.map -mmcu=atmega32 -o "Atmega32_SPI-Receiver_UART-Transmiter_I2C-Receiver.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Atmega32_SPI-Receiver_UART-Transmiter_I2C-Receiver.hex: Atmega32_SPI-Receiver_UART-Transmiter_I2C-Receiver.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Atmega32_SPI-Receiver_UART-Transmiter_I2C-Receiver.elf  "Atmega32_SPI-Receiver_UART-Transmiter_I2C-Receiver.hex"
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: Atmega32_SPI-Receiver_UART-Transmiter_I2C-Receiver.elf
	@echo 'Invoking: AVRDude'
	F:\Programs\Eclipse\IMT_SDK_Win_64\WinAVR\bin\avrdude -pm32 -cusbasp -Uflash:w:Atmega32_SPI-Receiver_UART-Transmiter_I2C-Receiver.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) Atmega32_SPI-Receiver_UART-Transmiter_I2C-Receiver.elf
	-@echo ' '

secondary-outputs: $(FLASH_IMAGE) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
