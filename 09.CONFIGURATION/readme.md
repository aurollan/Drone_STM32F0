# Configuration
You just buy your microcontroller and your st-link interface, nice.
This is the next step before we start to code.
We have some peripheral to connect to our microcontroller.
For this project we have to communicate with:

    gy-521 inertial measurment unit sensor
    our computer
    ESC (which drive our brushless motor).

Each of this peripheral use a communication bus available on
our microcontroller.
So we have to match a communication bus and associated GPIO to each 
of our peripheral.

Communication bus we need:

    I2C for gy-521
    U(S)ART for computer
    TIMER with PWM to for ESC

For my microcontroller here are the choice I made:

    I2C1 using the following GPIO:
        GPIOB 08 => SCL
        GPIOB 09 => SDA

    USART1 using the following GPIO:
        GPIOA 14 => TX
        GPIOA 15 => RX

    TIM3 timer with 4 channels PWM using the following GPIO:
        GPIOB 04 => channel 1
        GPIOB 05 => channel 2
        GPIOB 01 => channel 3
        GPIOB 02 => channel 4

Most of the time you have more that 1 possibility for each of your communication bus.
You can make your own choice.
We will create associated variable in on configuration header file
we use in our project.

