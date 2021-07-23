# System Clock
In this part we want the system clock to run at expected speed.

## Default clock speed
If you want your microcontroller to run at max speed, we must set it up.
Fortunatly, this is what the `SetSysClock()` function do for us.
You can find this function in 

    01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/CMSIS/Device/ST/STM32F0xx/Source/Templates/system_stm32f0xx.c

As explained in the `system_stm32f0xx.c` file: it use the PLL clock based on 
the HSE (Hight Speed External) clock to get the 48 Mhz frequency.

`SetSysClock()` is called by the `SystemInit()` function.
And finally `SystemInit()` function is called in the start up file 
`08.SYS_CLOCK/asm/startup_stm32f030.s` just before your main and just after 
initializing data sections.

Long story short, it's already done.

## Change clock speed
You may want to slow down your microcontroller clock and this is what we do in 
this part. I want to run the drone with a clock set up to 8 Mhz. If it's not 
I will set it up to 48 Mhz.


Now let's setup a communication between the microcontroller and our computer 
with a simple UART and Bluetooth (or FTDI).
