# connection to 
target remote: 3333
# loading exe
load
# Set breakpoint to main
break main
# globally enable the ITM and redirect all output to itm.txt
monitor tpiu config internal itm.txt uart off 72000000
# enable the ITM port 0
monitor itm port 0 on
# launch program
continue
