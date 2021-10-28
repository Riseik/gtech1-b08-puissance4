#include <stdio.h>
#include <stdlib.h>

char grid[6][9];     //Initialization of the size of the grid.

int line;     //Variable that will count the lines.
int column;     //Variable that will count the columns.
int victory;     //Variable that will be remember if the game is finished or not.
int play_again = 1;     //Variable that will remember if the players want to play or not.


void basic_grid()     //Function for the basic aspect and the reset of the grid.
{
  printf("  1 2 3 4 5 6 7 \n");     //There will be a nmber for each column.
  printf("_________________\n");     //There will be "_" above and below the grid.
  for (line = 0; line < 6; line++)
  {
    for (column = 0; column < 9; column++)
    {
      if (column == 0 || column == 8)
      {
        grid[line][column] = '|';     //The sides will be delimited by "|".
      }
      else
      {
        grid[line][column] = '.';     //The grid will be full of ".".
      }
      printf("%c", grid[line][column]);
      printf(" ");
    }
    printf("\n");
  }
  printf("_________________\n");
}

void game_grid()     //Function for the grid with the placed tokens.
{
  printf("  1 2 3 4 5 6 7 \n");
  printf("_________________\n");
  for (line = 0; line < 6; line++)
  {
    for (column = 0; column < 9; column++)
    {
      if (column == 0 || column == 8)
      {
        grid[line][column] = '|';
      }
      else if (grid[line][column] != '.')
      {
        if (grid[line][column] == 'X')
        {
          printf("\e[1;34m%c\e[0m", grid[line][column]);     //\e are for colouring the tokens.
        }
        else
        {
          printf("\e[1;31m%c\e[0m", grid[line][column]);
        }
        printf(" ");
        continue;
      }
      //"If" above put the placed token in the grid.

      else
      {
        grid[line][column] = '.';
      }
      printf("%c", grid[line][column]);
      printf(" ");
    }
    printf("\n");
  }
  printf("_________________\n");
}

void test_victory(int player)     //Function for the test of a winner, which means 4 same tokens in a row.
{
  for (line = 0; line < 6; line++)
  {
    for (column = 1; column < 5; column++)
    {
      if (grid[line][column] == grid[line][column + 1] && grid[line][column] == grid[line][column + 2] && grid[line][column] == grid[line][column + 3] && grid[line][column] != '.')
      {
        victory = 1;
      }
    }
  }
  //"For" above analyze the horizontal.

  for (line = 0; line < 4; line++)
  {
    for (column = 1; column < 5; column++)
    {
      if (grid[line][column] == grid[line + 1][column + 1] && grid[line][column] == grid[line + 2][column + 2] && grid[line][column] == grid[line + 3][column + 3] && grid[line][column] != '.')
      {
        victory = 1;
      }
    }
  }
  //"For" above analyze the diagonal down-right.

  for (line = 0; line < 4; line++)
  {
    for (column = 1; column < 8; column++)
    {
      if (grid[line][column] == grid[line + 1][column] && grid[line][column] == grid[line + 2][column] && grid[line][column] == grid[line + 3][column] && grid[line][column] != '.')
      {
        victory = 1;
      }
    }
  }
  //"For" above analyze the vertical.

  for (line = 0; line < 4; line++)
  {
    for (column = 3; column < 8; column++)
    {
      if (grid[line][column] == grid[line + 1][column - 1] && grid[line][column] == grid[line + 2][column - 2] && grid[line][column] == grid[line + 3][column - 3] && grid[line][column] != '.')
      {
        victory = 1;
      }
    }
  }
  //"For" above analyze the down-left.

  if (victory == 1)
  {
    if (player == 0)
    {
      printf("Well done Player 1 (\e[1;34mX\e[0m), you've won! ");
    }
    else
    {
      printf("Well done Player 2 (\e[1;31mO\e[0m), you've won! ");
    }
  }
  //"If" above congratulate the winner.
}

void test_draw()     //Function for the test of a full grid, which means a draw.
{
  int draw = 1;
  for (line = 0; line < 6; line++)
  {
    for (column = 0 ; column < 9; column++)
    {
      if (grid[line][column] == '.')
      {
        draw = 0;
      }
    }
  }
  if (draw == 1)
  {
    printf("Both of you are bad, there isn't any winner.\n");
    victory = 1;
  }
}

void placed_token(int player, int token)     //Function that ask where to place the token and place it in the grid.
{
  int place;     //Variable that remember the chosen column by the player.
  int can_be_placed = 0;     //Variable that remember if the token can be placed.
  while (can_be_placed == 0)
  {
    if (player == 0)
    {
      printf("Player 1, in which column would you place your token(\e[1;34mX\e[0m)?\n");
    }
    else
    {
      printf("Player 2, in which column would you place your token(\e[1;31mO\e[0m)?\n");
    }
    setbuf (stdin, NULL);
    scanf("%d", &place);
    for (line = 0; line < 6; line++)
    {
      if (place == -1)
      {
        victory = 1;
        can_be_placed = 1;
        if (player == 1)
        {
          printf("Well done Player 1 (\e[1;34mX\e[0m), you've won! ");
        }
        else
        {
          printf("Well done Player 2 (\e[1;31mO\e[0m), you've won! ");
        }
        break;
      }
      //"If" above analyze if the layer is surrendering or not.
      else if (place < 1 || place > 7)
      {
        printf("Invalid column...");
        break;
      }
      else if (grid[line][place] == '.' && grid[line + 1][place] == '.')
      {
        continue;
      }
      //"If" above analyze if the token is the lowest possible.

      else if (grid[line][place] == '.' && grid[line + 1][place] != '.')
      {
        grid[line][place] = token;
        can_be_placed = 1;
        break;
      }
      else
      {
        printf("Column full.");
        break;
      }
    }
  }
}

void another_game()     //Function that ask for another game.
{
  char answer;     //Variable that remember the decision of the player to whether replay a game or not.
  int decision = 0;     //Variable that remember if the player has make a decision.
  while (decision == 0)
  {
    printf("Wanna play another game? (\e[1;32my\e[0m/\e[1;31mn\e[0m)\n");
    setbuf (stdin, NULL);
    scanf ("%c", &answer);
    if (answer == 'n')
    {
      play_again = 0;
      decision = 1;
      printf("Good bye!\n");
    }
    else if (answer == 'y')
    {
      play_again = 1;
      decision = 1;
    }
    else
    {
      printf("I don't understand, can you repeat please? ");
    }
  }
}

void main()
{
  char token;     //Variable that remember which token is actually played.
  play_again = 1;
  while (play_again == 1)
  {
    int draw = 0;     //Variable that remember if the grid is full or not.
    victory = 0;
    int player = 0;     //Variable that remember which player is playing.
    printf("Player 1 play with \e[1;34mX\e[0m and player 2 play with \e[1;31mO\e[0m.\n\nWrite (-1) to forfeit.\n");
    basic_grid();
    while (victory == 0)
    {
      if (player == 0)
      {
        token = 'X';
      }
      else
      {
        token = 'O';
      }
      //"If" above switch the token.

      placed_token(player, token);
      if (victory == 0)
      {
        game_grid();
        test_victory(player);
        if (victory == 0)
        {
          test_draw();
        }
      }
      if (player == 0)
      {
        player = 1;
      }
      else
      {
        player = 0;
      }
      //"If" above switch the player.

    }
    another_game();
  }
}
