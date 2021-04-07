# Project tree

14.EXAMPLE_STEP
|
|_____> Makefile
|
|_____> readme.md
|
|_____> src
        |
        |______> main.c
        |
        |______> mcu
        |       |
        |       |____> setup clock
        |       |
        |       |____> setup pwm
        |       |
        |       |____> setup uart
        |       |
        |       |____> setup i2c
        |
        |______> sensors
        |       |
        |       |____> setup communication
        |       |
        |       |____> setup motors
        |       |
        |       |____> setup gyro
        |       |
        |       |____> setup acc
        |
        |______> drone application
                |
                |____> start
                |
                |____> move
                |
                |____> balance
                |
                |____> stop

## Explenation
### MCU
In the `mcu` repository we will setup the microcontroller communication 
interfaces.

### SENSORS
In the `sensors` repository we will translate raw data received to actual 
information we need.
And actual information we want to send to raw data.

### drone application
In the `drone application` repository we will code the drone behavior sending, receiving data.
And reaction to those informations.

