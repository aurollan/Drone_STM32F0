# Why use a library
We use a library because we don't want to code everything from scratch.
If you want to start we everything from scratch you can check my other 
tutorial.
This particular library is an Hardware Abstraction Layer.
It does only one thing that we need:
- configure and use register

We will code eveything else.

# Why this library
Because it's an error-proof library widely used.
It is (was) developed by the manufacturer.
It is easy to understand and well documented.

# Do i need every file in this library ?
No you won't we just need "Libraries/STM32F30x_StdPeriph_Driver/" and some 
headers.

# Could I use another library ?
Yes, the first part is just setting up our component, and communicate with
peripherals (the Hardware Abstraction Layer).
You could use another Hardware Layer abstraction library like
libopencm3 for example.

|---------------------------------------------------------------|
|                   Application layer input/output              |
|---------------------------------------------------------------|
        /\           /\           ||              /\  
        ||           ||           ||              ||
    angle var       angle     motor power     communication
        ||           ||           ||              ||       
        ||           ||           \/              \/
|---------------------------------------------------------------|
|                   Raw data interpretation layer               |
|---------------------------------------------------------------|
        /\           /\           ||              /\  
        ||           ||           ||              ||
    gyro data     acc data  duty cycle data   string data
        ||           ||           ||              ||       
        ||           ||           \/              \/
|---------------------------------------------------------------|
|           I2C            |   PWM (TIMER) |       USART        |
|---------------------------------------------------------------|
|                   Hardware Abstraction Layer                  |
|---------------------------------------------------------------|
