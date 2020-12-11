" Setting path to project
let g:ale_c_cc_options="-std=c11
            \ -DSTM32F030X8
            \ -Wall
            \ -Werror
            \ -Wextra
            \ -I 01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/CMSIS/Device/ST/STM32F0xx/Include
            \ -I 01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/CMSIS/Include
            \ -I 01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/STM32F0xx_StdPeriph_Driver/inc
            \ -I 01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Projects/STM32F0xx_StdPeriph_Templates"
let g:ale_cpp_cc_options="-std=c++14
            \ -DSTM32F030X8
            \ -Wall
            \ -Werror
            \ -Wextra
            \ -I 01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/CMSIS/Device/ST/STM32F0xx/Include
            \ -I 01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/CMSIS/Include
            \ -I 01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/STM32F0xx_StdPeriph_Driver/inc
            \ -I 01.LIBRARY/STM32F0xx_StdPeriph_Lib_V1.5.0/Projects/STM32F0xx_StdPeriph_Templates"

let g:gutentags_ctags_exclude = ['*ccls*']
