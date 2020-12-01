# make is alias for make all
.DEFAULT_GOAL := all

# Name of recipes
.PHONY: all llaunch mlaunch clean fclean re

################################################################################
#								PROJECT	CONFIG 								   #
################################################################################

# Selecting Core (STM32F303VC DISCOVERY IS ARM M4)
CORTEX_M = 4
CORE = CM$(CORTEX_M)

# Project name
NAME = I2C-$(CORE)

# Compiler, Linker & Debugger
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
DB = arm-none-eabi-gdb

# Launch debug from Linux (Ubuntu/Debian)
LDB = gdb-multiarch
# Launch debug from MacOS
MDB = arm-none-eabi-gdb

# STM32 library path
DIR_INC = inc
DIR_ASM = asm
DIR_SRC = src
DIR_OBJ = obj

################################################################################
#							PROJECT FILES									   #
################################################################################

FILE_ASM = startup_stm32f303xc.s

FILE_SRC = main.c \
		   i2c.c \
		   syscall.c \
		   read_data_acc.c \
		   itm.c \
		   timer.c \
		   system_stm32f3xx.c \

FILE_OBJ = $(FILE_SRC:.c=.o)
FILE_OBJ += $(FILE_ASM:.s=.o)

OBJ = $(addprefix $(DIR_OBJ)/, $(FILE_OBJ))
ASM = $(addprefix $(DIR_ASM)/, $(FILE_ASM))
SRC = $(addprefix $(DIR_SRC)/, $(FILE_SRC))

################################################################################
#							GCC COMPILATION FLAGS							   #
################################################################################

# Architecture flags (ARM)
ARCH_FLAGS =-mthumb -mcpu=cortex-m$(CORTEX_M) -mlittle-endian -mthumb-interwork

# Debug flags
DBG_FLAGS = -g3

# Floating point flags (ARM)
FP_FLAGS =  -mfloat-abi=hard -mfpu=fpv4-sp-d16

# Include path flags
INC_FLAGS = $(addprefix -I , $(DIR_INC))

# DEFINE/Macro flags
DM_FLAGS =  -DSTM32F303xC -DUSE_FULL_ASSERT

# Compiling Optimization flags (add -0s for best optimization flag)
CO_FLAGS = -ffunction-sections -fdata-sections

# Warning flags
WRN_FLAGS = -Werror -Wall -Wextra

# All flags for GCC compiling step
GCC_FLAGS = $(ARCH_FLAGS) $(DBG_FLAGS) $(FP_FLAGS) $(INC_FLAGS) \
		  $(DM_FLAGS) $(CO_FLAGS) $(WRN_FLAGS)

################################################################################
#								LINKING										   #
################################################################################

# Linking Optimization flags
LO_FLAGS = --gc-sections

# Map File flags
MAP_FLAGS = -Map=$(NAME).map

# Linking Script flags
LS_FLAGS = -T ld_scripts/STM32F303VCTx_FLASH.ld

# Nano Library
NL_FLAGS = --library-path=/usr/lib/arm-none-eabi/newlib/thumb/v7e-m/fpv4-sp/hard/  --library=c_nano -u _printf_float --library=m --library=g

# Linker floating point library
LFP_FLAGS = --library-path=/usr/lib/gcc/arm-none-eabi/7.3.1/thumb/v7e-m/fpv4-sp/hard/ --library=gcc
#
# All flags for LD linking step
LD_FLAGS = $(LS_FLAGS) $(NL_FLAGS) $(LO_FLAGS) $(MAP_FLAGS) $(LFP_FLAGS)

################################################################################
#								MAKE RULES									   #
################################################################################

all: $(NAME)

$(NAME): $(OBJ)
	$(LD) $^ $(LD_FLAGS) -o $@
	@echo "\033[33;32m=== Compilation $(NAME)...\t\t\tDONE\033[0m"
	@echo "---------------------------------------------------------------------"

# Build *.c file
$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	@mkdir -p obj
	$(CC) $(GCC_FLAGS) -o $@ -c $<
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling:\033[0m" $<
	@echo "---------------------------------------------------------------------"

# Build *.s file
$(DIR_OBJ)/%.o: $(DIR_ASM)/%.s
	@mkdir -p obj
	$(CC) $(GCC_FLAGS) -o $@ -c $<
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling:\033[0m" $<
	@echo "---------------------------------------------------------------------"

# MacOsX flash and launch debug session
mlaunch:
	@$(MDB) -q $(NAME) -x openocd.gdb

# Linux (Debian) flash and launch debug session
llaunch:
	@$(LDB) -q $(NAME) -x openocd.gdb

# Delete all intermediate files
clean: 
	@rm -rf *.map
	@rm -rf obj
	@echo "\033[33;32m=== Cleaning project $(DIR_OBJ) directory and $(NAME).map...\t\tDONE\033[0m"

# Delete all intermediate files and executable file
fclean: clean
	@rm -rf $(NAME)	
	@echo "\033[33;32m=== Cleaning executable $(NAME)...\t\t\tDONE\033[0m"

# Clean and rebuild project
re: fclean all
