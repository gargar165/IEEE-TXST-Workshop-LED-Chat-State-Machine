// this file handles the game play layout

// includes
#include <HardwareSerial.h>



// array for the game board
char game_board[3][3] = {{' ', ' ', ' '},
                           {' ', ' ', ' '},
                           {' ', ' ', ' '}};

// the game states
typedef enum
{

   GS_IDLE,

   GS_UPDATE_ARRAY_USER,
   GS_UPDATE_SCREEN_USER,
   GS_GET_COMP_INPUT,
   GS_UPDATE_SCREEN_COMP,

   GS_WINNER,
   GS_RESET,

   GE_NUM_OF,

} game_state_type;

// setting up the state variable
game_state_type gs = GS_IDLE;

// prints the game board
void print_board()
{

   // printing the output to the screen
   Serial.println("GAME:      ");
   Serial.println("  1|2|3");
   Serial.println("--------");
   Serial.print("1|");
   Serial.print(game_board[0][0]);
   Serial.print("|");
   Serial.print(game_board[0][1]);
   Serial.print("|");
   Serial.print(game_board[0][2]);
   Serial.println("|");
   Serial.println("--------");
   Serial.print("2|");
   Serial.print(game_board[1][0]);
   Serial.print("|");
   Serial.print(game_board[1][1]);
   Serial.print("|");
   Serial.print(game_board[1][2]);
   Serial.println("|");
   Serial.println("--------");
   Serial.print("3|");
   Serial.print(game_board[2][0]);
   Serial.print("|");
   Serial.print(game_board[2][1]);
   Serial.print("|");
   Serial.print(game_board[2][2]);
   Serial.println("|");
   Serial.println("--------");

   Serial.println("\nThis would be the game board if it worked...");
   Serial.println("But let's talk through our UART ports instead :)");

}

// printint updating the game baord
void update_game(char symbol)
{
   // stupid fix
   uint8_t row = (uint8_t)user_data[1] - 49;
   uint8_t col = (uint8_t)user_data[3] - 49;

   //Serial.println(col);
   // placing the symbol in a spot
   game_board[row][col] = symbol;

   // clearing out the input
   user_data[0] = '!';

}

uint8_t temp;

// the state machine controlling the game
void game_state_machine()
{
   if(temp != gs)
      Serial.println(gs);

   temp = gs;

   // if the input doesn't equal 0 it must be filled with data
   if (user_data[0] == 'G') {

      // if there is data setting it to the new data
      gs = GS_UPDATE_ARRAY_USER;

   }

   // if the game is in idle
   switch (gs) {

      case GS_IDLE:

         // do nothing because we are in idle

         // breaking out
         break;

      case GS_UPDATE_ARRAY_USER:

         // there is input so doing something with it
         update_game('O');

         // moving on to the next step
         gs = GS_UPDATE_SCREEN_USER;

         // breaking out
         break;

      case GS_UPDATE_SCREEN_USER:

         // updating the display for the user input
         print_board();

         // moving on to the next step
         gs = GS_GET_COMP_INPUT;

         // breaking out
         break;

      case GS_GET_COMP_INPUT:

         // getting the comp's option
         gs = GS_IDLE;

         break;

   }


}