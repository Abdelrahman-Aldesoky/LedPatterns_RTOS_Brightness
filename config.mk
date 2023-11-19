# Initially, when there was only one source file, PROJECT_NAME was set to the parent directory's name.
# The compiled output (.hex and .elf files) was named after the parent directory.
# After updating to compile multiple source files, this approach became unfeasible.
# Now, .hex and .elf files are named after their respective source files in the src directory.
PROJECT_NAME := $(notdir $(CURDIR))

# Micro controller Variables
MCU ?= atmega32
F_CPU ?= 8000000

# Compiler flags linker flag
CFLAGS ?= -mmcu=$(MCU) -DF_CPU=$(F_CPU) -std=gnu99 -Os -Wall

# Lib Makefile Directory
LIB_MAKE_FILE := ./lib 

# Main Makefile Directories Variables
M_BUILD_DIR := ./build
M_DEPS_DIR := ./build/dependencies
M_LIBS_DIR := ./build/libraries
M_OBJS_DIR := ./build/objects
M_PROGS_DIR := ./build/programs
M_SRCS_DIR := ./src

# Lib Makefile Directories Variables
L_BUILD_DIR := ../build
L_DEPS_DIR := ../build/dependencies
L_LIBS_DIR := ../build/libraries
L_OBJS_DIR := ../build/objects
L_SRCS_DIR := .

# Toolchain definitions
CC := avr-gcc
AR := avr-ar
OBJCOPY := avr-objcopy
SIZE := avr-size