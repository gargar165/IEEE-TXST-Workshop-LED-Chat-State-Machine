// Let's try to keep everything input related here.
#define USER_BUFFER_SIZE 512

// the global input variable
char user_data[USER_BUFFER_SIZE];

// Checks if my serial or serial1 is used.
// Reads all data into user_data if so, and prints to dummy terminal.
void input_state_machine()
{

   // iterator for while loops
   uint8_t user_loop = 0;

   // check my serial if I typed anything
   while (Serial.available() > 0)
   {
      // reading in the data
      user_data[user_loop] = (char)Serial.read();

      // upping loop
      user_loop++;

      // delaying a little because signal may not have reached my buffer yet
      delay(5);

   }

   // The way a CPU recognizes the end of a string is by reading 0x00
   //   (that is just denoting zero in hexadecimal). By setting this
   //   to zero here, we can denote the end of the string we sent.
   user_data[user_loop] = 0;

   // Check if we just zeroed out the first element
   if(user_data[0] != 0) {
      Serial.print("Me: ");
      Serial.println(user_data);
      Serial1.write(user_data);
   }
   
   // This just means "set the data at user_data and the next 511 addresses to zero".
   //   But this number is relative to the USER_BUFFER_SIZE define.
   // A CS1428 way of doing this would be
   // for(int i = 0; i < 512; i++)
   //   user_data[i] = 0;
   //
   // It's just an easy one-liner.
   memset(user_data, 0, USER_BUFFER_SIZE);
      
   // Again, delay 5 ms.
   // FUN FACT: If I recall correctly, this is around 10 times LIGHTER
   //   than the delay function. So I try to use this method instead to
   //   make my code more efficient.
   for(uint8_t i = 0; i < 5; i++)
      delayMicroseconds(1000);

   // Reset the iterator
   user_loop = 0;

   // Check the RX1/TX1 pins
   while (Serial1.available() > 0)
   {
      // reading in the data
      user_data[user_loop] = (char)Serial1.read();

      // upping loop
      user_loop++;

      // delaying a little
      for(uint8_t i = 0; i < 5; i++)
         delayMicroseconds(1000);
   }

   // Null-terminate
   user_data[user_loop] = 0;

   // Check for used buffer
   if(user_data[0] != 0) {
      Serial.print("Guest: ");
      Serial.print(user_data);
   }

}
