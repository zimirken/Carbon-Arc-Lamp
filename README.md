# Carbon-Arc-Lamp
Code for the controller for my automatic carbon arc lamp.

https://youtu.be/h0YubyjSBLM

I was watching a Technology Connections video about antique lighting, and he mentioned carbon arc lamps. I was intrigued, so I started to look into them. Seeing videos of people making their own was very dissapointing, as there wasn't much more complexity than holding two rods together. I wanted one that would be able to control itself. The original automatic ones used a solenoid in series with the arc that would pull the rods away as the current increased. While this was doable, I chose to use a motor driving a linear carriage instead. This was much easier to build.

The motor control system senses the voltage drop across the ballast resistor, to try to maintain that voltage drop (and thus current) at a specific level or range. I originally tried to do this with discrete transistors, as that fits the vintage theme, But after having many issues and having to rebuild a couple circuit boards I gave up and switched to an attiny85 driving an h-bridge IC. There is also a switch that turns the motor on full reverse.

This lamp uses a custom built carriage to move the lower electrode, because I already had a gearmotor and the other stuff laying around. In the future I would just buy a small 12V linear motor for $30. The motor I'm using is a 12V 60rpm gear motor.

The lamp is powered by 2x 12v lead acid batteries in series. The ballast resistor is a 2 ohm 250W resistor with a selectable tap. The ground for the circuit is run from a separate wire directly from the battery terminal, and the current sense input is across the resistor and all wiring all the way up to the inside of the lamp. With the current tap position, I think I have a total of 1-1.5ohms.

The current sense input is connected to a voltage divider using 10k resistors, and then has a diode clamping it to VCC, as when the rods touch to start the arc, the voltage jumps to 18volts. 

The program is fairly straightforward. There's a potentiometer to give a comparison input. At 0v sense, the motor is driven full forward, decreasing to stop as it approaches the comparison voltage. At 5V input, the motor is full reverse, decreasing to stop at the comparison input again. Since I have a 12V motor bieng driven by 24V, and I don't necessarily need to drive it at full speed, I have a way to set the max motor drive PWM. If the retract switch is on at powerup, and turned off within 2 seconds, the arduino will read the potentiometer voltage, scale it down to 0-255, and save that as the max motor drive pwm. This also has the effect of controlling the gain and/or dead zone of the program, as the motor won't move without a minimum amount of drive pwm.


