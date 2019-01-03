# Hey Emacs, this is a -*- makefile -*-
#
# simple_fc.makefile
#

BOARD=simple_fc
BOARD_VERSION=1.0
BOARD_DIR=$(BOARD)/chibios/v$(BOARD_VERSION)
BOARD_CFG=\"boards/$(BOARD_DIR)/board.h\"

ARCH=chibios
$(TARGET).ARCHDIR = $(ARCH)

RTOS=chibios

## FPU on F4
USE_FPU=hard

# See list of supported Tier 3 architectures at: https://forge.rust-lang.org/platform-support.html
RUST_ARCH = thumbv7em-none-eabihf

$(TARGET).CFLAGS += -DSTM32F4 -DPPRZLINK_ENABLE_FD

##############################################################################
# Architecture or project specific options
#
# Define project name here (target)
PROJECT = $(TARGET)

# Project specific files and paths (see Makefile.chibios for details)
CHIBIOS_BOARD_PLATFORM = STM32F4xx/platform.mk
CHIBIOS_BOARD_LINKER = STM32F407xG.ld
CHIBIOS_BOARD_STARTUP = startup_stm32f4xx.mk

# bootloader for Lisa MX is available from https://github.com/podhrmic/aggieair-bootloader
HAS_LUFTBOOT ?= 0
ifeq (,$(findstring $(HAS_LUFTBOOT),0 FALSE))
$(TARGET).CFLAGS+=-DLUFTBOOT
DFU_ADDR = 0x8004000
DFU_PRODUCT = SimpleFC
endif

##############################################################################
# Compiler settings
#
MCU  = cortex-m4

# default flash mode is via usb dfu bootloader
# possibilities: DFU-UTIL, SWD, STLINK
FLASH_MODE ?= SWD

#
# default LED configuration
#
RADIO_CONTROL_LED  ?= 1
BARO_LED           ?= none
AHRS_ALIGNER_LED   ?= 2
GPS_LED            ?= 3
SYS_TIME_LED       ?= none

#
# default uart configuration
#
RADIO_CONTROL_SPEKTRUM_PRIMARY_PORT   ?= UART2
RADIO_CONTROL_SPEKTRUM_SECONDARY_PORT ?= UART4

MODEM_PORT ?= UART1
MODEM_BAUD ?= B57600

GPS_PORT ?= UART3
GPS_BAUD ?= B9600

#
# default PPM input is on PA01
#
RADIO_CONTROL_PPM_PIN ?= PA01
ifeq ($(RADIO_CONTROL_PPM_PIN),$(filter $(RADIO_CONTROL_PPM_PIN),PA_01 PA01 PA1 SERVO6))
  PPM_CONFIG=1
else
$(error Unknown RADIO_CONTROL_PPM_PIN, configure it to either PA01)
endif

#
# default actuator configuration
#
# you can use different actuators by adding a configure option to your firmware section
# e.g. <configure name="ACTUATORS" value="actuators_ppm/>
# and by setting the correct "driver" attribute in servo section
# e.g. <servo driver="Ppm">
#
ACTUATORS ?= actuators_pwm
