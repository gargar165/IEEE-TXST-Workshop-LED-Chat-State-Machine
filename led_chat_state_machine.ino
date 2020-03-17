#include <avr/wdt.h>

#include "led.h"

// #defines are VERY useful tools for programmers when denoting numerical consts.
//   Think of them as keywords.
#define BAUD 9600

// setitng up the classes
led led1 = led(1, 50);
led led2 = led(2, 25); 

// standard setup function
void setup() {

   // setting up the interface in this file
   Serial.begin(BAUD);
   Serial1.begin(BAUD);

   // enabling the WDT
   wdt_enable(WDTO_1S);
}

// super loop
void loop() {

   // getting the input from the comm port
   input_state_machine();

   // updating led 1
   led1.led_state_machine();

   // updating led 2
   led2.led_state_machine();

   // petting the good boy
   wdt_reset();

}
