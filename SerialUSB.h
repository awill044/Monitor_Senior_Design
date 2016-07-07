// This file, in part, contains modified code from the following link:
// http://arduinobasics.blogspot.com/2015/05/ch376s-usb-readwrite-module.html
// The header from that file is:
/* ===============================================================
      Project: CH376S USB Read/Write Module testing ground
       Author: Scott C
      Created: 1st May 2015
  Arduino IDE: 1.6.2
      Website: http://arduinobasics.blogspot.com/p/arduino-basics-projects-page.html
  Description: This project will allow you to perform many of the functions available on the CH376S module.
               Checking connection to the module, putting the module into USB mode, resetting the module, 
               reading, writing, appending text to files on the USB stick. This is very useful alternative to
               SD card modules, plus it doesn't need any libraries.
================================================================== */

//========================================//
// Andrew Williams
// awill044@ucr.edu
// 6/1/16
//=======================================//

#include <SoftwareSerial.h>

SoftwareSerial USB(30, 31); 

// Used to convert the 4-bit color data from this program into the 8-bit form that is found
// in standard bitmap images.
uint8_t colorConvert(uint16_t mat[][32], uint8_t i, uint8_t j, uint8_t color){
  uint8_t temp = 0;
  uint16_t matTemp = mat[i][j];
  // Return the intensity of blue
  if(color == 0){    
    temp = (matTemp & 0x0F);
  }
  // return intensity of green
  else if(color == 1){
    temp = ((matTemp >> 4) & 0x0F);
  }
  // return intensity of red
  else{
    temp = ((matTemp >> 8) & 0x0F);
  }
  return (temp * 17);
}

// Opens the file for writing.
void fileOpen(){
  Serial.println("Opening file.");
  USB.write(0x57);
  USB.write(0xAB);
  USB.write(0x32);
  delay(2000);
}

// Resets the mode of the CH376S chip
void resetALL(){
    USB.write(0x57);
    USB.write(0xAB);
    USB.write(0x05);
    delay(200);
}

// Sets the CH376S chip to "USB mode", which is required to write
void set_USB(){
  USB.write(0x57);
  USB.write(0xAB);
  USB.write(0x15);
  USB.write(0x06);
  delay(20);
}

// This has something to do with checking to see if the flash drive is properly
// connected. I do not use this.
void diskConnectionStatus(){
  USB.write(0x57);
  USB.write(0xAB);
  USB.write(0x30);
  delay(2000);
}

// Mounts the USB flash drive
void USBdiskMount(){
  USB.write(0x57);
  USB.write(0xAB);
  USB.write(0x31);
  delay(2000);
}

// Creates the new file that we will write to
void fileCreate(){
  USB.write(0x57);
  USB.write(0xAB);
  USB.write(0x34);
  delay(2000);
}

// Sets the name of the new file.
void setFileName(String fileName){
  USB.write(0x57);
  USB.write(0xAB);
  USB.write(0x2F);
  USB.write(0x2F);         // Every filename must have this byte to indicate the start of the file name.
  USB.print(fileName);     // "fileName" is a variable that holds the name of the file.  eg. TEST.TXT
  USB.write((byte)0x00);   // you need to cast as a byte - otherwise it will not compile.  The null byte indicates the end of the file name.
  delay(20);
}

