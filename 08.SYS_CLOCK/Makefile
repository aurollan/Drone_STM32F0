# make is alias for make all
.DEFAULT_GOAL := all

# Name of recipes
.PHONY: all llaunch mlaunch clean fclean re

################################################################################
#								PROJECT	CONFIG 								   #
################################################################################

# Selecting Core (STM32F0 DISCOVERY IS ARM M0)
CORTEX_M = 0
CORE = CM$(CORTEX_M)

# Project name
NAME = SYSCLOCK-$(CORE)

# Compiler, Linker & Debugger
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
DB = arm-none-eabi-gdb

# Launch debug from Linux (Ubuntu/Debian)
LDB = gdb-multiarch

# STM32 library path
DIR_INC = inc
DIR_ASM = ../03.STARTUP_FILE
DIR_SRC = src
DIR_OBJ = obj

# For library source file
vpath %.c ../01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/STM32F0xx_StdPeriph_Driver/src/
# For system_stm32f0xx.c file
vpath %.c ../01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/CMSIS/Device/ST/STM32F0xx/Source/Templates/TrueSTUDIO/
# For ARM Cortex M0 header file
vpath %.h ../01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/CMSIS/Include/
# For library header file
vpath %.h ../01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/STM32F0xx_StdPeriph_Driver/inc/

################################################################################
#							PROJECT FILES									   #
################################################################################

FILE_ASM = startup_stm32f030x8.s

FILE_SRC = main.c \
		   system_stm32f0xx.c \

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

# Floating point flags (ARM) no hardware floating point support
FP_FLAGS =  -mfloat-abi=soft 

# Include path flags
INC_FLAGS = $(addprefix -I , $(DIR_INC))

# DEFINE/Macro flags
DM_FLAGS =  -DSTM32F030x8 -DUSE_FULL_ASSERT

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
LS_FLAGS = -T ld_scripts/STM32F030R8Tx_FLASH.ld

# All flags for LD linking step
LD_FLAGS = $(LS_FLAGS) $(LO_FLAGS) $(MAP_FLAGS)

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

# Linux (Debian) flash and launch debug session
launch:
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
