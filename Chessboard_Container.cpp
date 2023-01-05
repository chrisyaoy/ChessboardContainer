#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <limits>

/**
* @author Chris Yao
* Reference List: 
https://cplusplus.com/
https://en.wikipedia.org/wiki/Chessboard
https://stackoverflow.com/questions/31816095/why-should-i-not-include-bits-stdc-h
https://stackoverflow.com/questions/8234779/how-to-remove-from-a-map-while-iterating-it

* This is a 3-D problem where the constraint is based on the square that all side lengths greater than one from outermost to inner most.

* A regular chess board has size of 8, but we can first extend the problem to the square of any even size that greater than 2. 

TODO:We can apply our algorithm to solve the square of any odd size that greater than 3, by treating the inner most square of size 1 is a base of bucket.

1. Example one:
__________________________
| 8 | 4 | 7 | 3 | 3 | 5 |
__________________________
| 4 | 2 | 6 | 8 | 4 | 7 |
__________________________
| 4 | 2 | 6 | 8 | 4 | 7 |
__________________________
| 8 | 4 | 7 | 3 | 2 | 5 |
__________________________
| 8 | 4 | 7 | 3 | 2 | 5 |
__________________________
| 8 | 4 | 7 | 3 | 3 | 5 |
__________________________
The largest square of length 6, and the min height is 3.
The square of length 4, and the min height is 2.
The inner most square of length 2, and the min hight is 3.
The Volume is 4, on cell(2, 6), cell(3,6), cell(4,5), cell(5,5). 
Note: we use cell(i,j) indicate the cell of ith row and the jth column.

Assume:
The row x and the column y of the board: x == y, and x > 0;

**/
int boardVolume(std::vector<std::vector<int>> &board){
  //For the program security, we can add an input validation function and use it here

  //Assume the input board is verified after this line
  int volumn = 0;
  int size = board.size();
  int layer = size/2;
  //when check the fence of the base, we use the base to check what's the volume that can be store.

  std::map<int, int> base;
  //Check the square from the inner most to outer most
  for(int sq = 1; sq <= layer; ++sq){
    //Each layer has the square of length, find the min val
    int minVal = std::numeric_limits<int>::max();
    int length = sq * 2;

    for(int y = (size - length)/2 ; y < (size - length)/2 + length ; ++y){
      int x = (size - length)/2;
      int dx = length - 1;
      
      std::cout << "x: " << x << " y: " << y << " " << board[x][y] << std::endl;
      std::cout << "x+dx: " << x+dx << " y: " << y << " " << board[x+dx][y] << std::endl;

      minVal = std::min(minVal, board[x][y]);
      minVal = std::min(minVal, board[x+dx][y]);
      
      base[board[x][y]] += 1;
      base[board[x+dx][y]] += 1;
    }
    
    //avoid the edge case of the square of length 2
    if(sq > 1){
      for(int x = (size - length)/2 + 1; x < (size - length)/2 + length - 1; ++x){
        int y = (size - length)/2;
        int dy = length - 1;

        std::cout << "x: " << x << " y: " << y << " " << board[x][y] << std::endl;
        std::cout << "x: " << x << " y+dy: " << y+dy << " " << board[x][y+dy] << std::endl;

        minVal = std::min(minVal, board[x][y]);
        minVal = std::min(minVal, board[x][y+dy]);
        //record the base to calculate the volumn for bigger fence
        base[board[x][y]] += 1;
        base[board[x][y+dy]] += 1;
      }
      
      //sum the volumn of the current fence and base
      for(auto it = base.cbegin(); it != base.cend();){
        if(it->first < minVal){
          //add the total number of board times the difference of minVal and current height
          volumn += it->second * (minVal-it->first);
          // std::cout << " it->first: " << it->first << " : " << " volumn : " << volumn;
          base[minVal] += it->second;
          base.erase(it++);
        }else{
          // std::cout << " it->first: " << it->first << " : " << " it->second : " << it->second;
          ++it;
        }
      }
    }
    std::cout << "minVal: " << minVal << std::endl;
    std::cout << std::endl;
  }
  return volumn;
}

void printBoard(std::vector<std::vector<int>> &board){
  //For the program security, we can add an input validation function and use it here

  //Assume the input board is verified after this line
  int length = board.size();
  std::string fence(length*3, '_');
  for(int row = 0 ; row < length; ++row){
    std::cout << fence << std::endl;
    for(int col = 0; col < length; ++col){
      std::cout << ' ' + std::to_string(board[row][col]) + "|";
    }
    std::cout << std::endl;
  }
  std::cout << fence << std::endl;
}


int main ( int argc, char* argv[] )
{
  std::vector<std::vector<int>> testCaseOne
  {
    {8,4,7,3,3,5},
    {4,2,6,8,4,7},
    {4,2,6,8,4,7},
    {8,4,7,3,2,5},
    {8,4,7,3,2,5},
    {8,4,7,3,3,5}
  };
  printBoard(testCaseOne);
  std::cout << boardVolume(testCaseOne) << std::endl;

  std::vector<std::vector<int>> testCaseTwo
  {
    {4,4,4,4,4,4,4,4},
    {4,5,5,5,5,5,5,4},
    {4,5,6,6,6,6,5,4},
    {4,5,6,3,3,6,5,4},
    {4,5,6,3,3,6,5,4},
    {4,5,6,6,6,6,5,4},
    {4,5,5,5,5,5,5,4},
    {4,4,4,4,4,4,4,4}
  };
  printBoard(testCaseTwo);
  std::cout << boardVolume(testCaseTwo) << std::endl;

  std::vector<std::vector<int>> testCaseThree
  {
    {4,4,4,4,4,4,4,4},
    {4,3,3,3,3,3,3,4},
    {4,3,6,6,6,6,3,4},
    {4,3,6,2,2,6,3,4},
    {4,3,6,2,2,6,3,4},
    {4,3,6,6,6,6,3,4},
    {4,3,3,3,3,3,3,4},
    {4,4,4,4,4,4,4,4}
  };
  printBoard(testCaseThree);
  std::cout << boardVolume(testCaseThree) << std::endl;
  {
    {7,7,7,7,7,7,7,7,7,7},
    {7,4,4,4,4,4,4,4,4,7},
    {7,4,3,3,3,3,3,3,4,7},
    {7,4,3,6,6,6,6,3,4,7},
    {7,4,3,6,2,2,6,3,4,7},
    {7,4,3,6,2,2,6,3,4,7},
    {7,4,3,6,6,6,6,3,4,7},
    {7,4,3,3,3,3,3,3,4,7},
    {7,4,4,4,4,4,4,4,4,7},
    {7,7,7,7,7,7,7,7,7,7}
  };
  printBoard(testCaseFour);
  std::cout << boardVolume(testCaseFour) << std::endl;
  return 0;
}