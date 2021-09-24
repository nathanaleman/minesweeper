#include<iostream>
#include<cctype>
using namespace std;

const int bombless_tiles = 700;

void set_grid(char grid[20][40]);
void set_bombs(char invis_grid[20][40], int bomb_coords[200]);
void print_grid(char grid[20][40], int num_ofBombs);

int coords(char grid[20][40], char x, int& y, char xflag, int& num_ofBombs);

void convert_num_toChar(char grid[20][40], int count, char x, int y);
int convert_char_toNum(char x);
int count_bombs_aroundTiles(char invis_grid[20][40], int count, int x, int y);
void check_ifWon(char grid[20][40], int& counter, int bombless_tiles);

void print_zeroesUpLeft(char invis_grid[20][40], char grid[20][40], int x, int y);
void print_zeroesLeft(char invis_grid[20][40], char grid[20][40], int x, int y);
void print_zeroesDownLeft(char invis_grid[20][40], char grid[20][40], int x, int y);
void print_zeroesDown(char invis_grid[20][40], char grid[20][40], int x, int y);
void print_zeroesDownRight(char invis_grid[20][40], char grid[20][40], int x, int y);
void print_zeroesRight(char invis_grid[20][40], char grid[20][40], int x, int y);
void print_zeroesUpRight(char invis_grid[20][40], char grid[20][40], int x, int y);
void print_zeroesUp(char invis_grid[20][40], char grid[20][40], int x, int y);

void print_zeroes(char invis_grid[20][40], char grid[20][40], int count, int x2, int y);

int main()
{
    srand(time(NULL));
    char x, xflag;
    int y, bomb = 0, counter = 0, num_ofBombs = 100;
    char invis_grid[20][40], grid[20][40];
    int bomb_coords[200];

    set_grid(grid);
    set_grid(invis_grid);

    set_bombs(invis_grid, bomb_coords);

    print_grid(grid, num_ofBombs);


    while(bomb == 0 && counter < bombless_tiles)
    {
        cout << "Enter your move: ";
        cin >> x;
        x = toupper(x);
        int x2 = coords(grid, x, y, xflag, num_ofBombs);

        y = y-1;
   /*     for(int i = 0; i < 200; i = i + 2)
        {
            grid[bomb_coords[i]][bomb_coords[i+1]] = 'X';
        }*/

        if(x2 >= 0)
        {
            if(invis_grid[x2][y] == 'X')
              bomb++;
            else
            {
              int count = count_bombs_aroundTiles(invis_grid, 0, x2, y);
              convert_num_toChar(grid, count, x, y);

              if(count == 0)
                print_zeroes(invis_grid, grid, 0, x2, y);

            }
        }

        if(bomb == 1)
        {
            for(int i = 0; i < 200; i = i + 2)
            {
                grid[bomb_coords[i]][bomb_coords[i+1]] = 'X';
            }
        }

        print_grid(grid, num_ofBombs);

        check_ifWon(grid, counter, bombless_tiles);

    }

    if(bomb == 0)
      cout << "YOU DODGED ALL THE BOMBS!! NICE MOVING!" << endl;
    else
      cout << "YOU BLEW UP!! TRY AGAIN!!" << endl;

    return 0;
}

void set_grid(char grid[20][40])
{
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 40; j++)
        {
            grid[i][j] = ' ';
        }
    }
}

void set_bombs(char invis_grid[20][40], int bomb_coords[200])
{
    int pos = 0;
    for(int i = 0; i < 100; i++)
    {
        int randX = rand() % 20;
        int randY = rand() % 40;
        if(invis_grid[randX][randY] == ' ')
        {
            invis_grid[randX][randY] = 'X';
            bomb_coords[pos] = randX;
            bomb_coords[pos + 1] = randY;
            pos = pos + 2;
        }

        else
          i--;
    }
}

