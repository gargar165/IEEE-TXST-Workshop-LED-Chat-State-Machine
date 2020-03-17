#ifndef LED_H
#define LED_H

#include <elapsedMillis.h>

/**
 * Implementation of the LED with a timer to track its duty cycle.
 * 
 * Each LED will be tied to an ID number. They will also connected
 * to a digital pin starting at D11. Each LED will have a soft timer
 * attached to it, so it can create a fake periodic signal.
 */
class led
{
private:
    uint8_t id;
    uint8_t percentage;
    uint8_t pin = 11;
    elapsedMillis elapsed_time = 0;

    /**
     * All the possible states for an LED.
     * 
     * These states are used in the led_state_machine function.
     */
    typedef enum
    {
        LS_ON, // LED On
        LS_OFF // LED Off
    } led_state_type;

    // State variable
    led_state_type ls = LS_ON;

public:
    led(uint8_t num, uint8_t set_percent);
    ~led();

    void led_state_machine();
};

#endif