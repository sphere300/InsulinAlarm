/*

  Insulin Alarm Code

  This code is intended to be a very quick and dirty insulin alarm that goes off if the container it is stored in is left outside of the fridge too long. 
  
  I have a cat who is now diabetic, and after leaving the insulin out of the fridge one too many times by accident I decided to makee this alarm so that I don't need to keep buying more insulin.

  This is a very simple set of code designed to work with the adafruit trinket M0 board, a MCP9808 temperature sensor on adafruits break out board, a lithium ion battery, and a simple PS1240 Buzzer.
  
  Created by Sphere300

  Warnings and disclaimers:
  I am not an expert at firmware or hardware design and everything I do in the code and with the hardware may be flawed, so use this code and hardware at your own risk.
  
  This is a hobby project and is shared with others in case they find it useful. This code is not exensivly tested and may fail unexpectedly for any reason, 
  and as such it is NOT intended to be used in a medical setting or in any scenario where its failure may cause harm or loss of life.

  License:
  All materials for this project are released under te GNU Lesser General Public License 2.1. The Adafruit MCP9808 Library uses an MIT license and the RTCZero library is also GNU Lesser Publc license 2.1.
  You can find their work hosted in the arduino libraries or on git hub:
  https://github.com/arduino-libraries/RTCZero
  https://github.com/adafruit/Adafruit_MCP9808_Library

  This code was initially based on the SimpleRTCAlarm demo included with the RTC Libary.

  This code was created on:
  December 11 2020  
   
*/

#include <RTCZero.h>
#include "Adafruit_MCP9808.h"

Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

/* Create an rtc object */
RTCZero rtc;

//Buzzer bins
int buzzer1 = 3;
int buzzer2 = 4;

//Build in Red LED (the one we did not desolder)
int led = 13;

//Some time constants to setup the RTC
/* Change these values to set the current initial time */
const byte seconds = 0;
const byte minutes = 00;
const byte hours = 17;
/* Change these values to set the current initial date */
const byte day = 17;
const byte month = 11;
const byte year = 15;

//Track how long we have been on os we can indicate when we need to recharge the battery.
long onCount = 0;

void setup()
{
  //Indicate we are ready to program
  digitalWrite(led, HIGH);

  //Delay for 60 seconds to let us reprogram it if we need to (Standby screws up the USB avr)
  delay(60000); //Let us reprogram the board before we put the board to sleep.

  //
  digitalWrite(led, LOW);

  //Ensure we can talk to the temperature sensor
  if (!tempsensor.begin(0x18)) {
    
    //If we can't measure temperature then we are not going anywhere fast.
    while (1)
    {
      //Pulse the LED to let us know it can't talk to the Temp Sensor.
      digitalWrite(led, HIGH);
      delay(1000);
      digitalWrite(led, LOW);
      delay(1000);
    }
  }
  //Choose the fastest temperature setting with +-0.5°C in 30 ms
  tempsensor.setResolution(0); 
  //Shut it down to save power
  tempsensor.shutdown_wake(1);

  //Setup the buzzer
  pinMode(buzzer1, OUTPUT); 
  pinMode(buzzer2, OUTPUT);
  //Set the buzzer off
  digitalWrite(buzzer1, LOW);
  digitalWrite(buzzer2, LOW);
  
  //Start up the clock
  rtc.begin();
  rtc.setTime(hours, minutes, seconds); //We have no idea what the real time is ... 
  rtc.setDate(day, month, year);
  //Set the first alarm to be 1 minute from now 
  rtc.setAlarmTime(17, 05, 00);
  rtc.enableAlarm(rtc.MATCH_HHMMSS);
  rtc.attachInterrupt(alarmMatch);
  //Got to sleep.
  rtc.standbyMode();
  

}

void loop()
{
  onCount += 1;
  //Assuming a 420 mAh and based on standby consumption with the Dotstar and On LED's removed (0.06 mA) we should have an ideal longevity of about 291.7 days,
  // but we are chilling battery, it will lose power over time, and it may not be fully charged so lets turn on the low batt after 75% of the expected life or 218.75 days. 
  //The board will be asleep most of the time unless you leave it outside the fridge, so we assume that the standby dominates the power consumption. 
  //Based on that We can make an assumption that each sleep wake cycle dominates the on time. 
  //Ignoring the roughly 30ms per sleep cycle this we get 63000 cycles of 5 minute sleeps before 75% of the ideal battery life is consumed.
  if (onCount > 63000) {
    // Turn on to indicate low battery, yes it will consume power but without it we will never know when to replace the battery, and in theory you will use the insulin every day. 
    digitalWrite(led, HIGH);
  }
  
  //Wakeup the temperature sensor:
  tempsensor.wake();   // wake up, ready to read!
  //Read the temp
  float c = tempsensor.readTempC();
  while (c > 16)
  {
    //If the temp is > 16 then start buzzing. In theory it should be colder so this will turn off faster when its put back in the fridge.
    //buzz for 10 seconds
    for (int j = 0; j <= 50; j++) { //Buzz for 10 seconds.
      for (int i = 0; i <= 50; i++) {
        //Make a square wave. Set the pins to opposite values to give us a bit more sound
        digitalWrite(buzzer1, HIGH);
        digitalWrite(buzzer2, LOW);
        delay(1);               
        digitalWrite(buzzer1, LOW);
        digitalWrite(buzzer2, HIGH);
        delay(1);
      }
      for (int k = 0; k <= 100; k++) {
        //Make a higher pitched square wave
        digitalWrite(buzzer1, HIGH);
        digitalWrite(buzzer2, LOW);
        delay(0.5);
        digitalWrite(buzzer1, LOW);
        digitalWrite(buzzer2, HIGH);
        delay(0.5);
      }
    }
    //Check the temperature before we loop again.
    c = tempsensor.readTempC();
  }
  //Once the temperature drops below 16°C go back to sleep for a bit.
  tempsensor.shutdown_wake(1); // shutdown MSP9808 - power consumption ~0.1 mikro Ampere, stops temperature sampling
  //Reset the alarm for 5 minute from now. IE wakeup once every 5 minutes and check if its above temp.
  int alarmMinutes = rtc.getMinutes();
  alarmMinutes += 5;
  if (alarmMinutes >= 60) {
    alarmMinutes -= 60;
  }

  rtc.setAlarmTime(rtc.getHours(), alarmMinutes, rtc.getSeconds());
  
  rtc.standbyMode();    // Sleep until next alarm match*/
}

void alarmMatch()
{
  //We don't currently do anything in the interupt we just need it to wake from standby.
}
