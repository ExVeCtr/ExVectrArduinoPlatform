# ExVectr Arduino Platform Implementation
This repository is an implementation of the required functions to get a ExVeCtr Project running on Arduino.
Implemented classes are inside the namespace `VCTR::Platform`.
## Dependencies:
The ExVectr libraries below are required by this library to function.
- Core 
- HAL.
## ToDo ##
- [X] Implement time base.
- [X] Implement basic IO (GPIO, ADC, PWM, ~~DAC~~). DAC is not really supported by most boards. Must be implemented by board specific branches.
- [ ] Implement basic Bus (~~I2C~~, ~~SPI~~, Serial).
- [ ] Documentation.
## **This project is under initial development. Things will probably break.**