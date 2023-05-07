#include <SPI.h>
#include <SD.h>

File numofitems;
String fileName1 = "numofitems";
File velocity;
String fileName2 = "velocity";
File RealTime;
String fileName3 = "RealTime";
void setup() {
  Serial.begin(9600); // start serial port
 
  if (!SD.begin(4)) {
    Serial.println("No SD Module Detected");
    while (1);
  }
}
void loop() {
 numofitems = SD.open(fileName1, FILE_WRITE);
  if (numofitems) {
    numofitems.println(" ");
    numofitems.close();
    Serial.println(" ");
  } else {
    Serial.println("error opening file");
  }


 velocity = SD.open(fileName2, FILE_WRITE);
  if (velocity) {
    velocity.println(" ");
    velocity.close();
    Serial.println(" ");
  } else {
    Serial.println("error opening file");
  }

RealTime = SD.open(fileName3, FILE_WRITE);
  if (RealTime) {
    RealTime.println(" ");
    RealTime.close();
    Serial.println(" ");
  } else {
    Serial.println("error opening file");
  }
}
