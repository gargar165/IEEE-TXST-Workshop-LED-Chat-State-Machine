#include "led.h"

/**
 * Creates the led object
 * 
 * This object sets up the pin at num + 11, forcing the user to
 * start at pin 11. The user will set the duty cycle of the pin
 * using set_percent.
 * 
 * @param num Indicates what pin starting at 11 will be used
 * @param set_percent The duty cycle of the LED as a whole number
 * @return none
 */
led::led(uint8_t num, uint8_t set_percent)
{
    id = num;
    pin = pin + num;
    percentage = set_percent;
    pinMode(pin, OUTPUT);
}

/**
 * Destroys the led object
 * 
 * This shouldn't run in your code, but this is required for
 * compilation
 * 
 * @return none
 */
led::~led()
{
    Serial.print("goodnight");
}

/**
 * State machine code for LEDs
 * 
 * This state machine blinks LEDs at a frequency of 1 Hz or a 
 * period of 1 second. There is a periodic signal, the duty cycle
 * can be set. The period can be changed by modifying the ranges
 * of the if statements, but they should always produce some
 * periodic signal. 
 * 
 * @return none
 */
void led::led_state_machine()
{
    switch(ls)
    {
        case LS_ON:
            if(elapsed_time > (percentage * 10))
            {
                digitalWrite(pin, LOW);
                ls = LS_OFF;
            }
            break;
        case LS_OFF:
            if(elapsed_time > 1000)
            {
                elapsed_time = 0;
                digitalWrite(pin, HIGH);
                ls = LS_ON;
            }
            break;
        default:
            Serial.println("How did you even get here");
            break;
    }
}