# Flash tool /!\ HARDWARE REQUIRED /!\
## Software flash tool
On the software part, I use openOCD to flash my microcontroller.
### Why use OpenOCD ?
It's a widely used and reliable tool.
You can use JTAG ore SWI or any protocol to debug your microcontroller.
It's free and powerfull.


## Software debug tool
I need another tool to provide debugger feature to OpenOCD: GDB.

    sudo apt-get install gdb-mutltiarch

### Why use GDB ?
GDB is a well known and powerfull debug tool available on ARM architecture.

## Hardware interface
I use a st-link v2.1 as an interface between my microcontroller and 
my computer. This is the official interface provided by manufacturer.
You could find it on any website and even cheap copy on aliexpress.

