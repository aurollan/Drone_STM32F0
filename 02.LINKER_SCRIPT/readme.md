# Linker script
I made a local copy of the linker script you can find here

    ../01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Projects/STM32F0xx_StdPeriph_Templates/TrueSTUDIO/STM32F030/STM32F030R8_FLASH.ld

I have commented those three (last) lines causing me compilation issues

    /* Remove information from the standard libraries */
    /DISCARD/ :
    {
        /* libc.a ( * ) */
        /* libm.a ( * ) */
        /* libgcc.a ( * ) */
    }

This is why I made a local copy.

# Not enough information ?
Check out my other tutorial, I explain more in detail why and how we use a
linker script. Or look for answer on the internet, there is a lot of good
article on this topic.
