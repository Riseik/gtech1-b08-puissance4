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
        printf("%c", grid[line][column]);
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

void test_victory(player1)
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
    if (player1 == 1)
    {
      printf("Well done Player 1 (X), you've won! ");
    }
    else
    {
      printf("Well done Player 2 (O), you've won! ");
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

void placed_token(player1, token)
{
  can_be_placed = 0;
  while (can_be_placed == 0)
  {
    if (player1 == 1)
    {
      printf("Player 1, in which column would you place your token(X)?\n");
    }
    else
    {
      printf("Player 2, in which column would you place your token(O)?\n");
    }
    fflush(stdin);
    scanf("%d", &place);
    for (line = 0; line < 6; line++)
    {
      if (place < 1 || place > 7)
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
    printf("Wanna play another game? (y/n)\n");
    fflush(stdin);
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
    int player1 = 1;
    int player2 = 0;
    printf("Player 1 play with X and player 2 play with O.\n\n");
    basic_grid();
    while (victory == 0)
    {
      if (player1 == 1)
      {
        token = 'X';
      }
      else
      {
        token = 'O';
      }
      placed_token(player1, token);
      game_grid();
      test_victory(player1);
      if (victory ==0)
      {
        test_draw();
      }
      int tmp = player1;
      player1 = player2;
      player2 = tmp;
    }
    another_game();
  }
}
