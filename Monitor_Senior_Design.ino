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

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library


#define CLK 11
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);
#include "TaskScheduler.h" // Library by Anatoli Arkhipenko
#include "matrixHelpers.h"
#include "SerialUSB.h"


// The "write" button. Pressing this writes the cursor to the screen permanently
int writeButton = 42;
// The cursor size buttons. These change the size of the cursor, both height and
// width.
int decHeight = 45;
int incHeight = 46;
int decWidth = 44;
int incWidth = 43;
// input pin for button that initiates transfer of the image to flash drive
int transferPin = 47;
// input pin for button switching to scanning mode
int scanPin = 48;
// input pins from the potentiometers (dials) controlling the RGB color values.
int in_red = A4;
int in_green = A5;
int in_blue = A6;
// input pins for the joystick (which is used to move the cursor around the screen).
int in_up_down = A7;
int in_left_right = A8;

// variables to save the input values from the RGB knobs (potentiometers)
int sense_red = 0;
int sense_blue = 0;
int sense_green = 0;
// variables to save the input values from the joystick
int sense_up_down = 0;
int sense_left_right = 0;
// variable to save the value from the scanning knob (potentiometer)
int sense_scan = 0;

// This is set to true when the system goes into "transfer" mode.
// (when the system is sending the drawn image to the flash drive.)
boolean usbRunning = false;
// boolean variable to determine whether or not to show scanning
boolean scanYN = false;
// variable to store which row to print to the screen when slowing down scan
uint8_t rowNum = 0;
// variable to control how long each row is displayed when showing the scan
uint8_t rowCount = 0;
// Two boolean variables to flip true/false every half second to make the cursor "flash".
// Only flashes if the cursor is not being moved.
boolean flash = true; // Determines the half-second intervals to display the cursor
boolean isMoving = false; // indicates whether the cursor is moving
                          // (will always display if moving)
