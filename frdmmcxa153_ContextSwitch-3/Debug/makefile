################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/str/subdir.mk
-include utilities/debug_console_lite/subdir.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include board/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := frdmmcxa153_ContextSwitch-3
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: frdmmcxa153_ContextSwitch-3.axf

# Tool invocations
frdmmcxa153_ContextSwitch-3.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -no-warn-rwx-segments -Xlinker -Map="frdmmcxa153_ContextSwitch-3.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m33+nodsp -mthumb -T frdmmcxa153_ContextSwitch-3_Debug.ld -o "frdmmcxa153_ContextSwitch-3.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) frdmmcxa153_ContextSwitch-3.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "frdmmcxa153_ContextSwitch-3.axf"; # arm-none-eabi-objcopy -v -O binary "frdmmcxa153_ContextSwitch-3.axf" "frdmmcxa153_ContextSwitch-3.bin" ; # checksum -p MCXA153 -d "frdmmcxa153_ContextSwitch-3.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