// Performs all the necessary writing to the new file. There was a function
// provided in the tutorial listed in the header above that was supposed to
// wait for and receive acknowledgements from the CH376S chip. However,
// it didn't work, so I had to use delays instead to give the chip time
// to transmit to the flash drive.
void fileWrite(uint16_t mat[][32]){
  // NOTE: the parameter string is not used.
  // ***Length set 1***
  byte dataLength = (byte)54;
  delay(100);
  
  USB.write(0x57);
  USB.write(0xAB);
  USB.write(0x3C);
  USB.write((byte) dataLength);
  USB.write((byte) 0x00);
  delay(100);

  // ***Write 1*** -- First we send the 50 byte header
  // These 3 lines send the command to write bytes to the newly created file.
  USB.write(0x57);
  USB.write(0xAB);
  USB.write(0x2D);
  // Header data for the bitmap image
  USB.write((byte)0x42); USB.write((byte)0x4D); USB.write((byte)0x38); USB.write((byte)0x0C);
  USB.write((byte)0x00); USB.write((byte)0x00); USB.write((byte)0x00); USB.write((byte)0x00);
  USB.write((byte)0x00); USB.write((byte)0x00); USB.write((byte)0x36); USB.write((byte)0x00);
  USB.write((byte)0x00); USB.write((byte)0x00); USB.write((byte)0x28); USB.write((byte)0x00);
  USB.write((byte)0x00); USB.write((byte)0x00); USB.write((byte)0x20); USB.write((byte)0x00);
  USB.write((byte)0x00); USB.write((byte)0x00); USB.write((byte)0x20); USB.write((byte)0x00);
  USB.write((byte)0x00); USB.write((byte)0x00); USB.write((byte)0x01); USB.write((byte)0x00);
  USB.write((byte)0x18); USB.write((byte)0x00); USB.write((byte)0x00); USB.write((byte)0x00);
  USB.write((byte)0x00); USB.write((byte)0x00); USB.write((byte)0x02); USB.write((byte)0x0C);
  USB.write((byte)0x00); USB.write((byte)0x00); USB.write((byte)0x23); USB.write((byte)0x2E);
  USB.write((byte)0x00); USB.write((byte)0x00); USB.write((byte)0x23); USB.write((byte)0x2E);
  USB.write((byte)0x00); USB.write((byte)0x00); USB.write((byte)0x00); USB.write((byte)0x00);
  USB.write((byte)0x00); USB.write((byte)0x00); USB.write((byte)0x00); USB.write((byte)0x00); 
  USB.write((byte)0x00); USB.write((byte)0x00); 

  delay(100);

  // ***Update Pointer 1***
  // This updates the file pointer. I only know that If I remove this part, the file created ends
  // up being only about 2 bytes long regardless of the amount of information you send.
  USB.write(0x57);
  USB.write(0xAB);
  USB.write(0x3D);

  delay(100);

  uint8_t x = 0; uint8_t y = 0; uint8_t color = 0; uint8_t colConv = 0;
  // ***Write all the color data*** -- Next we write the 3072 bytes of color data
  for(uint16_t i=0; i<1536; i++){
    // set length
    dataLength = (byte)2;
    delay(100);
    USB.write(0x57);
    USB.write(0xAB);
    USB.write(0x3C);
    USB.write((byte) dataLength);
    USB.write((byte) 0x00);
    delay(100);

    // write data
    USB.write(0x57);
    USB.write(0xAB);
    USB.write(0x2D);

    for(uint8_t j=0; j<dataLength; j++){
      colConv = colorConvert(mat, x, y, color);
      USB.write((byte)colConv);
      color++;
      if(color > 2){
        color = 0;
        if(x < 31){
          x++;
        }
        else{
          x = 0;
          y++;
        }
      }
    }
    delay(100);

    // update pointer
    USB.write(0x57);
    USB.write(0xAB);
    USB.write(0x3D);
    delay(100);
  }
  // ***END COLOR DATA***

  // ***End file bytes***
  // This last chunk simply takes 2 bytes of 0's onto the end of the file to
  // signal file end.
  // set length
  dataLength = 2;
  delay(100);
  USB.write(0x57);
  USB.write(0xAB);
  USB.write(0x3C);
  USB.write((byte) dataLength);
  USB.write((byte) 0x00);
  delay(100);

  // write data
  USB.write(0x57);
  USB.write(0xAB);
  USB.write(0x2D);
  USB.write((byte)0x00);
  USB.write((byte)0x00);
  delay(100);

  // update pointer
  USB.write(0x57);
  USB.write(0xAB);
  USB.write(0x3D);
  delay(100);
}

// Closes the file
void fileClose(byte closeCmd){
  USB.write(0x57);
  USB.write(0xAB);
  USB.write(0x36);
  USB.write((byte)closeCmd);
}


