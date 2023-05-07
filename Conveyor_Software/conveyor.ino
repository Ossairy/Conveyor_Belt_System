#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>
File RealTime;
String fileName3 = "RealTime";
File numofitems;
String fileName1 = "numofitems";
File velocity;
String fileName2 = "velocity";
const int IR1 =1 ;
const int IR2 =2;
const int MOTORPWM =3 ;
const int ccw =4;
const int MOdirc =5;
const int cw =6;
const int MOValue =7;
const int rs = 5, en = 4, d4 = 3, d5 = 2, d6 = 1, d7 = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int MOout =0; 
int numitems=0 ;
int vel =0 ;
bool Flag = LOW;
int totalnumitems =0;
void setup() {
 pinMode( MOTORPWM ,OUTPUT);
 pinMode(cw,OUTPUT);
 pinMode(ccw,OUTPUT);
 //pinMode( d5 ,OUTPUT);
// pinMode(d6,OUTPUT);
// pinMode(d7,OUTPUT);
// pinMode(Up,INPUT);
// pinMode(Dwn,INPUT);
 pinMode( MOValue ,INPUT);
 pinMode(MOdirc,INPUT);
 pinMode(IR1,INPUT);
 pinMode(IR2, INPUT);
 lcd.begin(16, 2);
 if (!SD.begin(4)) {
    Serial.println("No SD Module Detected");
    while (1);
  }
}

void loop() {
  //numofitems = SD.open(fileName1, FILE_WRITE);
 // velocity = SD.open(fileName2, FILE_WRITE);
  lcd.setCursor(0, 0);
  lcd.print("carrying :" );
  lcd.print(numitems);
  lcd.print("items" );
  lcd.setCursor(0, 1);
  lcd.print("velocity :" );
  lcd.print(vel);
  lcd.print("rpm" );
// ____________________ H bridge & IRs __________________________
MOout = map(analogRead(MOValue), 0 , 1024 , 0 , 255);
if(digitalRead(MOdirc)){
 
  digitalWrite(ccw, LOW);
  digitalWrite(cw, HIGH);
   if(analogRead(IR1)>200){
     numitems++;
     totalnumitems++;
     Flag = HIGH;
     
   } else if(IR2){
    numitems--;
    Flag = HIGH;
   }
  
}
  else if(!digitalRead(MOdirc)){
  
  digitalWrite(cw, LOW);
  digitalWrite(ccw, HIGH);
if(analogRead(IR2)>200){
     numitems++;
     totalnumitems++;
     Flag = HIGH;
} if(IR1){
    //else if
    numitems--;
    Flag = HIGH;
}
  
}
if (numitems >0)
 {analogWrite(MOTORPWM , MOout);
 }else 
  { analogWrite(MOTORPWM ,0);
}
if(Flag){
  velocity = SD.open(fileName2, FILE_WRITE);
  if (velocity) {
    velocity.println(vel);
    velocity.close();
    Serial.println(vel);
  } else {
    Serial.println("error opening file");
  }
  numofitems = SD.open(fileName1, FILE_WRITE);
  if (numofitems) {
    numofitems.println(numitems);
    numofitems.close();
    Serial.println(numitems);
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
  Flag = LOW;
  }
  
}
