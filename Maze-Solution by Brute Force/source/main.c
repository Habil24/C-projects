#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// Global Variables for use
int matrixSize,startX,startY,exitX,exitY;
char src[1500] = " ";
char Ndirection[50] = " N ";
char Sdirection[50] = " S ";
char Edirection[50] = " E ";
char Wdirection[50] = " W ";

// Function for finding the array length
int numOfLines(FILE *const mazeFile) {
  int c, count;
  count = 0;
  for (;; ) {
    c = fgetc(mazeFile);
    if (c == EOF)
      break;

    if (c == '\n')
      ++count;        // end of line => increment line counter
  }
  rewind(mazeFile);

  return count+1;
}

int capLetter(char ch){
   int result = 0;
   if(ch >= 'A' && ch <= 'Z'){
        result = 1;
   }
   return result;
}

int lowLetter(char ch){
   int result = 0;
   if(ch >= 'a' && ch <= 'z'){
        result = 1;
   }
   return result;
}

int isSafe(char Mazearray[matrixSize][matrixSize],int x,int y){
    if(x >= 0 && x < matrixSize && y >= 0 && y < matrixSize && Mazearray[x][y] != '1'){
        return 1;
    }
    return 0;


}

void MazeSolution(char Mazearray[matrixSize][matrixSize],int x,int y,char pathArray[matrixSize][matrixSize],char wasHereArray[matrixSize][matrixSize]){
    if(recursiveMaze(Mazearray,x,y,pathArray,wasHereArray) == 0){
        printf("There does not exist a possible solution!!!");
    }
    else{
        pathArray[startX][startY] = 'S';
    }
}

int recursiveMaze(char Mazearray[matrixSize][matrixSize],int x,int y,char pathArray[matrixSize][matrixSize],char wasHereArray[matrixSize][matrixSize]){
    if(x == startX && y == startY){
        pathArray[x][y] = 'S';
    }
    if(x == exitX && y == exitY){
        pathArray[x][y] = 'E';
        return 1;
    }
    // check if the coordinate is safe to go(not 1)
    if(isSafe(Mazearray,x,y) == 1 && wasHereArray[x][y] != '1'){
        wasHereArray[x][y] = '1';

        // Move North
        if(recursiveMaze(Mazearray,x-1,y,pathArray,wasHereArray) == 1){
            pathArray[x][y] = 'R';
            strcat(src,Ndirection);
            return 1;
        }
        // Move South
        if(recursiveMaze(Mazearray,x+1,y,pathArray,wasHereArray) == 1){
            pathArray[x][y] = 'R';
            strcat(src,Sdirection);
            return 1;
        }
        // Move East
        if(recursiveMaze(Mazearray,x,y+1,pathArray,wasHereArray) == 1){
            pathArray[x][y] = 'R';
            strcat(src,Edirection);
            return 1;
        }
        // Move West
        if(recursiveMaze(Mazearray,x,y-1,pathArray,wasHereArray) == 1){
            pathArray[x][y] = 'R';
            strcat(src,Wdirection);
            return 1;
        }
    }
    return 0;
}

// Main Function
int main( int argc, char **argv )
{
    // Opening the Matrix File
    FILE *mazeFile;
    mazeFile = fopen(argv[1], "r" );
    if( mazeFile == NULL )
        return 1;
    matrixSize = numOfLines( mazeFile );
    // Reading text file into 2D array
    int i,j;
    char mazeArray [matrixSize][matrixSize];

    for (i = 0; i<matrixSize; i++) {
        for (j = 0; j<matrixSize; j++) {
            fscanf(mazeFile, "%c", &mazeArray[i][j]);
        }

        char eol;
        fscanf(mazeFile, "%c", &eol);
    }
    // Variables

    //Creating path array
    char pathArray[matrixSize][matrixSize];
    for (i = 0; i < matrixSize; ++i){
       for (j = 0; j < matrixSize; ++j){
            pathArray[i][j] = '0';
        }
    }
    // CheckPoint array
    char wasHereArray[matrixSize][matrixSize];
    for (i = 0; i < matrixSize; ++i){
       for (j = 0; j < matrixSize; ++j){
            wasHereArray[i][j] = '0';
        }
    }
    // Finding start and exit indexes
    for (i = 0; i<matrixSize; i++) {
      for (j = 0; j<matrixSize; j++) {
        if(mazeArray[i][j] == 'S'){
            startX = i;
            startY = j;
        }
        if(mazeArray[i][j] == 'E'){
            exitX = i;
            exitY = j;
        }
      }
    }

    MazeSolution(mazeArray,startX,startY,pathArray,wasHereArray);
    char *data = src;
    int length=strlen(data);
    char bytes[length];
    int n=0;
    while(n<=length)
    {
       bytes[n] = data[length-n-1];
       n++;
    }

    FILE *f = fopen("path.txt", "w");
    fprintf(f, "Start %s Exit",bytes);
    fclose(mazeFile);
    fclose(f);
    return 0;
}
