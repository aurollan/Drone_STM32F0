#!bin/sh
cd /tmp
openocd -f interface/stlink-v2.cfg -f target/stm32f0x.cfg
