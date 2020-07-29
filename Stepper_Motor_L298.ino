#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define potentiometer  A0  //10k Variable Resistor
#define bt_F A1 // Clockwise Button
#define bt_S A2 // Stop Button
#define bt_B A3 // Anticlockwise Button

#define in1 11 //Motor  L298 Pin in1 
#define in2 10 //Motor  L298 Pin in2 
#define in3 9  //Motor  L298 Pin in3 
#define in4 8  //Motor  L298 Pin in4

int read_ADC;
int Speed_LCD;
int Speed;
int Step;
int Mode=0;

void setup() { // put your setup code here, to run once
  
pinMode(potentiometer, INPUT); // declare potentiometer as input 

pinMode(bt_F, INPUT_PULLUP); // declare bt_F as input
pinMode(bt_S, INPUT_PULLUP); // declare bt_S as input
pinMode(bt_B, INPUT_PULLUP); // declare bt_B as input

pinMode(in1, OUTPUT); // declare as output for L298 Pin in1 
pinMode(in2, OUTPUT); // declare as output for L298 Pin in2 
pinMode(in3, OUTPUT); // declare as output for L298 Pin in3   
pinMode(in4, OUTPUT); // declare as output for L298 Pin in4 
  
lcd.begin(16,2);  
lcd.setCursor(0,0);
lcd.print(" WELCOME To  My ");
lcd.setCursor(0,1);
lcd.print("YouTube  Channel");
delay(2000); // Waiting for a while
lcd.clear();
}

void loop() { 

read_ADC = analogRead(potentiometer); // read analogue to digital value 0 to 1023 
Speed = map(read_ADC, 0, 1023, 100, 0);
Speed_LCD = map(read_ADC, 0, 1023, 0, 100); 


lcd.setCursor(0,0);
lcd.print("   Speed: ");
lcd.print(Speed_LCD); 
lcd.print("%  ");

if(digitalRead (bt_F) == 0){Mode = 1;} //For Clockwise
if(digitalRead (bt_S) == 0){Mode = 0;} //For Stop
if(digitalRead (bt_B) == 0){Mode = 2;} //For Anticlockwise

lcd.setCursor(0,1);

if(Mode==0){ lcd.print("      Stop      ");}
if(Mode==1){ lcd.print("    Clockwise   ");}
if(Mode==2){ lcd.print("  Anticlockwise ");}

if(Speed_LCD>0){
if(Mode==1){  
Step = Step+1;
if(Step>3){Step=0;}    
call_Step(Step);// Stepper motor rotates CW (Clockwise)
}

if(Mode==2){
Step = Step-1;
if(Step<0){Step=3;}  
call_Step(Step);// Stepper motor rotates CCW (Anticlockwise)
}

delay(Speed);
}  


}

//The sequence of control signals for 4 control wires is as follows:
//Step C0 C1 C2 C3
//  1  1  0  1  0
//  2  0  1  1  0
//  3  0  1  0  1
//  4  1  0  0  1

void call_Step(int i){
    switch (i) {
      case 0:  // 1010
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
      break;
      case 1:  // 0110
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
      break;
      case 2:  //0101
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
      break;
      case 3:  //1001
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
      break;
    }
  }

