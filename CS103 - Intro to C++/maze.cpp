#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
   int rows, cols;
   int result;
   char** mymaze=NULL;
   char* filename;
   if(argc < 2)
   {
       cout << "Please provide a maze input file" << endl;
       return 1;
   }
  
   filename = argv[1];
   mymaze = read_maze(filename, &rows, &cols);
   if (mymaze == NULL) {
      cout << "Error, input format incorrect." << endl;
      return 1;
   }

   result = maze_search(mymaze, rows, cols);

   if (result == 1){
     print_maze(mymaze, rows, cols);
   } else if (result == 0){
     cout << "No path could be found!" << endl;
   } else if (result == 2){
     cout << "Error, input format incorrect." << endl;
   } else {
     cout << "Invalid maze." << endl;
   }

   for(int i = 0; i < rows; i++){
     delete[] mymaze[i];
   }
   delete[] mymaze;

  return 0;
}

/*
Attempt to find path and return:
1 if successful
0 if no path exists
-1 if invalid maze (not exactly one S and one F)

If path if found fill it in the '*' characters
but don't overwrite the 'S' and 'F' cells
NOTE: don't forget to deallocate memory in here too!
*/

int maze_search(char** maze, int rows, int cols){
   int numStart = 0;
   int numFinish = 0;
   int queueLen;
   Location loc;
   Location neighborEast;
   Location neighborWest;
   Location neighborSouth;
   Location neighborNorth;
   Location finish;
   Location temp;
   int queueTally = 0;
   int exploreTally = 1;
   int success = 0;
   int exploredInt = 0;

   queueLen = rows * cols;

   for (int i = 0; i < rows; i++){
      for (int j = 0; j < cols; j++){
         if (maze[i][j] == 'S'){
            numStart++;
         }
      }
   }
   for (int i = 0; i < rows; i++){
      for (int j = 0; j < cols; j++){
         if (maze[i][j] == 'F'){
            numFinish++;
         }
      }
   }

   for (int i = 0; i < rows; i++){
      for (int j = 0; j < cols; j++){
         if ((maze[i][j] != 'F') && (maze[i][j] != 'S') && (maze[i][j] != '#') && (maze[i][j] != '.')){
            return 2;
         }
      }
   }
  
   if (!((numStart == 1) && (numFinish == 1))){
      return -1;
   }

   for (int i = 0; i < rows; i++){
      for (int j = 0; j < cols; j++){
         if (maze[i][j] == 'S'){
            loc.row = i;
            loc.col = j;
            break;
         }
      }
   }

   Queue q(queueLen);

   Location* explored = new Location[queueLen];
   for (int i = 0; i < queueLen; i++){
      explored[i].col = -1;
      explored[i].row = -1;
   }
   Location** predecessor = new Location*[rows];
   for (int i = 0; i < rows; i++){
      predecessor[i] = new Location[cols + 1];
   }

   explored[0] = loc;

   q.add_to_back(loc);

   while(!(q.is_empty())){
      loc = q.find(queueTally);
      exploredInt = 0;
      neighborEast = loc;
      neighborEast.row += 1;
      for (int i = 0; i < queueLen; i++){
        temp = explored[i];
         if ((neighborEast.row == temp.row) && (neighborEast.col == temp.col)){
            exploredInt++;
            break;
         }
      }
      if ((neighborEast.row < rows) && (maze[neighborEast.row][neighborEast.col] != '#') && (exploredInt == 0)){
         explored[exploreTally] = neighborEast;
         exploreTally++;
         q.add_to_back(neighborEast);
         predecessor[neighborEast.row][neighborEast.col] = loc;
         if (maze[neighborEast.row][neighborEast.col] == 'F'){
            success = 1;
            finish = neighborEast;
            break;
         }
      }
      exploredInt = 0;
      neighborWest = loc;
      neighborWest.row -= 1;

      for (int i = 0; i < queueLen; i++){
        temp = explored[i];
         if ((neighborWest.row == temp.row) && (neighborWest.col == temp.col)){
            exploredInt++;
            break;
         }
      }
      if ((neighborWest.row >= 0) && (maze[neighborWest.row][neighborWest.col] != '#') && (exploredInt == 0)){
         explored[exploreTally] = neighborWest;
         exploreTally++;
         q.add_to_back(neighborWest);
         predecessor[neighborWest.row][neighborWest.col] = loc;
         if (maze[neighborWest.row][neighborWest.col] == 'F'){
            success = 1;
            finish = neighborWest;
            break;
         }
      }
      exploredInt = 0;
      neighborSouth = loc;
      neighborSouth.col -= 1;
      for (int i = 0; i < queueLen; i++){
        temp = explored[i];
        if ((neighborSouth.row == temp.row) && (neighborSouth.col == temp.col)){
          exploredInt++;
          break;
        }
      }
      if ((neighborSouth.col >= 0) && (maze[neighborSouth.row][neighborSouth.col] != '#') && (exploredInt == 0)){
         explored[exploreTally] = neighborSouth;
         exploreTally++;
         q.add_to_back(neighborSouth);
         predecessor[neighborSouth.row][neighborSouth.col] = loc;
         if (maze[neighborSouth.row][neighborSouth.col] == 'F'){
            success = 1;
            finish = neighborSouth;
            break;
         }
      }
      exploredInt = 0;
      neighborNorth = loc;
      neighborNorth.col += 1;
      for (int i = 0; i < queueLen; i++){
        temp = explored[i];
        if ((neighborNorth.row == temp.row) && (neighborNorth.col == temp.col)){
          exploredInt++;
          break;
        }
      }
      if ((neighborNorth.col < cols) && (maze[neighborNorth.row][neighborNorth.col] != '#') && (exploredInt == 0)){
         explored[exploreTally] = neighborNorth;
         exploreTally++;
         q.add_to_back(neighborNorth);
         predecessor[neighborNorth.row][neighborNorth.col] = loc;
         if (maze[neighborNorth.row][neighborNorth.col] == 'F'){
            success = 1;
            finish = neighborNorth;
            break;
         }
      }
      queueTally++;
      q.remove_from_front();
   }

   if (success == 1){
      finish = predecessor[finish.row][finish.col];
      while (maze[finish.row][finish.col] != 'S'){
         maze[finish.row][finish.col] = '*';
         finish = predecessor[finish.row][finish.col];
      }
   }

   delete[] explored;
   for (int i = 0; i < rows; i++){
      delete[] predecessor[i];
   }
   delete[] predecessor;

   return success;
}