void print_grid(char grid[20][40], int num_ofBombs)
{
    cout << endl << "      1   2   3   4   5   6   7   8   9   10  11  12  13  ";
    cout << "14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  ";
    cout << "30  31  32  33  34  35  36  37  38  39  40" << endl;
    cout << "    __________________________________________________________";
    cout << "__________________________________________________________";
    cout << "_____________________________________________" << endl;
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 40; j++)
        {
            if(i == 0 && j == 0)
                cout << "  A | ";
            else if(i == 1 && j == 0)
                cout << "  B | ";
            else if(i == 2 && j == 0)
                cout << "  C | ";
            else if(i == 3 && j == 0)
                cout << "  D | ";
            else if(i == 4 && j == 0)
                cout << "  E | ";
            else if(i == 5 && j == 0)
                cout << "  G | ";
            else if(i == 6 && j == 0)
                cout << "  H | ";
            else if(i == 7 && j == 0)
                cout << "  I | ";
            else if(i == 8 && j == 0)
                cout << "  J | ";
            else if(i == 9 && j == 0)
                cout << "  K | ";
            else if(i == 10 && j == 0)
                cout << "  L | ";
            else if(i == 11 && j == 0)
                cout << "  M | ";
            else if(i == 12 && j == 0)
                cout << "  N | ";
            else if(i == 13 && j == 0)
                cout << "  O | ";
            else if(i == 14 && j == 0)
                cout << "  P | ";
            else if(i == 15 && j == 0)
                cout << "  Q | ";
            else if(i == 16 && j == 0)
                cout << "  R | ";
            else if(i == 17 && j == 0)
                cout << "  S | ";
            else if(i == 18 && j == 0)
                cout << "  T | ";
            else if(i == 19 && j == 0)
                cout << "  V | ";
            else
                cout << " ";

            cout << grid[i][j] << " |";
        }
        cout << endl;
        cout << "    |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---";
        cout << "|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---";
        cout << "|---|---|---|---|---|---|---|---|---|---|" << endl;
    }
    cout << " Type 'F' = Flag a bomb    Type 'U' = Unflag a bomb    Number of Bombs Left = " << num_ofBombs << endl;
}

int convert_char_toNum(char x)
{
    if(x == 'A')
      return 0;
    if(x == 'B')
      return 1;
    if(x == 'C')
      return 2;
    if(x == 'D')
      return 3;
    if(x == 'E')
      return 4;
    if(x == 'G')
      return 5;
    if(x == 'H')
      return 6;
    if(x == 'I')
      return 7;
    if(x == 'J')
      return 8;
    if(x == 'K')
      return 9;
    if(x == 'L')
      return 10;
    if(x == 'M')
      return 11;
    if(x == 'N')
      return 12;
    if(x == 'O')
      return 13;
    if(x == 'P')
      return 14;
    if(x == 'Q')
      return 15;
    if(x == 'R')
      return 16;
    if(x == 'S')
      return 17;
    if(x == 'T')
      return 18;
    if(x == 'V')
      return 19;
}

void convert_num_toChar(char grid[20][40], int count, char x, int y)
{
    int temp = convert_char_toNum(x);

    if(count == 0)
      grid[temp][y] = '0';
    if(count == 1)
      grid[temp][y] = '1';
    if(count == 2)
      grid[temp][y] = '2';
    if(count == 3)
      grid[temp][y] = '3';
    if(count == 4)
      grid[temp][y] = '4';
    if(count == 5)
      grid[temp][y] = '5';
    if(count == 6)
      grid[temp][y] = '6';
    if(count == 7)
      grid[temp][y] = '7';
    if(count == 8)
      grid[temp][y] = '8';

}

int count_bombs_aroundTiles(char invis_grid[20][40], int count, int x, int y)
{

    if(x-1>=0 && y-1>=0 && invis_grid[x-1][y-1] == 'X')
      count++;
    if(y-1>=0 && invis_grid[x][y-1] == 'X')
      count++;
    if(y-1>=0 && x+1<=19 && invis_grid[x+1][y-1] == 'X')
      count++;
    if(x+1<=19 && invis_grid[x+1][y] == 'X')
      count++;
    if(y+1<=39 && x+1<=19 && invis_grid[x+1][y+1] == 'X')
      count++;
    if(y+1<=39 && invis_grid[x][y+1] == 'X')
      count++;
    if(y+1<=39 && x-1>=0 && invis_grid[x-1][y+1] == 'X')
      count++;
    if(x-1>=0 && invis_grid[x-1][y] == 'X')
      count++;

      return count;
}

