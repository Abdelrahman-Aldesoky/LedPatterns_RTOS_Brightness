#------------------------------------------------------------------#
# Makefile for AVR projects  "Assignment"                          #
# Author: Abdelrahman Mohamed Ibrahim Al-desoky.                   #
# Date: 07/11/2023                                                 #
#                                                                  #
# This Makefile compiles C source files located in the src         #
# directory into .hex and .elf files for AVR Micro controllers.    #
# The Micro controller model and clock frequency are configurable  #
# through the config.mk file or environment variables. The         #
# Makefile automatically generates dependencies, so that source    #
# files are recompiled when the header files they include are      #
# modified.                                                        #
#                                                                  #
# The Makefile also includes a status target that checks           #
# if the .hex and .elf files were successfully produced, and       #
# records the date and time of generation. This works on both      #
# Windows CMD prompt and Linux. The output file is named           #
# Binaries_Status_Report.txt and is placed in the build directory  #
# specified in the variables.                                                #
#------------------------------------------------------------------#

# Assign variables based on the OS
ifeq ($(OS),Windows_NT)
MK_DIR = if not exist $(subst /,\,$1) mkdir $(subst /,\,$1)
DEL_ALL = if exist $(subst /,\,$1) rmdir /s /q $(subst /,\,$1)
DATE_CMD = %date% %time%
REPORT = if exist $(subst /,\,$(M_BUILD_DIR))\Binaries_Status_Report.txt \
(type $(subst /,\,$(M_BUILD_DIR))\Binaries_Status_Report.txt) \
else (echo Nothing to Report.)
BINARY_REPORT = if exist $(subst /,\,$(M_PROGS_DIR))\binaryReport_$*.txt \
(type $(subst /,\,$(M_PROGS_DIR))\binaryReport_$*.txt) \
else (echo binaryReport_$*.txt not found.)
else
MK_DIR = mkdir -p $1
DEL_ALL = rm -rf $1
DATE_CMD = $(shell date)
REPORT = if [ -f $(M_BUILD_DIR)/Binaries_Status_Report.txt ]; \
then cat $(M_BUILD_DIR)/Binaries_Status_Report.txt; \
else echo "Nothing to Report."; fi
BINARY_REPORT = if [ -f $(M_PROGS_DIR)/binaryReport_$*.txt ]; \
then cat $(M_PROGS_DIR)/binaryReport_$*.txt; \
else echo "binaryReport_$*.txt not found."; fi
endif

# Include config.mk if it exists. It can overwrite the variables in here.
-include config.mk

# Lib Makefile Directory
LIB_MAKE_FILE ?= ./lib 

# Main Makefile Directories Variables
M_BUILD_DIR ?= ./build
M_DEPS_DIR ?= ./build/dependencies
M_LIBS_DIR ?= ./build/libraries
M_OBJS_DIR ?= ./build/objects
M_PROGS_DIR ?= ./build/programs
M_SRCS_DIR ?= ./src

# Toolchain definitions
CC ?= avr-gcc
OBJCOPY ?= avr-objcopy
SIZE ?= avr-size

# Micro controller Variables
MCU ?= atmega32
F_CPU ?= 8000000

# Compiler flags linker flag include
CFLAGS ?= -mmcu=$(MCU) -DF_CPU=$(F_CPU) -std=gnu99 -O2 -Wall
LDFLAGS ?= -L$(M_LIBS_DIR)

