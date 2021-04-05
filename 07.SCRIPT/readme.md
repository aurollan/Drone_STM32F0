# Scripts
## itm_launch.sh
This script rely on a little rust program to log in real time 
data send trough ITM.
I used to communicate with my microcontroller through ITM before but i don't 
use it anymore. For thy project we will communicate through UART.

## minicom.sh
Just launch the minicom to send and receive from uart.

## minirc.dfl
A minicom configuration file matching the microcontroller UART configuration.
We nned it to decode uart communication send on the bus.


## openocd.gdb
A script of command to enter in debug mode with openOCD.

## openocd_launch.sh
Just a command to launch openOCD with the right argument.

## Why use scripts ?
Those steps are easy to write but it is really annoying to repeat them each 
time.

## Can I make my own ?
Yes, you should.




