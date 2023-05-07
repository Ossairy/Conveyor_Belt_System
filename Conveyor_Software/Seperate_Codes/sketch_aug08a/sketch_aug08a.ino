#include <LiquidCrystal.h>

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
}

void loop() {


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
   if(IR1){
     numitems++;
   } else if(IR2){
    numitems--;
   }
  
}
  else if(!digitalRead(MOdirc)){
  
  digitalWrite(cw, LOW);
  digitalWrite(ccw, HIGH);
if(IR2)
     numitems++;
    else if(IR1)
    numitems--;
   
  
}
if (numitems >0)
 analogWrite(MOTORPWM , MOout);
 else 
   analogWrite(MOTORPWM ,0);
}
