################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/src/core/ipv4/acd.c \
../lwip/src/core/ipv4/autoip.c \
../lwip/src/core/ipv4/dhcp.c \
../lwip/src/core/ipv4/etharp.c \
../lwip/src/core/ipv4/icmp.c \
../lwip/src/core/ipv4/igmp.c \
../lwip/src/core/ipv4/ip4.c \
../lwip/src/core/ipv4/ip4_addr.c \
../lwip/src/core/ipv4/ip4_frag.c 

C_DEPS += \
./lwip/src/core/ipv4/acd.d \
./lwip/src/core/ipv4/autoip.d \
./lwip/src/core/ipv4/dhcp.d \
./lwip/src/core/ipv4/etharp.d \
./lwip/src/core/ipv4/icmp.d \
./lwip/src/core/ipv4/igmp.d \
./lwip/src/core/ipv4/ip4.d \
./lwip/src/core/ipv4/ip4_addr.d \
./lwip/src/core/ipv4/ip4_frag.d 

OBJS += \
./lwip/src/core/ipv4/acd.o \
./lwip/src/core/ipv4/autoip.o \
./lwip/src/core/ipv4/dhcp.o \
./lwip/src/core/ipv4/etharp.o \
./lwip/src/core/ipv4/icmp.o \
./lwip/src/core/ipv4/igmp.o \
./lwip/src/core/ipv4/ip4.o \
./lwip/src/core/ipv4/ip4_addr.o \
./lwip/src/core/ipv4/ip4_frag.o 


# Each subdirectory must supply rules for building sources it contributes
lwip/src/core/ipv4/%.o: ../lwip/src/core/ipv4/%.c lwip/src/core/ipv4/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DMCUXPRESSO_SDK -DFSL_SDK_DRIVER_QUICK_ACCESS_ENABLE=1 -DUSB_STACK_FREERTOS -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DSDK_DEBUGCONSOLE=1 -DMCUX_META_BUILD -DCPU_RW612ETA2I -DOSA_USED -DBOOT_HEADER_ENABLE=1 -DUSE_RTOS=1 -DSDK_OS_FREE_RTOS -DCPU_RW612ETA2I_cm33_nodsp -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\source" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\flash_config" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\drivers" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\CMSIS" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\CMSIS\m-profile" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\device" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\device\periph" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\utilities" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\lists" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\utilities\str" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\utilities\debug_console_lite" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\uart" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\osa\config" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\osa" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\els_pkc" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\phy" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\silicon_id" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\els_pkc\src\comps\mcuxClBuffer\inc" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\els_pkc\src\comps\mcuxClBuffer\inc\internal" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\els_pkc\src\comps\mcuxClCore\inc" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\els_pkc\src\comps\mcuxClEls\inc" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\els_pkc\src\comps\mcuxClEls\inc\internal" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\els_pkc\src\comps\mcuxClMemory\inc" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\els_pkc\src\comps\mcuxClMemory\inc\internal" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\els_pkc\src\comps\mcuxCsslMemory\inc" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\els_pkc\src\comps\mcuxCsslMemory\inc\internal" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\els_pkc\src\comps\mcuxCsslCPreProcessor\inc" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\els_pkc\src\comps\mcuxCsslDataIntegrity\inc" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\els_pkc\src\comps\mcuxCsslFlowProtection\inc" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\els_pkc\src\comps\mcuxCsslParamIntegrity\inc" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\els_pkc\src\comps\mcuxCsslSecureCounter\inc" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\els_pkc\src\compiler" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\els_pkc\src\platforms\rw61x" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\els_pkc\src\platforms\rw61x\inc" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\els_pkc\includes\platform\rw61x" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\component\gpio" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\lwip\port" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\lwip\src\include" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\lwip\port\sys_arch\dynamic" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\usb\include" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\usb\host" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\usb\host\class" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\freertos\freertos-kernel\include" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\freertos\freertos-kernel\portable\GCC\ARM_CM33_NTZ\non_secure" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\board" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\source\config\host\ehci" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\freertos\freertos-kernel\template" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\freertos\freertos-kernel\template\ARM_CM33_3_priority_bits" -O0 -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -fno-builtin -mcpu=cortex-m33+nodsp -imacros "C:\Users\nxa16972\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_SmartLock_TCPandServo\source\mcux_config.h" -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33+nodsp -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-lwip-2f-src-2f-core-2f-ipv4

clean-lwip-2f-src-2f-core-2f-ipv4:
	-$(RM) ./lwip/src/core/ipv4/acd.d ./lwip/src/core/ipv4/acd.o ./lwip/src/core/ipv4/autoip.d ./lwip/src/core/ipv4/autoip.o ./lwip/src/core/ipv4/dhcp.d ./lwip/src/core/ipv4/dhcp.o ./lwip/src/core/ipv4/etharp.d ./lwip/src/core/ipv4/etharp.o ./lwip/src/core/ipv4/icmp.d ./lwip/src/core/ipv4/icmp.o ./lwip/src/core/ipv4/igmp.d ./lwip/src/core/ipv4/igmp.o ./lwip/src/core/ipv4/ip4.d ./lwip/src/core/ipv4/ip4.o ./lwip/src/core/ipv4/ip4_addr.d ./lwip/src/core/ipv4/ip4_addr.o ./lwip/src/core/ipv4/ip4_frag.d ./lwip/src/core/ipv4/ip4_frag.o

.PHONY: clean-lwip-2f-src-2f-core-2f-ipv4