int coords(char grid[20][40], char x, int& y, char xflag, int& num_ofBombs)
{
    int temp;
    switch(x)
    {
        case 'A':
            cin >> y;
            return convert_char_toNum(x);
            break;
        case 'B':
            cin >> y;
            return convert_char_toNum(x);
            break;
        case 'C':
            cin >> y;
            return convert_char_toNum(x);
            break;
        case 'D':
            cin >> y;
            return convert_char_toNum(x);
            break;
        case 'E':
            cin >> y;
            return convert_char_toNum(x);
            break;
        case 'G':
            cin >> y;
            return convert_char_toNum(x);
            break;
        case 'H':
            cin >> y;
            return convert_char_toNum(x);
            break;
        case 'I':
            cin >> y;
            return convert_char_toNum(x);
            break;
        case 'J':
            cin >> y;
            return convert_char_toNum(x);
            break;
        case 'K':
            cin >> y;
            return convert_char_toNum(x);
            break;
        case 'L':
            cin >> y;
            return convert_char_toNum(x);
            break;
        case 'M':
            cin >> y;
            return convert_char_toNum(x);
            break;
        case 'N':
            cin >> y;
            return convert_char_toNum(x);
            break;
        case 'O':
            cin >> y;
            return convert_char_toNum(x);
            break;
        case 'P':
            cin >> y;
            return convert_char_toNum(x);
            break;
        case 'Q':
            cin >> y;
            return convert_char_toNum(x);
            break;
        case 'R':
            cin >> y;
            return convert_char_toNum(x);
            break;
        case 'S':
            cin >> y;
            return convert_char_toNum(x);
            break;
        case 'T':
            cin >> y;
            return convert_char_toNum(x);
            break;
        case 'V':
            cin >> y;
            return convert_char_toNum(x);
            break;
        case 'F':
            cout << "Enter the coordinates for your flag: ";
            cin >> xflag;
            xflag = toupper(xflag);
            num_ofBombs--;
            temp = coords(grid, xflag, y, xflag, num_ofBombs);
            if(temp != -1 && grid[temp][y-1] != 'F')
              grid[temp][y-1] = 'F';
            else
              cout << "you cant do that man" << endl;
            return -1;
            break;
        case 'U':
            cout << "Enter the coordinates to remove your flag: ";
            cin >> xflag;
            xflag = toupper(xflag);
            num_ofBombs++;
            temp = coords(grid, xflag, y, xflag, num_ofBombs);
            if(temp != -1 && grid[temp][y-1] == 'F')
              grid[temp][y-1] = ' ';
            else
              cout << "you cant do that man" << endl;
            return -1;
            break;
        default:
            cout << "aint no option" << endl;
            return -1;
    }
}

void check_ifWon(char grid[20][40], int& counter, int bombless_tiles)
{
    int temp_count = 0;
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 40; j++)
        {
            if(grid[i][j] != ' ' && grid[i][j] != 'F')
              temp_count++;
        }
    }

    if(temp_count >= bombless_tiles)
      counter = bombless_tiles;
    else
      temp_count = 0;
}

void print_zeroesUpLeft(char invis_grid[20][40], char grid[20][40], int x, int y)
{
      int count = count_bombs_aroundTiles(invis_grid, 0, x, y);
      if(count != 0)
        return;
      else
      {
        grid[x][y] = '0';
        if(x-1>-1 && y-1>-1)
          return print_zeroesUpLeft(invis_grid, grid, x-1, y-1);
        else
          return;
      }
}

void print_zeroesLeft(char invis_grid[20][40], char grid[20][40], int x, int y)
{
      int count = count_bombs_aroundTiles(invis_grid, 0, x, y);
      if(count != 0)
        return;
      else
      {
        grid[x][y] = '0';
        if(y-1>-1)
          return print_zeroesLeft(invis_grid, grid, x, y-1);  // left
        else
          return;
      }
}

void print_zeroesDownLeft(char invis_grid[20][40], char grid[20][40], int x, int y)
{
      int count = count_bombs_aroundTiles(invis_grid, 0, x, y);
      if(count != 0)
        return;
      else
      {
        grid[x][y] = '0';
        if(y-1>-1 && x+1<20)
          return print_zeroesDownLeft(invis_grid, grid, x+1, y-1);
        else
          return;
      }
}

