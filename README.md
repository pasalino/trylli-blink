# Trilly Blink 

## Overview 
Create a trylly blink with arduino mini pro 3V3 (8MHz) and sound sensor.
Trilly blink in a random mode in 10 different type.
When you clap your hands trilly blink fast.

[![Watch the video](https://raw.github.com/GabLeRoux/WebMole/master/ressources/WebMole_Youtube_Video.png)](https://youtu.be/ctat5pEXB5U)

## Electronic

![alt text](https://raw.githubusercontent.com/pasalino/)

### Scheme

In docs folder thereis a scheme with Fritzing format and PDF

### Component
* Arduino Pro Mini
* 2xled yellow
* 1xled white
* 2x100ohm resistor
* 1xdigital sound sensor

### Used Pin 
2     - In sound sensor
3,5,6 - Analog out in PWM
4     - Always on 

### Sound sensor
* LM393  DC4-6V Nero

## Tips

* For sound sensors i used interrupt function 
* For led i used PWM out for create a fade effect
* There is a random function for create different effect
