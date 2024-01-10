#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "bmplib.h" 
#include "queue.h"
using namespace std;

void usage() { 
    cerr << "usage: ./label <options>" << endl;
    cerr <<"Examples" << endl;
    cerr << "./label test_queue" << endl;
    cerr << "./label gray <input file> <outputfile>" << endl;
    cerr << "./label binary <inputfile> <outputfile>" << endl;
    cerr << "./label segment <inputfile> <outputfile>" << endl;
}

//==============================
//Function prototypes go here
void test_queue();
void clean(unsigned char ***input,unsigned char **gray,unsigned char **binary, int **labeled_image,int height , int width);
void rgb2gray(unsigned char*** input,unsigned char** gray,int height,int width);
void gray2binary(unsigned char** gray,unsigned char** binary,int height,int width);
int component_labeling(unsigned char** binary,int** labeled_image, int height, int width); 
void label2RGB(int** labeled_image,unsigned char*** input ,int segments,int height,int width);

// The main function, you do not need to make any changes to this function 
// However, we encourage you to try to understand what's going on in the main function
int main(int argc,char **argv) {

    srand(time(0));
    if(argc < 2 )  {
        usage();
        return -1;
    }        
    unsigned char ***input=0;
    unsigned char **gray=0;
    unsigned char **binary=0;
    int **labeled_image=0;
    if( strcmp("test_queue",argv[1]) == 0 ) { 
        test_queue();
    } 
    else if(strcmp("gray",argv[1]) == 0 ) {
        if(argc <4 ) {
            cerr << "not enough argument for gray" << endl;
            return -1;
        }
        int height, width;
        input = readRGBBMP(argv[2],&height,&width);
        if(input == 0)
        {
            cerr << "unable to open " << argv[2] << " for input." << endl;
            return -1;
        }
        //dynamically allocated a 2D gray image array            
        gray = new unsigned char*[height];
        for(int i=0;i<height;i++){
          gray[i] = new unsigned char[width];
        }
        //call rgb2gray to get the gray image from rgb
        rgb2gray(input,gray,height,width);
        if(writeGSBMP(argv[3],gray,height,width) != 0) { 
            cerr << "error writing file " << argv[3] << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }
        //call the function that handles memory deallocation
        clean(input,gray,binary,labeled_image,height,width);
    }
    else if(strcmp("binary",argv[1]) == 0 ) {
        if(argc <4 ) {
            cerr << "not enough arguemnt for binary" << endl;
            return -1;
        }          
        int height,width;
        input = readRGBBMP(argv[2],&height,&width);
        if(input == 0)
        {
            cerr << "unable to open " << argv[2] << " for input." << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }        
        //dynamically allocated a 2D gray image array
        //dynamically allocated a 2D binary image array    
        gray = new unsigned char*[height];
        binary = new unsigned char*[height];
        for(int i=0;i<height;i++){
          gray[i] = new unsigned char[width];
          binary[i] = new unsigned char[width];
        }
        //call rgb2gray to get the gray image from rgb
        rgb2gray(input,gray,height,width);
        //call gray2binary to get the binary image from gray
        gray2binary(gray,binary,height,width);
        if(writeBinary(argv[3],binary,height,width) != 0) { 
            cerr << "error writing file " << argv[3] << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }
        //call the function that handles memory deallocation
        clean(input,gray,binary,labeled_image,height,width);
     
    }
    else if(strcmp("segment",argv[1]) == 0 ) {
        if(argc <4 ) {
            cerr << "not enough arguemnt for segment" << endl;
            return -1;
        } 
        int height,width;
        input = readRGBBMP(argv[2],&height,&width);
        if(input == 0)
        {
            cerr << "unable to open " << argv[2] << " for input." << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }        
        //dynamically allocated a 2D gray image array
        //dynamically allocated a 2D binary image array  
        gray = new unsigned char*[height];
        binary = new unsigned char*[height];
        for(int i=0;i<height;i++){
          gray[i] = new unsigned char[width];
          binary[i] = new unsigned char[width];
        }
        rgb2gray(input,gray,height,width);
        gray2binary(gray,binary,height,width);
        //dynamically allocated a 2D array for labels.
        labeled_image = new int*[height];
        for(int i=0;i<height;i++){
          labeled_image[i] = new int[width];
          for(int j=0;j<width;j++){
            labeled_image[i][j] = 0;
          }
        }
        int segments = component_labeling(binary, labeled_image, height, width); 
        cout<< "Segments found: " << segments << endl;
        //replace 3D input image with 0 to be used as output.
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                for(int k=0;k<RGB;k++){
                  input[i][j][k] = 0;
                } 
            }
        }
        //label2rgb
        label2RGB(labeled_image, input, segments, height, width);
      if(writeRGBBMP(argv[3],input,height,width) != 0) {
            cerr << "error writing file " << argv[3] << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }
        //call the function that handles memory deallocation
        clean(input,gray,binary,labeled_image,height,width);
    }
   return 0;
}


