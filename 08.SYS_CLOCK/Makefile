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
NAME = SYS_CLOCK-$(CORE)

# Compiler, Linker & Debugger
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
DB = arm-none-eabi-gdb

# Launch debug from Linux (Ubuntu/Debian)
LDB = gdb-multiarch

# Include directories given to GCC
# For our own include files
DIR_INC_LOCAL = inc
# For system_stm32f0xx.h file and stm32f0xx.h file
DIR_INC_DEVICE = ../01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/CMSIS/Device/ST/STM32F0xx/Include
# For ARM Cortex M0 header files
DIR_INC_CORTEX = ../01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/CMSIS/Include
# For Std library header files
DIR_INC_STD_LIB = ../01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/STM32F0xx_StdPeriph_Driver/inc
# For Std library stm32f0xx_conf.h header files (if you want to use FULL_ASSERT)
DIR_INC_STD_LIB_CONF = ../01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Projects/STM32F0xx_StdPeriph_Templates

# Start up file directory (I have commented a line so I made a local copy)
DIR_ASM = asm
 
# Useless now
DIR_SRC = src

# Object files directory
DIR_OBJ = obj

# VPATH name to find *.c files
# For system_stm32f0xx.c file
vpath %.c ../01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/CMSIS/Device/ST/STM32F0xx/Source/Templates/
# For Std library source file
vpath %.c ../01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/STM32F0xx_StdPeriph_Driver/src/
# For our own source files
vpath %.c src/

################################################################################
#							PROJECT FILES									   #
################################################################################

# Start up file name (I have commented a line so I made a local copy)
FILE_ASM = startup_stm32f030.s

# Files used for building project
FILE_SRC = main.c \
           stm32f0xx_rcc.c \
           stm32f0xx_gpio.c \
		   system_stm32f0xx.c \

FILE_OBJ = $(FILE_SRC:.c=.o)
FILE_OBJ += $(FILE_ASM:.s=.o)

OBJ = $(addprefix $(DIR_OBJ)/, $(FILE_OBJ))
ASM = $(addprefix $(DIR_ASM)/, $(FILE_ASM))
# We are using vpath now so we don't have to bother with file path for 
# *.c and *.h
# SRC = $(addprefix $(DIR_SRC)/, $(FILE_SRC))

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
INC_LOCAL_FLAG = $(addprefix -I , $(DIR_INC_LOCAL))
INC_DEVICE_FLAG = $(addprefix -I , $(DIR_INC_DEVICE))
INC_CORTEX_FLAG = $(addprefix -I , $(DIR_INC_CORTEX))
INC_STD_LIB_FLAG = $(addprefix -I , $(DIR_INC_STD_LIB))
INC_STD_LIB_CONF_FLAG = $(addprefix -I , $(DIR_INC_STD_LIB_CONF))

# All flags together
INC_FLAGS = $(INC_LOCAL_FLAG) $(INC_DEVICE_FLAG) $(INC_CORTEX_FLAG) \
			$(INC_STD_LIB_FLAG) $(INC_STD_LIB_CONF_FLAG)

# DEFINE/Macro flags
DM_FLAGS = -DSTM32F030X8

# Both following define come together (for using FULL_ASSERT)
DM_FLAGS += -DUSE_FULL_ASSERT
DM_FLAGS += -DUSE_STDPERIPH_DRIVER

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

# Linking Script file (I have commented 3 line a the end so I made a local copy)
LS_FLAGS = -T ld_script/STM32F030R8Tx_FLASH.ld

# All flags for LD linking step
LD_FLAGS = $(LS_FLAGS) $(LO_FLAGS) $(MAP_FLAGS)

################################################################################
#								MAKE RULES									   #
################################################################################

all: $(NAME)

$(NAME): $(OBJ)
	$(LD) $^ $(LD_FLAGS) -o $@
	@echo "\033[33;32m=== Linking $(NAME)...\t\t\tDONE\033[0m"
	@echo "---------------------------------------------------------------------"

# Build *.c file
$(DIR_OBJ)/%.o: %.c
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
