# Start up file
I made a local copy of the start up file you can find here

    ../01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/CMSIS/Device/ST/STM32F0xx/Source/Templates/TrueSTUDIO/startup_stm32f030.s

I have commented this line causing me compilation issues

    /* Call static constructors */
        /* Useless for now */
        /* bl __libc_init_array */

This is why I made a local copy.

# Not enough information ?
Check out my other tutorial, I explain more in detail why and how we use a
start up file. Or look for answer on the internet, there is a lot of good
article on this topic.
