#include <HardwareSerial.h>
#include <elapsedMillis.h>
#include <avr/wdt.h>

// the input variable
char user_data[512];

class led
{
public:
   // constructor
   led(uint8_t num, uint8_t per) {

      // getting the ID
      id = num;

      // setting up the pin number
      pin = pin + num;

      // setting percentage
      percentage = per;

      // setting up the pin mode
      pinMode(pin, OUTPUT);

      Serial.println(pin, DEC);

   }

   // setting up the incoming parser
   void update_timing() 
   {

      // percentage of time on in tens
      percentage = user_data[2] - 48;

      // resetting the input data
      user_data[0] = '!';

   }

   // updating the led
   void led_state_machine() 
   {

      /* // parsing if there is an update for me
      if (user_data[0] == 'L'){

         // checking the next character
         if (user_data[1]-48 == id) {

            // update percentage
            update_timing();

         }

      } */

      // switch case for the different states
      switch (ls) {

         case LS_ON:

            // checking how long it has been on
            if (elapsed_time > (percentage * 10)) {

               // turning on the LED
               digitalWrite(pin, LOW);

               // moving to turn off the led
               ls = LS_OFF;

            }

            // breaking out
            break;

         case LS_OFF:

            // if the loop is at 100%
            if (elapsed_time > 1000) {

               // turning on the LED
               digitalWrite(pin, HIGH);

               // resetting the on loop timer
               elapsed_time = 0;

               // moving to turn off the led
               ls = LS_ON;

            }

            // breaking out
            break;

      }

   }

private:
   uint8_t loop = 0;
   uint8_t id;
   uint8_t percentage = 0;
   uint8_t pin = 11;
   elapsedMillis elapsed_time = 0;

   // led states
   typedef enum
   {

      LS_ON,
      LS_OFF,

   } led_state_type;

   // setting up the state variable
   led_state_type ls = LS_ON;

};

// setitng up the classes
led led1 = led(1, 50);
led led2 = led(2, 25); 

// standard setup function
void setup() {

   // setting up the interface in this file
   Serial.begin(9600);
   Serial1.begin(9600);

   // printing the board
   //print_board();

   // enabling the WDT
   wdt_enable(WDTO_1S);
}

// super loop
void loop() {

   // getting the input from the comm port
   input_state_machine();

   // updating the game from user input
   //game_state_machine();

   // updating led 1
   led1.led_state_machine();

   // updating led 2
   led2.led_state_machine();

   // petting the good boy
   wdt_reset();

}