// Copyright 2016 Andrew Williams
/*
    This file is part of Monitor Senior Design.

    Monitor Senior Design is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Monitor Senior Design is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Monitor Senior Design.  If not, see <http://www.gnu.org/licenses/>.
*/

// The base matrix that contains the data to be printed to the screen.
// Each entry is a color for a specific pixel
uint16_t matrixBase[32][32] = {
    { 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} , 
	{ 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000} 
};

// This contains all the data for the cursor, which the user
// will use to draw on the screen (matrix). The size of the
// cursor can be varied to have a width between 1 and 32
// and to have a height between 1 and 32.
struct MatrixCursor{
	// x coordinate of the top left cell of the cursor
	uint8_t x;
	// y coordinate of the top left cell of the cursor
	uint8_t y;
	// width of the cursor
	uint8_t width;
	// height of the cursor
	uint8_t height;
	// the color of the cursor
	uint16_t color;
	
	MatrixCursor() : x(0), y(0), width(3), height(3), color(matrix.Color444(0x0, 0x0, 0xF))
	{}
};

// The instance representing the cursor that the user will use to draw.
struct MatrixCursor matCurs;

uint16_t extractRGB(uint16_t mat[][32], uint8_t x, uint8_t y){
  return matrix.Color444((mat[x][y] >> 8)&0x0F, (mat[x][y] >> 4)&0x0F, (mat[x][y])&0x0F);
}

// Returns true if the given coordinate is within the area of the
// cursor. Used in the printToMatrix() function to determine
// whether to print the base matrix pixel or the cursor pixel.
boolean inCursor(uint8_t x, uint8_t y){
	if((matCurs.x <= x) && (x < matCurs.x+matCurs.width) &&
		(matCurs.y <= y) && (y < matCurs.y+matCurs.height)){
		return true;
	}
	else{
		return false;
	}
}
// Writes the base matrix to the screen. Takes in a boolean
// parameter to control whether the cursor is printed or not.
void printToMatrix(boolean displayCursor){
	uint8_t i, j;
	for(i=0; i<32; i++){
		for(j=0; j<32; j++){
			if((displayCursor == true) && (inCursor(j, i) == true)){
				matrix.drawPixel(j, i, matCurs.color);
			}
			else{
				matrix.drawPixel(j, i, extractRGB(matrixBase, i, j));
			}
		}
	}
}

// Writes the given row of the base matrix to the screen. Takes in a boolean
// parameter to control wheter the cursor is printed or not.
void printRowToMatrix(boolean displayCursor, uint8_t row){
	uint8_t i, j;
  for(i=0; i<32; i++){
    for(j=0; j<32; j++){
      if(j == row){
        if((displayCursor == true) && (inCursor(j, i) == true)){
          matrix.drawPixel(j, i, matCurs.color);
        }
        else{
          matrix.drawPixel(j, i, extractRGB(matrixBase, i, j));
        }
      }
      else{
        matrix.drawPixel(j, i, matrix.Color444(0, 0, 0));
      }
    }
  }
}

void printClearMatrix(){
  uint8_t i, j;
  for(i=0; i<32; i++){
    for(j=0; j<32; j++){
       matrix.drawPixel(j, i, matrix.Color444(0, 0, 0));
    }
  }
}

// Clears the entire matrix so that it's color is black
void clearMatrix(){
  for(uint8_t i=0; i<32; i++){
    for(uint8_t j=0; j<32; j++){
      matrixBase[i][j] = 0x0000;
    }
  }
}

// clears a row so that all of its pixels are black (or off)
void clearRow(uint8_t row){
  uint8_t i;
  //matrix.fillScreen(matrix.Color444(0, 0, 0));
  for(i=0; i<32; i++){
    matrix.drawPixel(row, i, matrix.Color444(0, 0, 0));
  }
}

// Takes the cursor position, size, and color, and overwrites the
// corresponding cells of the parameter matrix. Esentially, this
// is what "draws" to the base matrix. Call this when the user
// presses the button to draw.
void writeToBase(){
	uint8_t i, j;
	for(i=matCurs.x; i<matCurs.x+matCurs.width; i++){
		for(j=matCurs.y; j<matCurs.y+matCurs.height; j++){
			matrixBase[j][i] = matCurs.color;
		}
	}
}

// Converts a the ten bit input value from the knobs (potentiometers) to a 4 bit form
uint16_t colorTruncate(int color_10bit){
  if((color_10bit >= 128) && (color_10bit < 256)){
    color_10bit = 0x02;
  }
  else if((color_10bit >= 256) && (color_10bit < 384)){
    color_10bit = 0x04;
  }
  else if((color_10bit >= 384) && (color_10bit < 512)){
    color_10bit = 0x06;
  }
  else if((color_10bit >= 512) && (color_10bit < 640)){
    color_10bit = 0x08;
  }
  else if((color_10bit >= 640) && (color_10bit < 768)){
    color_10bit = 0x0A;
  }
  else if((color_10bit >= 768) && (color_10bit < 896)){
    color_10bit = 0x0C;
  }
  else if((color_10bit >= 896) && (color_10bit < 1024)){
    color_10bit = 0x0E;
  }
  else{
    color_10bit = 0x00;
  }
  return color_10bit;
}

// Reads the value read from the scanning knob (potentiometer) and returns the value
// that will be used to determine how quickly to scan.
boolean scanMode(int scanIn){
  if(digitalRead(scanIn) == LOW){
    scanIn = true;
  }
  else{
    scanIn = false;
  }
  return scanIn;
}

