uint8_t temp_1 = 0;

void input_state_machine()
{

   // local variable
   uint8_t user_loop = 0;

   // checking the comm port
   while (Serial.available() > 0)
   {
      // reading in the data
      user_data[user_loop] = (char)Serial.read();

      // upping loop
      user_loop++;

      // delaying a little
      delay(5);

   }

   user_data[user_loop] = 0;

   if(user_data[0] != 0) {
      Serial.print("Me: ");
      Serial.println(user_data);
      Serial1.write(user_data);
   }
   
   memset(user_data, 0, 512);
      
   delay(5);

   user_loop = 0;

   while (Serial1.available() > 0)
   {
      // reading in the data
      user_data[user_loop] = (char)Serial1.read();

      // upping loop
      user_loop++;

      // delaying a little
      delay(5);
   }

   user_data[user_loop] = 0;

   if(user_data[0] != 0) {
      Serial.print("Guest: ");
      Serial.print(user_data);
   }

}