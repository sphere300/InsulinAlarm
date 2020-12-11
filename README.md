# InsulinAlarm
A quick and dirty project to build a small device that sounds an alarm if the insulin is left out of the fridge too long.

# Part List:
* [Adafruit Trinket M0](https://www.adafruit.com/product/3500)
* [MCP9808 High Accuracy I2C Temperature Sensor Breakout Board](https://www.adafruit.com/product/1782)
* [Piezo Buzzer - PS1240] (https://www.adafruit.com/product/160)
* [Lithium Ion Polymer Battery - 3.7v 500mAh] (https://www.adafruit.com/product/1578)
* [JST-PH 2-Pin SMT Right Angle Connector] (https://www.adafruit.com/product/1769)
* Wire
* Snap Safe Safety Amber Vial 40 DR (Could be replaced with any large enough container though you would need to change one of the prints)

This project also assumes that you have a Lantus Insulin vial inside a Snap Safe Safety Amber Vial 40 DR container. The electronics can easily fit within the 40DR saftey vial with the insulin.

# Assembly Instructions:
*Desolder the DotStar LED, and the on LED.* 

With those two LEDs you are looking at a battery life with a 500 mAh battery in the neighborhood of 20 days. Without them it will last up to 347.22 days (realistically a lot less, but that's the theoretical cap with a 500 mAh battery).

The DotStar has a high idle current somewhere in the neighborhood of 1 mA. Without it and the on LED I was able to measure a standby current from the battery of 0.06 mA

I suggest you do this first as there is a very real chance you will break and destroy your Trinket M0 in the process of removing the SMT LED's. The good new is that they are cheap microcontrollers so it won't set you back much but its a tricky process. After removing the LEDs you should immediately test using a blink demo to ensure that after their removal there are no shorts and that the code is able to run.

![LED's to Remove](/Diagrams/Remove%20LED's.png)

Once you have the LED's removed you should proceed to wire everything up:

![Wiring Diagram](/Diagrams/Wiring.png)

Note in the parts list I list a 500 mAh battery but in the code I mention a 420 mAh battery that is because I used the 420 with a [JS Battery Extender Cable] (https://www.adafruit.com/product/1131) on my iteration. In retrospect the right angle JST connecter would have been better as cutting the cable and soldering a female connector to the short wire 420 mAh battery is tad fragile.

Once everything is wired you can snap it all together for something like this:

![Finished Top Side](/Pictures/Complete%20Top%20Side.png)
![Finished Bottom Side](/Pictures/Complete%20Bottom.png)

Push the assembly into the pill bottle and then put the electronics inside.

![All Together](/Pictures/Complete.png)

One last todo I may update in the coming days is to firmely attach the electronics and battery to the seperator as they move around a bit when I remove the insulin. As I mentioned in my description I recently bought the new lantus so I just wanted something quick and dirty. I am certain as I use it I will tweak and adjust this as I continue to give insulin to my cat twice daily but overal this is the first iteration of this.