void print_zeroesDown(char invis_grid[20][40], char grid[20][40], int x, int y)
{
    int count = count_bombs_aroundTiles(invis_grid, 0, x, y);

    if(count != 0)
      return;
    else
    {
      grid[x][y] = '0';
      if(x+1<20)
        return print_zeroesDown(invis_grid, grid, x+1, y);   // down
      else
        return;
    }

}
void print_zeroesDownRight(char invis_grid[20][40], char grid[20][40], int x, int y)
{
      int count = count_bombs_aroundTiles(invis_grid, 0, x, y);
      if(count != 0)
        return;
      else
      {
        grid[x][y] = '0';
        if(y+1<40 && x+1<20)
          return print_zeroesDownRight(invis_grid, grid, x+1, y+1);
        else
          return;
      }
}

void print_zeroesRight(char invis_grid[20][40], char grid[20][40], int x, int y)
{
      int count = count_bombs_aroundTiles(invis_grid, 0, x, y);
      if(count != 0)
        return;
      else
      {
        grid[x][y] = '0';
        if(y+1<40)
          return print_zeroesRight(invis_grid, grid, x, y+1);    // down
        else
          return;
      }
}

void print_zeroesUpRight(char invis_grid[20][40], char grid[20][40], int x, int y)
{
      int count = count_bombs_aroundTiles(invis_grid, 0, x, y);
      if(count != 0)
        return;
      else
      {
        grid[x][y] = '0';
        if(y+1<40 && x-1>-1)
          return print_zeroesUpRight(invis_grid, grid, x-1, y+1);
        else
          return;
      }
}

void print_zeroesUp(char invis_grid[20][40], char grid[20][40], int x, int y)
{
      int count = count_bombs_aroundTiles(invis_grid, 0, x, y);
      if(count != 0)
        return;
      else
      {
        grid[x][y] = '0';
        if(x-1>-1)
          return print_zeroesUp(invis_grid, grid, x-1, y);
        else
          return;
      }
}

