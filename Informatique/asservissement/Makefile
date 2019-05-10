default: all

Makefile_path := $(shell dirname $(abspath $(lastword $(MAKEFILE_LIST))))

Toolchain = arm-none-eabi-

CC = $(Toolchain)gcc
CFlags =
CXX= $(Toolchain)g++
CXXFlags =
LD = $(Toolchain)ld
LFlags =
GDB=$(Toolchain)gdb

ifeq (, $(shell which ccache))
else
	CC := ccache $(CC)
	CXX:= ccache $(CXX)
endif


# Generic flags
CFlags += \
	-Os \
	-std=gnu11 \
	-fdiagnostics-color=always \
	-Wall \
	-Wextra \
	-g \

	# -ffunction-sections \
	# -fdata-sections \
	# -fno-common \
	# -fno-exceptions \
	# --static

CXXFlags += \
	-std=gnu++14

LFlags += \
	-Wl,--gc-sections \
	-nostartfiles \
	-lm \
	-lstdc++_nano \
	-lc \
	-lg \
	-lrdimon


# MCU specific flags (stm32f401re)
LINKER_SCRIPTS_DIR = $(Makefile_path)/hal_common/linker_scripts

CFlags += \
	-mcpu=cortex-m4 \
	-mthumb \
	-mfloat-abi=hard \
	-mfpu=fpv4-sp-d16 \
	-specs=nano.specs

	# Use LibOpenCm3
LIBOPENCM3_DIR = $(Makefile_path)/hal_common/libopencm3
CFlags += -I $(LIBOPENCM3_DIR)/include -DSTM32F3
LFlags += -L $(LIBOPENCM3_DIR)/lib -lopencm3_stm32f3

libopencm3:
	$(MAKE) -C $(LIBOPENCM3_DIR) -j

# Openocd configuration
OPENOCD_CFG = /usr/share/openocd/scripts/board/st_nucleo_f3.cfg


LFlags += -T $(LINKER_SCRIPTS_DIR)/stm32f303.ld

CFlags += -I.

all: tsmr.hex

%.cpp.o: %.cpp Makefile
	@$(CXX) $(CFlags) $(CXXFlags) $< -o $@ -c
	@echo CXX $<

%.c.o: %.c Makefile
	@$(CC) $(CFlags) $< -o $@ -c
	@echo CC $<


tsmr.elf: \
		lowlevel/adc.c.o \
		lowlevel/can.c.o \
		lowlevel/clock.c.o \
		lowlevel/debug.c.o \
		lowlevel/eeprom.c.o \
		lowlevel/encoders.c.o \
		lowlevel/gpio.c.o \
		lowlevel/motors.c.o \
		asservissement/calibration.c.o \
		asservissement/odometry.c.o \
		asservissement/pid.c.o \
		main.c.o \
		|
	$(CC) $(CFlags) $^ $(LFlags) -o $@
	@echo LINK $@


tests.elf: \
		lowlevel/adc.c.o \
		lowlevel/can.c.o \
		lowlevel/clock.c.o \
		lowlevel/debug.c.o \
		lowlevel/eeprom.c.o \
		lowlevel/encoders.c.o \
		lowlevel/gpio.c.o \
		lowlevel/motors.c.o \
		asservissement/calibration.c.o \
		asservissement/odometry.c.o \
		asservissement/pid.c.o \
		main_tests.c.o \
		|
	$(CC) $(CFlags) $^ $(LFlags) -o $@
	@echo LINK $@

%.hex: %.elf
	@arm-none-eabi-objcopy -Oihex $^ $@
	@echo OBJCOPY $@


#please do not put sudo before openocd, please run
#sudo usermod -a -G uucp <user> for serial monitor
#for udev rule:
#nano /etc/udev/rules.d/70-st-link.rules
#  #NUCLEO ST-LINK/V2.1
#  ATTRS{idVendor}=="0483", ATTRS{idProduct}=="374b",TAG+="uaccess"
#to find theses values lsusb
#then udevadm control --reload-rules
#unplug and plug st-link

install_udev:
	@echo "Installing udev rules…"
	@sudo ./install_udev.sh
	@echo "Now, unplug and re-plug the st-link."

%.flash: %.hex
	openocd -f $(OPENOCD_CFG) \
		-c "init" \
		-c "reset init" \
		-c "flash write_image erase $^" \
		-c "reset" \
		-c "shutdown"

#NOTE: the files in the gdb dir must correspond to your MCU
%.debug: %.elf
	$(GDB) $^ --command=gdb/attach.gdb

clean:
		find . \
		\( -not -path  "./hal_common*" \) \
		\( -name "*.o" \
		-o -name "*.a" \
		-o -name "*.hex" \
		-o -name "*.elf" \
		\) -delete
