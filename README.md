# ieee_workshop_state_machine
HUGE thanks to @Robertsbarr from Clemson University on this one. I modified the crud out of it, but the led class originated from code he made.

Needs elapsedMillis library.
https://github.com/pfeerick/elapsedMillis/archive/master.zip

  Essentially, this project demonstrates how to use elapsedMillis to the programmers's advantage so that the programmer can refrain from using the delay() to produce a soft PWM signal while doing other stuff in the background. This state machine code does two things.
  
  1: It attempts to create a 1 Hz signal whose duty cycle is affected by the second parameter in the led object's constructor. If I say something like "led led1(pin, 45)", then the state machine will try to produce a periodic signal of 1 Hz at 45% duty cycle.
  
  2: It will check if either Serial or Serial1 are used. If so, it will appropriately print "Me: " or "Guest: " to show which UART port is being used. It will then recycle the same user_data buffer to prevent having to create two separate buffers.
  
  Considering that the Mega's UART buffers are 63 bytes, making USER_BUFFER_SIZE 512 bytes is probably very unnecessary. However, the Mega's UART buffers can be changed be undefining both SERIAL_TX_BUFFER_SIZE and SERIAL_RX_BUFFER_SIZE, then redefining them to any size, as long as it is below 256 to prevent irratic behavior.
  
  If you're curious as to how this works, go to C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino.
  You can sift through the HardwareSerial (or any part of Arduino) files here, but DON'T CHANGE ANYTHING UNLESS YOU KNOW WHAT YOU'RE DOING! I don't even change anything here to allow all my projects to behave as expected.