//==============================
//Loop over the 'in' image array and calculate the single 'out' pixel value using the formula
// GS = 0.2989 * R + 0.5870 * G + 0.1140 * B 
void rgb2gray(unsigned char ***in,unsigned char **out,int height,int width) {
  int r, g, b;
  int sum;
  for (int i = 0; i < height; i++){
    for (int j = 0; j < width; j++){
      r = in[i][j][0];
      g = in[i][j][1];
      b = in[i][j][2];
      sum = (0.2989 * r) + (0.5870 * g) + (0.1140 * b);
      out[i][j] = sum;
    }
  }
}
//==============================
//Loop over the 'in' gray scale array and create a binary (0,1) valued image 'out'
//Set the 'out' pixel to 1 if 'in' is above the THRESHOLD (already defined), else 0
void gray2binary(unsigned char **in,unsigned char **out,int height,int width) {
  for (int i = 0; i < height; i++){
      for (int j = 0; j < width; j++){
        if (in[i][j] > THRESHOLD){
          out[i][j] = 1;
        } else {
          out[i][j] = 0;
        }
      }
    }
}
//==============================
//This is the function that does the work of looping over the binary image and doing the connected component labeling
//See the guide for more detail.
//- Should return number of segments or components found
//- Two disjoint components should not share the same label.
int component_labeling(unsigned char **binary_image,int **label,int height,int width) {
   int numComp = 0;
   int queueLen;
   Location loc;
   Location neighborEast;
   Location neighborWest;
   Location neighborSouth;
   Location neighborNorth;
   int finish = 0;

   queueLen = height * width;
   Queue q(queueLen);

   int** explored = new int*[height];
   for (int i = 0; i < height; i++){
      explored[i] = new int[width + 1];
   }
   for (int i = 0; i < height; i++){
       for (int j = 0; j < width + 1; j++){
           explored[i][j] = 0;
       }
   }

   while (finish != 1){
    finish = 1;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
           if ((binary_image[i][j] == 1) && (explored[i][j] == 0)){
               loc.row = i;
               loc.col = j;
               finish = 0;
               break;
           }
       }
       if (finish == 0){
         break;
       }
    }
    if (finish == 1){
       break;
    }

    numComp++;
    q.push(loc);

    while(!(q.is_empty())){
      loc = q.pop();
      explored[loc.row][loc.col] = 1;
      label[loc.row][loc.col] = numComp;

      neighborEast = loc;
      neighborEast.row += 1; 
      if ((neighborEast.row < height) && (binary_image[neighborEast.row][neighborEast.col] == 1) && (explored[neighborEast.row][neighborEast.col] == 0)){
         explored[neighborEast.row][neighborEast.col] = 1;
         label[neighborEast.row][neighborEast.col] = numComp;
         q.push(neighborEast);
      }

      neighborWest = loc;
      neighborWest.row -= 1;
      if ((neighborWest.row >= 0) && (binary_image[neighborWest.row][neighborWest.col] == 1) && (explored[neighborWest.row][neighborWest.col] == 0)){
         explored[neighborWest.row][neighborWest.col] = 1;
         label[neighborWest.row][neighborWest.col] = numComp;
         q.push(neighborWest);
      }
      
      neighborSouth = loc;
      neighborSouth.col -= 1;
      if ((neighborSouth.col >= 0) && (binary_image[neighborSouth.row][neighborSouth.col] == 1) && (explored[neighborSouth.row][neighborSouth.col] == 0)){
         explored[neighborSouth.row][neighborSouth.col] = 1;
         label[neighborSouth.row][neighborSouth.col] = numComp;
         q.push(neighborSouth);
      }

      neighborNorth = loc;
      neighborNorth.col += 1;
      if ((neighborNorth.col < width) && (binary_image[neighborNorth.row][neighborNorth.col] == 1) && (explored[neighborNorth.row][neighborNorth.col] == 0)){
         explored[neighborNorth.row][neighborNorth.col] = 1;
         label[neighborNorth.row][neighborNorth.col] = numComp;
         q.push(neighborNorth);
       }
    }
    q.end(queueLen);
   }

   for (int i = 0; i < height; i++){
      delete[] explored[i];
   }
   delete[] explored;

  return numComp;
}   


//==============================
//Randomly assign a color (RGB) to each segment or component
//No two segments should share the same color.
void label2RGB(int  **labeled_image, unsigned char ***rgb_image,int num_segments,int height,int width) {
  int x = 0;
  int y = 0;
  int z = 0;
  for (int i = 0; i < num_segments; i++){
    x = rand() % 256;
    y = rand() % 256;
    z = rand() % 256;
    for (int j = 0; j < height; j++){
      for (int k = 0; k < width; k++){
        if (labeled_image[j][k] == i + 1){
          rgb_image[j][k][0] = x;
          rgb_image[j][k][1] = y;
          rgb_image[j][k][2] = z;
        }
      }
    }
  }
}
//========= CHECKPOINT 6 ==============
//fill out this function to delete all of the dynamic arrays created
//-- these arrays are created in the main function.
void clean(unsigned char ***input,unsigned char **gray,unsigned char **binary, int **labeled_image,int height , int width) {
    if(input) {
      for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
          delete[] input[i][j];
        }
        delete[] input[i];
      }
      delete[] input;
    }
    if(gray){
      for (int i = 0; i < height; i++){
        delete[] gray[i];
      }
      delete[] gray;
    }
    if(binary){
      for (int i = 0; i < height; i++){
        delete[] binary[i];
      }
      delete[] binary;
    }
    if(labeled_image){
      for (int i = 0; i < height; i++){
        delete[] labeled_image[i];
      }
      delete[] labeled_image;
    }
}

void test_queue() { 
    // create some locations;
    Location three_one, two_two;
    three_one.row = 3; three_one.col = 1;
    two_two.row = 2; two_two.col = 2;

    //create an Queue with max capacity 5
    Queue q(5);

    cout << boolalpha;
    cout << q.is_empty() << endl;           // true
    q.push(three_one);
    cout << q.is_empty() << endl;           // false
    q.push(two_two);

    Location loc = q.pop();
    cout << loc.row << "," << loc.col << endl; // 3 1
    loc = q.pop();
    cout << loc.row << "," << loc.col << endl; // 2 2
    cout << q.is_empty() << endl;           // true
}