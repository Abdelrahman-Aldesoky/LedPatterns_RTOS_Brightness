#------------------------------------------------------------------#
# Makefile for AVR projects  "Assignment"                          #
# Author: Abdelrahman Mohamed Ibrahim Al-desoky.                   #
# Date: 07/11/2023                                                 #
#                                                                  #
# This Makefile compiles C source files located in the current     #
# directory into a library for AVR Micro controllers. The          #
# Micro controller model and clock frequency are configurable      #
# through the config.mk file or environment variables. The         #
# Makefile automatically generates dependencies, so that source    #
# files are recompiled when the header files they include are      #
# modified.                                                        #
#                                                                  #
# The Makefile also includes a status target that checks           #
# if the libraries were successfully produced, and records the     #
# date and time of generation and all libraries names. This works  #
# on both Windows CMD prompt and Linux. The output file is named   #
# Libraries_Status_Report.txt and is placed in the build           #
# directory specified in the variables.                            #
#------------------------------------------------------------------#

# Assign variables based on the OS
ifeq ($(OS),Windows_NT)
MK_DIR = if not exist $(subst /,\,$1) mkdir $(subst /,\,$1)
DEL_ALL = if exist $(subst /,\,$1) rmdir /s /q $(subst /,\,$1)
DATE_CMD = %date% %time%
REPORT = if exist $(subst /,\,$(L_BUILD_DIR))\Libraries_Status_Report.txt \
(type $(subst /,\,$(L_BUILD_DIR))\Libraries_Status_Report.txt) \
else (echo Nothing to Report.)
else
MK_DIR = mkdir -p $1
DEL_ALL = rm -rf $1
DATE_CMD = $(shell date)
REPORT = if [ -f $(L_BUILD_DIR)/Libraries_Status_Report.txt ]; \
then cat $(L_BUILD_DIR)/Libraries_Status_Report.txt; \
else echo "Nothing to Report."; fi
endif

# Include config.mk if it exists you can assign most of the variables there and it will overwrite the ones in here
-include ../config.mk

# Lib Makefile Directories Variables
L_BUILD_DIR ?= ../build
L_DEPS_DIR ?= ../build/dependencies
L_LIBS_DIR ?= ../build/libraries
L_OBJS_DIR ?= ../build/objects
L_SRCS_DIR ?= .

# Toolchain definitions
CC ?= avr-gcc
AR ?= avr-ar

# Micro controller Variables
MCU ?= atmega32
F_CPU ?= 8000000

# Compiler flags
CFLAGS ?= -mmcu=$(MCU) -DF_CPU=$(F_CPU) -std=gnu99 -O2 -Wall

# Source files
L_SRCS = $(wildcard $(L_SRCS_DIR)/*.c)

# Use the part of the filename before the underscore
BASE_NAMES := $(foreach src,$(notdir $(L_SRCS)),$(firstword $(subst _, ,$(basename $(src)))))

# Objects dependencies and libraries files
OBJS := $(addprefix $(L_OBJS_DIR)/, $(addsuffix .o, $(BASE_NAMES)))
DEPS := $(addprefix $(L_DEPS_DIR)/, $(addsuffix .d, $(BASE_NAMES)))
LIBS := $(addprefix $(L_LIBS_DIR)/lib, $(addsuffix .a, $(BASE_NAMES)))

# Preserve intermediate files
.PRECIOUS: $(L_OBJS_DIR)/%.o

# Rule to create all (Default target)
all: $(LIBS)

# Rule to compile source files into an object files also creates dependencies 
$(L_OBJS_DIR)/%.o: $(L_SRCS_DIR)/%*.c
	@$(call MK_DIR,$(L_BUILD_DIR))
	@$(call MK_DIR,$(L_OBJS_DIR))
	@$(call MK_DIR,$(L_DEPS_DIR))
	@$(call MK_DIR,$(L_LIBS_DIR))
	@$(CC) $(CFLAGS) -MD -MP -MF $(L_DEPS_DIR)/$*.d -c $< -o $@

# Include dependencies
-include $(DEPS)

# Rule to create static libraries
$(L_LIBS_DIR)/lib%.a : $(L_OBJS_DIR)/%.o
	@$(AR) rcs $@ $<
	@echo "Generated Library: $(notdir $@) Generation Time: $(DATE_CMD)" >> $(L_BUILD_DIR)/Libraries_Status_Report.txt
	@echo "Generated Library: $(notdir $@) Generation Time: $(DATE_CMD)"

# Rule to clean all generated files
clean:
	@$(call DEL_ALL,$(L_BUILD_DIR))
	@echo "Cleanup complete. All generated files have been removed."

# Status rule
status:
	@$(REPORT)

# Help target
help:
	@echo "|----------------------------------------HELP.------------------------------------------|"
	@echo "|                                                                                       |"
	@echo "|This Makefile compiles C source files located in the current directory into libraries  |"
	@echo "|for AVR Micro controller. The Micro controller model and clock frequency are           |"
	@echo "|configurable through the config.mk file or environment variables. The Makefile         |"
	@echo "|automatically generates dependencies, so that source files are recompiled automatically|"
	@echo "|when the header files corresponding to it get modified.                                |"
	@echo "|                                                                                       |"
	@echo "|The Makefile also includes a status report target that checks if the libraries were    |"
	@echo "|successfully produced, and records the date and time of generation and all library     |"
	@echo "|names. This works on both Windows CMD prompt and Linux. The output file is named       |"
	@echo "|Libraries_Status_Report.txt and is placed in the libraries directory inside the build  |"
	@echo "|directory specified in the variables. The all target is the default target it builds   |"
	@echo "|all the libraries that needs to be rebuilt.                                            |"
	@echo "|                                                                                       |"
	@echo "|Usage:                                                                                 |"
	@echo "|  make [TARGET] [VARIABLE=value]                                                       |"
	@echo "|                                                                                       |"
	@echo "|Targets:                                                                               |"
	@echo "|  all (default)           : Builds the libraries.                                      |"
	@echo "|  status                  : Generates a status report.                                 |"
	@echo "|  clean                   : Removes all generated files so be careful.                 |"
	@echo "|  help                    : Displays this help menu.                                   |"
	@echo "|                                                                                       |"
	@echo "|Variables:                                                                             |"
	@echo "|  MCU   : The Micro controller model (default: atmega32).                              |"
	@echo "|  F_CPU : The Micro controller clock frequency in Hz (default: 8000000).               |"
	@echo "|  CFLAGS: Additional flags to pass to the compiler.                                    |"
	@echo "|                                                                                       |"
	@echo "|Examples:                                                                              |"
	@echo "|  make                                                                                 |"
	@echo "|  make F_CPU=16000000 MCU=atmega328p                                                   |"
	@echo "|  make all CFLAGS=-mmcu=atmega328p -DF_CPU=16000000 -std=gnu99 -O2 -Wall               |"
	@echo "|  When executing the make all command with the CFLAGS variable, it is important to     |"
	@echo "|  ensure that multiple arguments are enclosed in quotes.                               |"
	@echo "|  make clean                                                                           |"
	@echo "|  make status                                                                          |"
	@echo "|  make help                                                                            |"
	@echo "|---------------------------------------------------------------------------------------|"

# Phony targets
.PHONY: all clean status help

# Delete on error so no corrupt files
.DELETE_ON_ERROR: