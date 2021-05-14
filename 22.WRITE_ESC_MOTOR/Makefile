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
NAME = WRITE_ESC-$(CORE).elf

# Compiler, Linker & Debugger
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
DB = arm-none-eabi-gdb

# Launch debug from Linux (Ubuntu/Debian)
GDB = gdb-multiarch

# Flash utility
FLASH_TOOL = openocd

# Include directories given to GCC
# For our own include files. All file path are relative to this repository
DIR_INC_LOCAL = src
# For system_stm32f0xx.h file and stm32f0xx.h file
DIR_INC_DEVICE = ../01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/CMSIS/Device/ST/STM32F0xx/Include
# For ARM Cortex M0 header files
DIR_INC_CORTEX = ../01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/CMSIS/Include
# For Std library header files
DIR_INC_STD_LIB = ../01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/STM32F0xx_StdPeriph_Driver/inc
# For Std library stm32f0xx_conf.h header files (if you want to use FULL_ASSERT)
DIR_INC_STD_LIB_CONF = ../01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Projects/STM32F0xx_StdPeriph_Templates

# Start up file repository (I have commented a line so I made a local copy)
DIR_ASM = ../03.STARTUP_FILE

# Linker script file repository (I have commented a line so I made a local copy)
DIR_LKS = ../02.LINKER_SCRIPT

# OpenOCD debug script file repository
DIR_OCD_SCRIPT = ../08.SCRIPT

# Object files repository
DIR_OBJ = obj

# VPATH name to find *.c files
# For system_stm32f0xx.c file
vpath %.c ../01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/CMSIS/Device/ST/STM32F0xx/Source/Templates/
# For Std library source file
vpath %.c ../01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/STM32F0xx_StdPeriph_Driver/src/

# For our own source files
vpath %.c src/

# For microcontroller part
vpath %.c src/mcu/
vpath %.c src/mcu/clock/setup/
vpath %.c src/mcu/i2c/setup/
vpath %.c src/mcu/uart/setup/
vpath %.c src/mcu/pwm/setup/
vpath %.c src/mcu/uart/sensor_interface/
vpath %.c src/mcu/i2c/sensor_interface/
vpath %.c src/mcu/pwm/sensor_interface/

# For sensor part
vpath %.c src/sensors/
vpath %.c src/sensors/inertial_measurement_unit/
vpath %.c src/sensors/inertial_measurement_unit/mapping_and_configuration/
vpath %.c src/sensors/inertial_measurement_unit/mcu_interface/
vpath %.c src/sensors/inertial_measurement_unit/application_interface/accelerometer/
vpath %.c src/sensors/inertial_measurement_unit/application_interface/gyroscope/
vpath %.c src/sensors/motors/
vpath %.c src/sensors/motors/mcu_interface/
vpath %.c src/sensors/motors/application_interface/
vpath %.c src/sensors/motors/mapping_and_configuration/

# For application part

################################################################################
#							PROJECT FILES									   #
################################################################################

# Start up file name (I have commented a line so I made a local copy)
FILE_ASM = startup_stm32f030.s

# Linker script file name (I have commented a line so I made a local copy)
FILE_LKS = STM32F030R8Tx_FLASH.ld

# Files used for building project
FILE_SRC = main.c \
		   syscall.c \
		   init_mcu.c \
		   init_sensors.c \
		   setup_imu.c \
		   setup_motors.c \
		   dronef0_clock.c \
		   dronef0_uart.c \
		   dronef0_uart_tx_rx.c \
		   dronef0_i2c.c \
		   dronef0_i2c_rd_wr.c \
		   pwm_write.c \
           stm32f0xx_rcc.c \
           stm32f0xx_tim.c \
           stm32f0xx_i2c.c \
           stm32f0xx_usart.c \
           stm32f0xx_gpio.c \
		   stm32f0xx_flash.c \
		   system_stm32f0xx.c \
		   gyroscope.c \
		   accelerometer.c \
		   imu_mcu.c \
		   power.c \
		   motors_mcu.c \


	

FILE_OBJ = $(FILE_SRC:.c=.o)
FILE_OBJ += $(FILE_ASM:.s=.o)

OBJ = $(addprefix $(DIR_OBJ)/, $(FILE_OBJ))
ASM = $(addprefix $(DIR_ASM)/, $(FILE_ASM))
# We are using vpath now so we don't have to bother with file path for 
# *.c and *.h

################################################################################
#							GCC COMPILATION FLAGS							   #
################################################################################

# Architecture flags (ARM)
ARCH_FLAGS =-mthumb -mcpu=cortex-m$(CORTEX_M) -mlittle-endian -mthumb-interwork

# Debug flags
DBG_FLAGS = -g3

# Floating point flags (ARM) no hardware floating point support, only soft
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

# DEFINE/MACRO flags
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
LS_FLAGS = -T $(DIR_LKS)/$(FILE_LKS)

# Linking nano librarie
LN_FLAGS = --library-path=/usr/lib/arm-none-eabi/newlib/thumb/v6-m/ --library=c_nano -u _printf_float

# Linking libgcc.a
LG_FLAGS = --library-path=/usr/lib/gcc/arm-none-eabi/7.3.1/thumb/v6-m/ --library=gcc

# All flags for LD linking step
LD_FLAGS = $(LS_FLAGS) $(LO_FLAGS) $(MAP_FLAGS) $(LN_FLAGS) $(LG_FLAGS)

################################################################################
#								MAKE RULES									   #
################################################################################

all: $(NAME)

$(NAME): $(OBJ)
	$(LD) $^ -o $@ $(LD_FLAGS)
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
debug:
	@$(GDB) -q $(NAME) -x $(DIR_OCD_SCRIPT)/openocd.gdb

flash: all
	@$(FLASH_TOOL) -f interface/stlink-v2.cfg -f target/stm32f0x.cfg -c "program $(NAME) verify reset exit"

# Delete all intermediate files
clean: 
	@rm -rf *.map
	@rm -rf obj
	@echo "\033[33;32m=== Cleaning project $(DIR_OBJ) repository and $(NAME).map...\t\tDONE\033[0m"

# Delete all intermediate files and executable file
fclean: clean
	@rm -rf $(NAME)	
	@echo "\033[33;32m=== Cleaning executable $(NAME)...\t\t\tDONE\033[0m"

# Clean and rebuild project
re: fclean all
