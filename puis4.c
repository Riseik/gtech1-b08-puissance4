#include <stdio.h>
#include <stdlib.h>

char grid[6][9];
int line;
int column;
int can_be_placed;
int place;
int victory;
int play_again = 1;

void basic_grid()
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

void game_grid()
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
          printf("\e[1;34m%c\e[0m", grid[line][column]);
        }
        else
        {
          printf("\e[1;31m%c\e[0m", grid[line][column]);
        }
        printf(" ");
        continue;
      }
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

void test_victory(player)
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
}

void test_draw()
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

void placed_token(player, token)
{
  can_be_placed = 0;
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
      else if (place < 1 || place > 7)
      {
        printf("Invalid column...");
        break;
      }
      else if (grid[line][place] == '.' && grid[line + 1][place] == '.')
      {
        continue;
      }
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

void another_game()
{
  char answer;
  int decision = 0;
  while (decision == 0)
  {
    printf("Wanna play another game? (\e[1;32my\e[0m/\e[1;31mn\e[0m)\n");
    setbuf (stdin, NULL);
    scanf ("%c", &answer);
    if (answer == 'n')
    {
      play_again = 0;
      decision = 1;
      printf("Good bye!");
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
  char token;
  play_again = 1;
  while (play_again == 1)
  {
    int draw = 0;
    victory = 0;
    int player = 0;
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
    }
    another_game();
  }
}
