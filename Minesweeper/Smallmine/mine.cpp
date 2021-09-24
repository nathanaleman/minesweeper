#include<iostream>
#include<cctype>
using namespace std;

const int bombless_tiles = 20;

void set_grid(char grid[5][5]);
void set_bombs(char invis_grid[5][5], int bomb_coords[10]);
void print_grid(char grid[5][5], int num_ofBombs);

int coords(char grid[5][5], char x, int& y, char xflag, int& num_ofBombs);

void convert_num_toChar(char grid[5][5], int count, char x, int y);
int convert_char_toNum(char x);
int count_bombs_aroundTiles(char invis_grid[5][5], int count, char x, int y);
void check_ifWon(char grid[5][5], int& counter, int bombless_tiles);

int main()
{
    srand(time(NULL));
    char x, xflag;
    int y, bomb = 0, counter = 0, num_ofBombs = 5;
    char invis_grid[5][5], grid[5][5];
    int bomb_coords[10];

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

        if(x2 >= 0)
        {
            if(invis_grid[y][x2] == 'X')
              bomb++;
            else
            {
              int count = count_bombs_aroundTiles(invis_grid, 0, x, y);
              convert_num_toChar(grid, count, x, y);
            }
        }

        if(bomb == 1)
        {
            for(int i = 0; i < 10; i = i + 2)
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

void set_grid(char grid[5][5])
{
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            grid[i][j] = ' ';
        }
    }
}

void set_bombs(char invis_grid[5][5], int bomb_coords[10])
{
    int pos = 0;
    for(int i = 0; i < 5; i++)
    {
        int randX = rand() % 5;
        int randY = rand() % 5;
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

void print_grid(char grid[5][5], int num_ofBombs)
{
    cout << endl << "      A   B   C   D   E" << endl;
    cout << "    _____________________" << endl;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(i == 0 && j == 0)
                cout << "  1 | ";
            else if(i == 1 && j == 0)
                cout << "  2 | ";
            else if(i == 2 && j == 0)
                cout << "  3 | ";
            else if(i == 3 && j == 0)
                cout << "  4 | ";
            else if(i == 4 && j == 0)
                cout << "  5 | ";
            else
                cout << " ";

            cout << grid[i][j] << " |";
        }
        cout << endl;
        if(i == 0)
          cout << "    |---|---|---|---|---|          Type 'F' = Flag a bomb" << endl;
        else if(i == 1)
          cout << "    |---|---|---|---|---|          Type 'U' = Unflag a bomb" << endl;
        else if(i == 2)
          cout << "    |---|---|---|---|---|          Number of Bombs Left = " << num_ofBombs << endl;
        else
          cout << "    |---|---|---|---|---|" << endl;
    }

    cout << endl;

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
}

void convert_num_toChar(char grid[5][5], int count, char x, int y)
{
    int temp = convert_char_toNum(x);

    if(count == 0)
      grid[y][temp] = '0';
    if(count == 1)
      grid[y][temp] = '1';
    if(count == 2)
      grid[y][temp] = '2';
    if(count == 3)
      grid[y][temp] = '3';
    if(count == 4)
      grid[y][temp] = '4';
    if(count == 5)
      grid[y][temp] = '5';
    if(count == 6)
      grid[y][temp] = '6';
    if(count == 7)
      grid[y][temp] = '7';
    if(count == 8)
      grid[y][temp] = '8';

}

int count_bombs_aroundTiles(char invis_grid[5][5], int count, char x, int y)
{
    int tempX = convert_char_toNum(x);

    if(tempX-1>=0 && y-1>=0 && invis_grid[y-1][tempX-1] == 'X')
      count++;
    if(y-1>=0 && invis_grid[y-1][tempX] == 'X')
      count++;
    if(y-1>=0 && tempX+1<=4 && invis_grid[y-1][tempX+1] == 'X')
      count++;
    if(tempX+1<=4 && invis_grid[y][tempX+1] == 'X')
      count++;
    if(y+1<=4 && tempX+1<=4 && invis_grid[y+1][tempX+1] == 'X')
      count++;
    if(y+1<=4 && invis_grid[y+1][tempX] == 'X')
      count++;
    if(y+1<=4 && tempX-1>=0 && invis_grid[y+1][tempX-1] == 'X')
      count++;
    if(tempX-1>=0 && invis_grid[y][tempX-1] == 'X')
      count++;

      return count;
}

int coords(char grid[5][5], char x, int& y, char xflag, int& num_ofBombs)
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
        case 'F':
            cout << "Enter the coordinates for your flag: ";
            cin >> xflag;
            xflag = toupper(xflag);
            num_ofBombs--;
            temp = coords(grid, xflag, y, xflag, num_ofBombs);
            if(temp != -1 && grid[y-1][temp] != 'F')
              grid[y-1][temp] = 'F';
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
            if(temp != -1 && grid[y-1][temp] == 'F')
              grid[y-1][temp] = ' ';
            else
              cout << "you cant do that man" << endl;
            return -1;
            break;
        default:
            cout << "aint no option" << endl;
            return -1;
    }
}

void check_ifWon(char grid[5][5], int& counter, int bombless_tiles)
{
    int temp_count = 0;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
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