void print_zeroes(char invis_grid[20][40], char grid[20][40], int count, int x2, int y)
{
      if(count_bombs_aroundTiles(invis_grid, count, x2, y) == 0)
      {
        print_zeroesUpLeft(invis_grid, grid, x2, y);
        print_zeroesLeft(invis_grid, grid, x2, y);
        print_zeroesDownLeft(invis_grid, grid, x2, y);
        print_zeroesDown(invis_grid, grid, x2, y);
        print_zeroesDownRight(invis_grid, grid, x2, y);
        print_zeroesRight(invis_grid, grid, x2, y);
        print_zeroesUpRight(invis_grid, grid, x2, y);
        print_zeroesUp(invis_grid, grid, x2, y);
      }
      if(count_bombs_aroundTiles(invis_grid, count, x2-1, y-1) == 0)
      {
        print_zeroesUpLeft(invis_grid, grid, x2-1, y-1);
        print_zeroesLeft(invis_grid, grid, x2-1, y-1);
        print_zeroesDownLeft(invis_grid, grid, x2-1, y-1);
        print_zeroesDown(invis_grid, grid, x2-1, y-1);
        print_zeroesDownRight(invis_grid, grid, x2-1, y-1);
        print_zeroesRight(invis_grid, grid, x2-1, y-1);
        print_zeroesUpRight(invis_grid, grid, x2-1, y-1);
        print_zeroesUp(invis_grid, grid, x2-1, y-1);
      }
      if(count_bombs_aroundTiles(invis_grid, count, x2, y-1) == 0)
      {
        print_zeroesUpLeft(invis_grid, grid, x2, y-1);
        print_zeroesLeft(invis_grid, grid, x2, y-1);
        print_zeroesDownLeft(invis_grid, grid, x2, y-1);
        print_zeroesDown(invis_grid, grid, x2, y-1);
        print_zeroesDownRight(invis_grid, grid, x2, y-1);
        print_zeroesRight(invis_grid, grid, x2, y-1);
        print_zeroesUpRight(invis_grid, grid, x2, y-1);
        print_zeroesUp(invis_grid, grid, x2, y-1);
      }
      if(count_bombs_aroundTiles(invis_grid, count, x2+1, y-1) == 0)
      {
        print_zeroesUpLeft(invis_grid, grid, x2+1, y-1);
        print_zeroesLeft(invis_grid, grid, x2+1, y-1);
        print_zeroesDownLeft(invis_grid, grid, x2+1, y-1);
        print_zeroesDown(invis_grid, grid, x2+1, y-1);
        print_zeroesDownRight(invis_grid, grid, x2+1, y-1);
        print_zeroesRight(invis_grid, grid, x2+1, y-1);
        print_zeroesUpRight(invis_grid, grid, x2+1, y-1);
        print_zeroesUp(invis_grid, grid, x2+1, y-1);
      }
      if(count_bombs_aroundTiles(invis_grid, count, x2+1, y) == 0)
      {
        print_zeroesUpLeft(invis_grid, grid, x2+1, y);
        print_zeroesLeft(invis_grid, grid, x2+1, y);
        print_zeroesDownLeft(invis_grid, grid, x2+1, y);
        print_zeroesDown(invis_grid, grid, x2+1, y);
        print_zeroesDownRight(invis_grid, grid, x2+1, y);
        print_zeroesRight(invis_grid, grid, x2+1, y);
        print_zeroesUpRight(invis_grid, grid, x2+1, y);
        print_zeroesUp(invis_grid, grid, x2+1, y);
      }
      if(count_bombs_aroundTiles(invis_grid, count, x2+1, y+1) == 0)
      {
        print_zeroesUpLeft(invis_grid, grid, x2+1, y+1);
        print_zeroesLeft(invis_grid, grid, x2+1, y+1);
        print_zeroesDownLeft(invis_grid, grid, x2+1, y+1);
        print_zeroesDown(invis_grid, grid, x2+1, y+1);
        print_zeroesDownRight(invis_grid, grid, x2+1, y+1);
        print_zeroesRight(invis_grid, grid, x2+1, y+1);
        print_zeroesUpRight(invis_grid, grid, x2+1, y+1);
        print_zeroesUp(invis_grid, grid, x2+1, y+1);
      }
      if(count_bombs_aroundTiles(invis_grid, count, x2, y+1) == 0)
      {
        print_zeroesUpLeft(invis_grid, grid, x2, y+1);
        print_zeroesLeft(invis_grid, grid, x2, y+1);
        print_zeroesDownLeft(invis_grid, grid, x2, y+1);
        print_zeroesDown(invis_grid, grid, x2, y+1);
        print_zeroesDownRight(invis_grid, grid, x2, y+1);
        print_zeroesRight(invis_grid, grid, x2, y+1);
        print_zeroesUpRight(invis_grid, grid, x2, y+1);
        print_zeroesUp(invis_grid, grid, x2, y+1);
      }
      if(count_bombs_aroundTiles(invis_grid, count, x2-1, y+1) == 0)
      {
        print_zeroesUpLeft(invis_grid, grid, x2-1, y+1);
        print_zeroesLeft(invis_grid, grid, x2-1, y+1);
        print_zeroesDownLeft(invis_grid, grid, x2-1, y+1);
        print_zeroesDown(invis_grid, grid, x2-1, y+1);
        print_zeroesDownRight(invis_grid, grid, x2-1, y+1);
        print_zeroesRight(invis_grid, grid, x2-1, y+1);
        print_zeroesUpRight(invis_grid, grid, x2-1, y+1);
        print_zeroesUp(invis_grid, grid, x2-1, y+1);
      }
      if(count_bombs_aroundTiles(invis_grid, count, x2-1, y) == 0)
      {
        print_zeroesUpLeft(invis_grid, grid, x2-1, y);
        print_zeroesLeft(invis_grid, grid, x2-1, y);
        print_zeroesDownLeft(invis_grid, grid, x2-1, y);
        print_zeroesDown(invis_grid, grid, x2-1, y);
        print_zeroesDownRight(invis_grid, grid, x2-1, y);
        print_zeroesRight(invis_grid, grid, x2-1, y);
        print_zeroesUpRight(invis_grid, grid, x2-1, y);
        print_zeroesUp(invis_grid, grid, x2-1, y);
      }
}