// The display state machine. This simply writes the current contents of the matrix 
// (and the cursor every half second) to the LED matrix display
enum DISP_States {DISP_Init, DISP_Display, DISP_Pause};
int DISP_State = DISP_Init;
void DISP_SM(){
  switch(DISP_State){
    case DISP_Init:
      DISP_State = DISP_Display;
      break;
    case DISP_Display:
      if(usbRunning == true){
        DISP_State = DISP_Pause;
        printClearMatrix(); // turn all pixels to black
      }
      else{
        DISP_State = DISP_Display;
      }
      break;
    case DISP_Pause:
      if(usbRunning == true){
        DISP_State = DISP_Pause;
      }
      else{
        DISP_State = DISP_Display;
        // Make sure to reset the matrix after the drawing has been copied to the
        // flash drive.
        clearMatrix();
        printToMatrix(false);
      }
      break;
    default:
      DISP_State = DISP_Init;
      break;
  }
  switch(DISP_State){
    case DISP_Init:
      break;
    case DISP_Display:
      scanYN = scanMode(scanPin);
      if(scanYN == false){
        if(isMoving || flash){
          printToMatrix(true);
        }
        else{
          printToMatrix(false);
        }
      }
      else{
        if(isMoving || flash){
          printRowToMatrix(true, rowNum);
        }
        else{
          printRowToMatrix(false, rowNum);
        }
      }
      rowCount += 1;
      if(rowCount >= 2){
        if(rowNum < 31){
          rowNum += 1;
        }
        else{
          rowNum = 0;
        }
        rowCount = 0;
      }
      break;
    case DISP_Pause:
      matCurs.x = 0;
      matCurs.y = 0;
      matCurs.width = 3;
      matCurs.height = 3;
      break;
    default:
      break;
  }
}
// State machine to change the size of the cursor. Detects one of 4 different button
// presses to either grow or shrink the width, or grow and shrink the height.
enum CURS_States {CURS_Init, CURS_Wait, CURS_IncWidth, CURS_DecWidth, CURS_IncHeight, CURS_DecHeight, CURS_Pause};
int CURS_State = CURS_Init;
void CURS_SM(){
  switch(CURS_State){
    case CURS_Init:
      CURS_State = CURS_Wait;
      break;
    case CURS_Wait:
      if(usbRunning == true){
        CURS_State = CURS_Pause;
      }
      else if(digitalRead(incWidth) == LOW){
        CURS_State = CURS_IncWidth;
        if(matCurs.width < 32){
          matCurs.width += 1;
        }
      }
      else if(digitalRead(decWidth) == LOW){
        CURS_State = CURS_DecWidth;
        if(matCurs.width > 1){
          matCurs.width -= 1;
        }
      }
      else if(digitalRead(incHeight) == LOW){
        CURS_State = CURS_IncHeight;
        if(matCurs.height < 32){
          matCurs.height += 1;
        }
      }
      else if(digitalRead(decHeight) == LOW){
        CURS_State = CURS_DecHeight;
        if(matCurs.height > 1){
          matCurs.height -= 1;
        }
      }
      else{
        CURS_State = CURS_Wait;
      }
      break;
    case CURS_IncWidth:
      if(usbRunning == true){
        CURS_State = CURS_Pause;
      }
      else if(digitalRead(incWidth) == LOW){
        CURS_State = CURS_IncWidth;
      }
      else{
        CURS_State = CURS_Wait;
      }
      break;
    case CURS_DecWidth:
      if(usbRunning == true){
        CURS_State = CURS_Pause;
      }
      else if(digitalRead(decWidth) == LOW){
        CURS_State = CURS_DecWidth;
      }
      else{
        CURS_State = CURS_Wait;
      }
      break;
    case CURS_IncHeight:
      if(usbRunning == true){
        CURS_State = CURS_Pause;
      }
      else if(digitalRead(incHeight) == LOW){
        CURS_State = CURS_IncHeight;
      }
      else{
        CURS_State = CURS_Wait;
      }
      break;
    case CURS_DecHeight:
      if(usbRunning == true){
        CURS_State = CURS_Pause;
      }
      else if(digitalRead(decHeight) == LOW){
        CURS_State = CURS_DecHeight;
      }
      else{
        CURS_State = CURS_Wait;
      }
      break;
    case CURS_Pause:
      if(usbRunning == true){
        CURS_State = CURS_Pause;
      }
      else{
        CURS_State = CURS_Wait; 
      }
      break;
    default:
      CURS_State = CURS_Init;
      break;
  }
  switch(CURS_State){
    case CURS_Init:
      break;
    case CURS_Wait:
      break;
    case CURS_IncWidth:
      break;
    case CURS_DecWidth:
      break;
    case CURS_IncHeight:
      break;
    case CURS_DecHeight:
      break;
    case CURS_Pause:
      break;
    default:
      break;
  }
}
// The "update" state machine. This just updates the internal variables for RGB values
// and joystick values. In essence, it reads from the input of the knobs/joystick.
enum UPD_States {UPD_Init, UPD_Wait};
int UPD_State = UPD_Init;
void UPD_SM(){
  switch(UPD_State){
    case UPD_Init:
      UPD_State = UPD_Wait;
      break;
    case UPD_Wait:
      UPD_State = UPD_Wait;
      break;
    default:
      UPD_State = UPD_Init;
      break;
  }
  switch(UPD_State){
    case UPD_Init:
      break;
    case UPD_Wait:
      sense_red = analogRead(in_red);
      sense_green = analogRead(in_green);
      sense_blue = analogRead(in_blue);
      matCurs.color = matrix.Color444(colorTruncate(sense_red), colorTruncate(sense_green), colorTruncate(sense_blue));
      sense_up_down = analogRead(in_up_down);
      sense_left_right = analogRead(in_left_right);
      break;
    default:
      UPD_State = UPD_Init;
      break;
  }
}
// The movement state machine
enum MOVE_States {MOVE_Init, MOVE_Wait, MOVE_Move, MOVE_Pause};
int MOVE_State = MOVE_Init;
void MOVE_SM(){
  switch(MOVE_State){
    case MOVE_Init:
      MOVE_State = MOVE_Wait;
      isMoving = false;
      break;
    case MOVE_Wait:
      if(usbRunning == true){
        MOVE_State = MOVE_Pause;
      }
      else if(sense_up_down < 400 || sense_up_down > 600 || sense_left_right < 400 ||
      sense_left_right > 600){
        MOVE_State = MOVE_Move;
        isMoving = true;
      }
      else{
        MOVE_State = MOVE_Wait;
      }
      break;
    case MOVE_Move:
      if(usbRunning == true){
        MOVE_State = MOVE_Pause;
      }
      else if(sense_up_down < 400 || sense_up_down > 600 || sense_left_right < 400 ||
      sense_left_right > 600){
        MOVE_State = MOVE_Move;
      }
      else{
        MOVE_State = MOVE_Wait;
        isMoving = false;
      }
      break;
    case MOVE_Pause:
      if(usbRunning == true){
        MOVE_State = MOVE_Pause;
      }
      else{
        MOVE_State = MOVE_Wait;
      }
      break;
    default:
      MOVE_State = MOVE_Init;
      break;
  }
  switch(MOVE_State){
    case MOVE_Init:
      break;
    case MOVE_Wait:
      break;
    case MOVE_Move:
      if((sense_up_down < 400) && (matCurs.y+matCurs.height < 32)){
        matCurs.y += 1;
      }
      else if((sense_up_down > 620) && (matCurs.y > 0)){
        matCurs.y -= 1;
      }
      if((sense_left_right < 400) && (matCurs.x > 0)){
        matCurs.x -= 1;
      }
      else if((sense_left_right > 600) && (matCurs.x+matCurs.width < 32)){
        matCurs.x += 1;
      }
      break;
    default:
      break;
  }
}
// The write state machine. Whenever the write button is pressed, the base matrix is
// written to.
enum WRITE_States {WRITE_Init, WRITE_Wait, WRITE_Write, WRITE_Pause};
int WRITE_State = WRITE_Init;
void WRITE_SM(){
  switch(WRITE_State){
    case WRITE_Init:
      WRITE_State = WRITE_Wait;
      break;
    case WRITE_Wait:
      if(usbRunning == true){
        WRITE_State = WRITE_Pause;
      }
      else if(digitalRead(writeButton) == LOW){
        WRITE_State = WRITE_Write;
      }
      else{
        WRITE_State = WRITE_Wait;
      }
      break;
    case WRITE_Write:
      if(usbRunning == true){
        WRITE_State = WRITE_Pause;
      }
      else if(digitalRead(writeButton) == LOW){
        WRITE_State = WRITE_Write;
      }
      else{
        WRITE_State = WRITE_Wait;
      }
      break;
    case WRITE_Pause:
      if(usbRunning == true){
        WRITE_State = WRITE_Pause;
      }
      else{
        WRITE_State = WRITE_Wait;
      }
      break;
    default:
      WRITE_State = WRITE_Init;
      break;
  }
  switch(WRITE_State){
    case WRITE_Init:
      break;
    case WRITE_Wait:
      break;
    case WRITE_Write:
      writeToBase();
      break;
    default:
      break;
  }
}

enum FLASH_States {FLASH_Init, FLASH_Flash};
int FLASH_State = FLASH_Init;
void FLASH_SM(){
  switch(FLASH_State){
    case FLASH_Init:
      FLASH_State = FLASH_Flash;
      break;
    case FLASH_Flash:
      FLASH_State = FLASH_Flash;
      break;
  }
  switch(FLASH_State){
    case FLASH_Init:
      break;
    case FLASH_Flash:
      flash = !flash;
      break;
  }
}

// This SM controls whether the system goes into "transfer" mode,
// which disables drawing and initiates transfer of the drawn image
// to the flash drive.
enum USB_States {USB_Init, USB_Wait, USB_Transfer};
int USB_State = USB_Init;
void USB_SM(){
  switch(USB_State){
    case USB_Init:
      USB_State = USB_Wait;
      break;
    case USB_Wait:
      if(digitalRead(transferPin) == LOW){
        USB_State = USB_Transfer;
      }
      else{
        USB_State = USB_Wait;
      }
      break;
    case USB_Transfer:
      if(usbRunning == true){
        USB_State = USB_Transfer;
      }
      else{
        USB_State = USB_Wait;
      }
      break;
    default:
      USB_State = USB_Init;
      break;
  }
  switch(USB_State){
    case USB_Init:
      break;
    case USB_Wait:
      break;
    case USB_Transfer:
      usbRunning = true; // flash lights to indicate working
      resetALL();
      set_USB();
      diskConnectionStatus();
      USBdiskMount();
      setFileName("DRAWING.BMP");
      fileOpen();
      fileCreate();
      fileWrite(matrixBase);
      fileClose(0x01);
      resetALL();
      usbRunning = false; // Stop flashing lights
      break;
    default:
      break;
  }
}


// These are the tasks being executed. They are handled by the task scheduler library
// code from "TaskScheduler.h".
Task displayTask(5, TASK_FOREVER, &DISP_SM); // The display task
Task updateTask(50, TASK_FOREVER, &UPD_SM); // the update task (updates from input)
Task cursorTask(50, TASK_FOREVER, &CURS_SM); // task for changing cursor size
Task movementTask(200, TASK_FOREVER, &MOVE_SM); // the movement task
Task writeTask(50, TASK_FOREVER, &WRITE_SM); // The write task
Task flashTask(500, TASK_FOREVER, &FLASH_SM); // the task to flash the cursor every half second
Task transferTask(50, TASK_FOREVER, &USB_SM); // Task to transfer image to flash drive

// Initialization of the task scheduler
Scheduler runner;


void setup() {
  Serial.begin(9600);
  USB.begin(9600);
  matrix.begin();
  runner.init();
  runner.addTask(displayTask);
  runner.addTask(updateTask);
  runner.addTask(cursorTask);
  runner.addTask(movementTask);
  runner.addTask(writeTask);
  runner.addTask(flashTask);
  runner.addTask(transferTask);
  pinMode(writeButton, INPUT);
  pinMode(incWidth, INPUT);
  pinMode(decWidth, INPUT);
  pinMode(incHeight, INPUT);
  pinMode(decHeight, INPUT);
  pinMode(transferPin, INPUT);
  pinMode(scanPin, INPUT);
  digitalWrite(writeButton, HIGH);
  digitalWrite(incWidth, HIGH);
  digitalWrite(decWidth, HIGH);
  digitalWrite(incHeight, HIGH);
  digitalWrite(decHeight, HIGH);
  digitalWrite(transferPin, HIGH);
  digitalWrite(scanPin, HIGH);
  printToMatrix(true);
  displayTask.enable();
  updateTask.enable();
  cursorTask.enable();
  movementTask.enable();
  writeTask.enable();
  flashTask.enable();
  transferTask.enable();
}

void loop() {
  runner.execute();
}

