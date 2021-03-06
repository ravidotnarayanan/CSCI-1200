#include <iostream>
#include <vector>
#include <vector>
#include <algorithm>
#include <cstdlib>

#define npaths(x,y) (legal_loc(board, loc(x,y), rows, columns)? \ num_paths_recursive(board, loc(x,y), num_moves+1, rows, columns) : 0)

class loc {
  public:
    // constructor
    loc(int r, int c) { this->r = r; this->c = c; }

    int r;
    int c;
};

bool legal_loc(std::vector<std::vector<bool> > board, const loc &pos, const int rows, const int columns)
{
  return ((0 <= pos.r && pos.r <= rows-1) && (0 <= pos.c && pos.c <= columns-1) && ! board[pos.r][pos.c]);
}

int num_paths_recursive(int **board, const loc &pos, int num_moves, const int rows, const int columns)
{
  if (pos.r == rows-1 && pos.c == 0) { // base case: you're in the bottom left corner
    if (num_moves == rows*columns) {
      return 1; // visited every square
    } else {
      return 0; // didn't visit every square
    }
  } else { 
    //mark this position as being visited.
    board[pos.r][pos.c] = 1;

    int sum = 0;
    if ((0 <= pos.r-1 && pos.r-1 <= rows-1) && (0 <= pos.c && pos.c <= columns-1) && ! board[pos.r-1][pos.c])
      sum += num_paths_recursive(board, loc(pos.r-1,pos.c), num_moves+1, rows, columns);

    if ((0 <= pos.r && pos.r <= rows-1) && (0 <= pos.c+1 && pos.c+1 <= columns-1) && ! board[pos.r][pos.c+1])
      sum += num_paths_recursive(board, loc(pos.r,pos.c+1), num_moves+1, rows, columns);

    if ((0 <= pos.r+1 && pos.r+1 <= rows-1) && (0 <= pos.c && pos.c <= columns-1) && ! board[pos.r+1][pos.c])
      sum += num_paths_recursive(board, loc(pos.r+1,pos.c), num_moves+1, rows, columns);

    if ((0 <= pos.r && pos.r <= rows-1) && (0 <= pos.c-1 && pos.c-1 <= columns-1) && ! board[pos.r][pos.c-1])
      sum += num_paths_recursive(board, loc(pos.r,pos.c-1), num_moves+1, rows, columns);

    return sum;
  }
}

int num_paths(const int rows, const int columns)
{
  int **board = new int*[rows];
  for (int r = 0; r < rows; r++) {
    board[r] = new int[columns]; // populate the entire board with every position marked as not being visited
    for (int c = 0; c < columns; c++) {
      board[r][c] = 0;
    }
  }

  /* Find the number of paths to the bottom right corner starting at row 0,
   * column 0, having already moved once (to get to the first coordinate). */
  return num_paths_recursive(board, loc(0,0), 1, rows, columns);
}

int main(int argc, char **argv)
{
  if (argc != 3)
    return 1;

  int columns = atoi(argv[1]);
  int rows = atoi(argv[2]);

  std::cout << num_paths(rows,columns) << std::endl;

  return 0;
}
  
bool operator==(const loc &pos1, const loc &pos2)
{
  return pos1.r == pos2.r && pos1.c == pos2.c;
}