# Sources objects dependencies elfs and hexs files
SRCS = $(wildcard $(M_SRCS_DIR)/*.c)
OBJS = $(patsubst $(M_SRCS_DIR)/%.c,$(M_OBJS_DIR)/%.o,$(SRCS))
DEPS = $(patsubst $(M_SRCS_DIR)/%.c,$(M_DEPS_DIR)/%.d,$(SRCS))
ELFS = $(patsubst $(M_SRCS_DIR)/%.c,$(M_PROGS_DIR)/%.elf,$(SRCS))
HEXS = $(patsubst $(M_SRCS_DIR)/%.c,$(M_PROGS_DIR)/%.hex,$(SRCS))

# Conditional assignment of LIBS for cross-platform compatibility.
# On Windows, wildcard can list .a files anytime.
# On Unix-like systems, wildcard can only list .a files if they exist when Makefile is parsed.
# Hence, we use find command on Unix-like systems to ensure LIBS is correctly populated.
ifeq ($(OS),Windows_NT)
LIBS = $(wildcard $(M_LIBS_DIR)/*.a)
else
LIBS = $(shell find $(M_LIBS_DIR) -name '*.a' 2>/dev/null)
endif

# Preserve intermediate files
.PRECIOUS: $(M_PROGS_DIR)/%.elf $(M_OBJS_DIR)/%.o

# Rule to create all (Default target)
all: libs $(HEXS)

# Phony Target to always check if the lib makefile is up to date or not
libs:
	@$(MAKE) -C $(LIB_MAKE_FILE) CFLAGS="$(CFLAGS)"

# Rule to compile source files into an object files also creates dependencies  
$(M_OBJS_DIR)/%.o: $(M_SRCS_DIR)/%.c
	@$(CC) $(CFLAGS) -MD -MP -MF $(M_DEPS_DIR)/$*.d -c $< -o $@

# Include dependencies
-include $(DEPS)

# Rule to create .elf files also generates binary report with the same .c file name
$(M_PROGS_DIR)/%.elf: $(M_OBJS_DIR)/%.o $(LIBS)
	@$(call MK_DIR,$(M_PROGS_DIR))
	@$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)
	@$(SIZE) --format=avr --mcu=$(MCU) $@ > $(M_PROGS_DIR)/binaryReport_$*.txt
	@echo "Generated Binary: $(notdir $@) Generation Time: $(DATE_CMD)" >> $(M_BUILD_DIR)/Binaries_Status_Report.txt
	@echo "Generated Binary: $(notdir $@) Generation Time: $(DATE_CMD)"

# Rule to create .hex files 
$(M_PROGS_DIR)/%.hex: $(M_PROGS_DIR)/%.elf
	@$(OBJCOPY) -j .text -j .data -O ihex $< $@
	@echo "Generated Binary: $(notdir $@) Generation Time: $(DATE_CMD)" >> $(M_BUILD_DIR)/Binaries_Status_Report.txt
	@echo "Generated Binary: $(notdir $@) Generation Time: $(DATE_CMD)"
	@$(BINARY_REPORT)
 
# Rule to clean all generated files
clean:
	@$(call DEL_ALL,$(M_BUILD_DIR))
	@echo "Cleanup complete. All generated files have been removed."

# Status rule
status:
	@$(REPORT)

# Help target
help: 
	@echo "|----------------------------------------HELP.-------------------------------------------|"
	@echo "|                                                                                        |"
	@echo "|This Makefile compiles C source files located in the src directory into .hex and        |"
	@echo "|.elf files for the AVR Micro controller. The Micro controller model and clock           |"
	@echo "|frequency are configurable through the config.mk file or environment variables. The     |"
	@echo "|Makefile automatically generates dependencies, so that source files are recompiled      |"
	@echo "|when any of header files they include are modified.                                     |"
	@echo "|                                                                                        |"
	@echo "|The Makefile also includes a status target that checks if the .hex and .elf             |"
	@echo "|files were successfully produced, and records the date and time of generation. This     |"
	@echo "|works on both Windows CMD prompt and Linux. The file is named Binaries_Status_Report.txt|"
	@echo "|and is placed in the build directory specified in the variables.                        |"
	@echo "|                                                                                        |"
	@echo "|Usage:                                                                                  |"
	@echo "|  make [TARGET] [VARIABLE=value]                                                        |"
	@echo "|                                                                                        |"
	@echo "|Targets:                                                                                |"
	@echo "|  all (default)           : Builds the .hex and .elf.                                   |"
	@echo "|  libs                    : Builds all the outdated libraries in my lib directory.      |"
	@echo "|  status                  : Generates a status report.                                  |"
	@echo "|  clean                   : Removes all generated files so be careful.                  |"
	@echo "|  help                    : Displays this help menu.                                    |"
	@echo "|                                                                                        |"
	@echo "|Variables:                                                                              |"
	@echo "|  MCU   : The Micro controller model (default: atmega32).                               |"
	@echo "|  F_CPU : The Micro controller clock frequency in Hz (default: 8000000).                |"
	@echo "|  CFLAGS: Additional flags to pass to the compiler.                                     |"
	@echo "|                                                                                        |"
	@echo "|Examples:                                                                               |"
	@echo "|  make                                                                                  |"
	@echo "|  make F_CPU=16000000 MCU=atmega328p                                                    |"
	@echo "|  make all CFLAGS=-mmcu=atmega328p -DF_CPU=16000000 -std=gnu99 -O2 -Wall                |"
	@echo "|  When executing the make all command with the CFLAGS variable, it is important to      |"
	@echo "|  ensure that multiple arguments are enclosed in quotes.                                |"
	@echo "|  make libs                                                                             |"
	@echo "|  make clean                                                                            |"
	@echo "|  make status                                                                           |"
	@echo "|  make help                                                                             |"
	@echo "|----------------------------------------------------------------------------------------|"

# Phony targets
.PHONY: all libs clean status help

# Delete on error so no corrupt files
.DELETE_ON_ERROR: