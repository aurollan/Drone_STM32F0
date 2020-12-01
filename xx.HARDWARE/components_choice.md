# Understanding components
Here is a good explaination about how to choose your quadricopter components:\
size/propeller/mortor/esc/battery
Ressources:
https://quadquestions.com/blog/2017/02/22/choose-right-size-motors-drone/

Frame choice
Ressources:
https://www.getfpv.com/learn/new-to-fpv/all-about-multirotor-fpv-drone-frame/

If you read carefully this article you should now be comfortable with the
principle. \
You can refer to this article if you are lost. \

## Objective
###	What we want to do ?
We want to create a medium unexpensive upgradable quadicopter.
If you want a bigger quadricopter you can choose bigger propellers and upgrade 
your Lipo battery and ESC accordingly.
If you want more torque you can choose a 3S lipo battery intead of 2S and keep 
the same motor but you have to get slighly larger propeller...
You have to adjust you components to fit your goal.

### How it works ?
You have to follow that order:
First, propellers are fitted to the size of your quadricopter.
Second, motors are build to work with specific propellers.

Motors needs a specific voltage and drain a certain amount of current (amps)

Third, ESC manage the motors and need to handle at least 20% more amps than 
needed by the motor at max power.
Finally, battery supply energy consumed by your components they need to fill 
the need of motors voltage and currents (amps).
Keep in mind that 4 motors consume 4 time more current.
For hight performance motors you need a really good battery.


## Finding the right information
### Exploring components documentation

#### Propellers
You won't find any sheet about propellers.
It's a simple product and all you need to know is:

- size (in inches)
- number of blades
- pitch

If you need detailled informations:
https://oscarliang.com/choose-propellers-mini-quad/
#### Motors sheet
There is everything you need in this sheet.
This is were you find information you need to chose your motors.
I will cover those informations in the next part.


#### ESC
There is a manual provided if you want to use it with preconfigured transmitter.
But we don't need it for our project. And everything we need is
written on the ESC.
ESC are electronic components designed to manage the brushless motors. We just 
need to "tell" the speed and the ESC translate it to the motor.
If you want to understand how it works just check the video below.

Ressource:
https://www.youtube.com/watch?v=uOQk8SJso6Q

#### Battery
This is the source of power for our quadricopter.
Most of the time there is no sheet with it.
Everything is written on the battery.
https://learn.sparkfun.com/tutorials/how-to-power-a-project/all

## Finding the right configuration
### Propellers
5 inch propller require
	210mm frame
	2204 2208, 2036 motor size
	2300 2600 kv motor

### Motors
7,4 volt
if (1000 == KV)
	7400 kv per motor

### ESC
25C
	25 * 1100mHa =  25 500 mHa => 25.5A

Max continous Amp draw (A)
= Battery capacity (Ah) x Discharge rate (C)

### Battery

I need motors wich max Amp < 5 and 4 of them:
	4 motors * 5max amp = 20 Amp

25 - 20 => 5 Amp left for safety







