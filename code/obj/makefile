################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################
-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
bcd2civ.hex \

SECONDARY_LIST += \
bcd2civ.lst \

SECONDARY_SIZE += \
bcd2civ.siz \


# All Target
all: 
	$(MAKE) --no-print-directory main-build 

main-build: bcd2civ.elf secondary-outputs

# Tool invocations
bcd2civ.elf: $(OBJS) $(USER_OBJS)
	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -T "/home/ra0sms/stm32/RiskV/bcd2civ/code/Ld/Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"bcd2civ.map" --specs=nano.specs --specs=nosys.specs -o "bcd2civ.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lprintf
bcd2civ.hex: bcd2civ.elf
	@	riscv-none-embed-objcopy -O ihex "bcd2civ.elf" "bcd2civ.hex"
bcd2civ.lst: bcd2civ.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "bcd2civ.elf" > "bcd2civ.lst"
bcd2civ.siz: bcd2civ.elf
	riscv-none-embed-size --format=berkeley "bcd2civ.elf"

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(S_DEPS)$(S_UPPER_DEPS)$(ASM_DEPS)$(ASM_UPPER_DEPS)$(C_DEPS) bcd2civ.elf

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets