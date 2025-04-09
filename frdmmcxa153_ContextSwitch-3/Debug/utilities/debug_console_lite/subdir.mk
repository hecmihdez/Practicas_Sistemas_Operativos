################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/debug_console_lite/fsl_debug_console.c 

C_DEPS += \
./utilities/debug_console_lite/fsl_debug_console.d 

OBJS += \
./utilities/debug_console_lite/fsl_debug_console.o 


# Each subdirectory must supply rules for building sources it contributes
utilities/debug_console_lite/%.o: ../utilities/debug_console_lite/%.c utilities/debug_console_lite/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MCXA153VLH -DCPU_MCXA153VLH_cm33_nodsp -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DMCUX_META_BUILD -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmmcxa153_ContextSwitch-3\source" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmmcxa153_ContextSwitch-3\drivers" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmmcxa153_ContextSwitch-3\CMSIS" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmmcxa153_ContextSwitch-3\CMSIS\m-profile" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmmcxa153_ContextSwitch-3\device" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmmcxa153_ContextSwitch-3\device\periph" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmmcxa153_ContextSwitch-3\utilities" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmmcxa153_ContextSwitch-3\utilities\str" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmmcxa153_ContextSwitch-3\utilities\debug_console_lite" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmmcxa153_ContextSwitch-3\component\uart" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmmcxa153_ContextSwitch-3\board" -O0 -fno-common -g3 -gdwarf-4 -mcpu=cortex-m33+nodsp -c -ffunction-sections -fdata-sections -fno-builtin -imacros "C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmmcxa153_ContextSwitch-3\source\mcux_config.h" -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33+nodsp -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-utilities-2f-debug_console_lite

clean-utilities-2f-debug_console_lite:
	-$(RM) ./utilities/debug_console_lite/fsl_debug_console.d ./utilities/debug_console_lite/fsl_debug_console.o

.PHONY: clean-utilities-2f-debug_console_lite

