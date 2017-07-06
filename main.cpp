#include <iostream>
#include <fstream>
using namespace std;

struct colorPicker{ //Stores rgb codes, default color is white (255.255.255)
    int r=255;
    int g=255;
    int b=255;
};
struct shape{ //Stores shape data
    int x0;
    int y0;
    int heigth;
    int width;
    colorPicker color;
};
typedef colorPicker grid[100][100]; //2D array for the grid in which new shapes are going to be drawn

int MaxValue(int currentMax, int newValue){
    if (newValue>currentMax) {
        return newValue;
    }
    else{
        return currentMax;
    }
}
void GridColoring(grid MainGrid, shape s){
    int x0=s.x0, y0=s.y0;
    for (int i=0; i<s.heigth; i++) {
        for (int j=0; j<s.width; j++) {
            MainGrid[x0][y0].r=s.color.r;
            MainGrid[x0][y0].g=s.color.g;
            MainGrid[x0][y0].b=s.color.b;
            x0++;
        }
        x0=s.x0;
        y0++;
    }
}
void DataInitialization(grid MainGrid, int &maxHeigth, int &maxWidth){
    ifstream source("U2.txt");
    int numberOfShapes;
    //Max value variable ar equal to 0 because we know that they will be replaced by bigger values once data is read
    maxHeigth=0;
    maxWidth=0;
    
    source>>numberOfShapes;
    shape ShapeArray[numberOfShapes];
    
    for (int i=0; i<numberOfShapes; i++) {
        source>>ShapeArray[i].x0>>ShapeArray[i].y0  //Getting starting coordinates
              >>ShapeArray[i].width>>ShapeArray[i].heigth  //Gettingdimensions
              >>ShapeArray[i].color.r>>ShapeArray[i].color.g>>ShapeArray[i].color.b; //Getting color code
        
        //Checking if heigth or width values from this iteration are bigger than current max values:
        maxHeigth=MaxValue(maxHeigth, ShapeArray[i].heigth);
        maxWidth=MaxValue(maxWidth, ShapeArray[i].width);
        
        GridColoring(MainGrid, ShapeArray[i]); //Initiating grid coloring
    }
    source.close();
}
void PrintResult(grid MainGrid, int maxHeigth, int maxWidth){
    ofstream output("U2_rez.txt");
    output<<maxHeigth<<"\t"<<maxWidth<<endl;
    for (int y=0; y<maxHeigth; y++) {
        for (int x=0; x<maxWidth; x++) {
            output<<MainGrid[x][y].r<<"\t"<<MainGrid[x][y].g<<"\t"<<MainGrid[x][y].b<<endl;
        }
    }
    output.close();
}

int main(){
    grid MainGrid;
    int maxHeigth, maxWidth;
    DataInitialization(MainGrid, maxHeigth, maxWidth);
    PrintResult(MainGrid, maxHeigth, maxWidth);
}
