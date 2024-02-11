#define IN2 13
#define IN1 12
#define IN4 9
#define IN3 8
#define E2 10
#define E1 11
#define a4 7
#define a5 6
#define a6 5
#define a7 3
#define TRIGGER_PIN 4
#define ECHO_PIN 2
#define MAX_DISTANCE 100

#include<NewPing.h>
#include <Wire.h>
#include <MPU6050_light.h>
MPU6050 mpu(Wire);

unsigned long currentTime;
unsigned long  previousTime=0;
const int eventInterval=50;
int q=0;
char rC;
int c = 4,timex,now;
int speedE1=250;
int speedE2 =speedE1-70 ;
unsigned long timer = 0;
unsigned int dist;
float temp ,t,Z,temp1;
bool ir1, ir2, ir3, ir4, ir5, ir6, ir7, ir8;
long duration, average;
long aver[3];
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup(){
Serial.begin(9600);
pinMode(A0, INPUT);
pinMode(A1, INPUT);
pinMode(A2, INPUT);
pinMode(A3, INPUT);
pinMode(a4, INPUT);
pinMode(a5, INPUT);
pinMode(a6, INPUT);
pinMode(a7, INPUT);
pinMode(TRIGGER_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);
pinMode(E1, OUTPUT);
pinMode(E2, OUTPUT);
pinMode(IN4, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN1, OUTPUT);                        
  Wire.begin();
  mpu.begin();
 mpu.calcGyroOffsets();                          // This does the calibration
  
}
void Bot(bool IN_1,bool IN_2,int speedE1,bool IN_3,bool IN_4,int speedE2){
    digitalWrite(IN1,IN_1);
    digitalWrite(IN2,IN_2);
    analogWrite(E1,speedE1);
    digitalWrite(IN3,IN_3);
    digitalWrite(IN4,IN_4);
    analogWrite(E2,speedE2);
}
   
void midObj(){
    ir6 = digitalRead(a5);
    ir5 = digitalRead(a4);
    if(ir6==HIGH){
        mpu.update(); Z=mpu.getAngleZ(); 
        temp = Z-88;
        rotation(temp);
        Bot(HIGH,LOW,200,HIGH,LOW,200);
        mpu.update(); Z=mpu.getAngleZ(); 
        temp=Z+88;
        rotation(temp);
        Bot(HIGH,LOW,200,HIGH,LOW,200);
        mpu.update(); Z=mpu.getAngleZ(); 
        temp=Z+88;
        rotation(temp);
        Bot(HIGH,LOW,200,HIGH,LOW,200);
        mpu.update(); Z=mpu.getAngleZ(); 
        temp=Z-88;
        rotation(temp);
        Bot(HIGH,LOW,200,HIGH,LOW,200);
    }
    
    else if(ir5==HIGH){
        mpu.update(); Z=mpu.getAngleZ(); 
        temp = Z+88;
        rotation(temp);
        Bot(HIGH,LOW,200,HIGH,LOW,200);
        mpu.update(); Z=mpu.getAngleZ(); 
        temp=Z-88;
        rotation(temp);
        Bot(HIGH,LOW,200,HIGH,LOW,200);
        mpu.update(); Z=mpu.getAngleZ(); 
        temp=Z-88;
        rotation(temp);
        Bot(HIGH,LOW,200,HIGH,LOW,200);
        mpu.update(); Z=mpu.getAngleZ(); 
        temp=Z+88;
        rotation(temp);
        Bot(HIGH,LOW,200,HIGH,LOW,200);
      }
}
void rotation(float temp ){
    timex = 5000; 
    now=millis();
    while(true){
        mpu.update(); Z=mpu.getAngleZ();    
        if ( Z <= 43 && Z >= 47 ){ Bot(LOW,LOW,0,LOW,LOW,0);}
        else if ( Z< 47 ){ Bot(HIGH,LOW,155,LOW,HIGH,155); }
        else { Bot(LOW,HIGH,200,HIGH,LOW,200); }
        if((millis()-now)>timex){break;}
    }
   Bot(LOW,LOW,0,LOW,LOW,0);
}

void loop(){ 
 Bot(HIGH,LOW,255,HIGH,LOW,255);

//  if(Serial.available()){
//        rC = Serial.read();
//        if(rC == 'a'){c=0;}//auto mode
//        else if(rC == 'b'){c=1;}//human tracking mode
//        else if(rC == 'c'){c=2;}//line tracking mode
//        else if(rC == 'd'){c=3;}//bluetooth mode
//        else if(rC == 'e'){c=4;}//stop
//        else if(c>4){c=0;}
//    }
//    switch(c){
//    case 0 :     Serial.println('a');
//                 ir6 = digitalRead(a5);
//                 ir5 = digitalRead(a4);
//                 if(ir6 == true&&ir5 == true){ 
//                   
//                   dist= sonar.ping_cm();
//                   ir1 = digitalRead(A0);
//                   ir2 = digitalRead(A1); 
//                   if (dist == 0) {dist = 40;}  
//                   if ( dist > 13 && ir1 == false && ir2 == false ){Bot(HIGH,LOW,200,HIGH,LOW,200); }
//                   
//                   dist= sonar.ping_cm();
//                   if (dist == 0) {dist = 40;}
//                   ir1 = digitalRead(A0);ir2 = digitalRead(A1);
//                   if ( dist < 13 && (ir1 == true || ir2 == true )){
//                   
//                      ir3 = digitalRead(A2); ir4 = digitalRead(A3);
//                      if ( ir3 == true && ir4 == false ){ Bot(LOW,LOW,200,LOW,LOW,200);  }
//                      ir3 = digitalRead(A2); ir4 = digitalRead(A3);
//                      if ( ir4 == true && ir3 == false ){ Bot(LOW,HIGH,200,HIGH,LOW,200);  }
//                    }
//                    dist= sonar.ping_cm();
//                    if (dist == 0) {dist = 40;}
//                     ir1 = digitalRead(A0); ir2 = digitalRead(A1);
//                    if ( dist<5 && ir1==false && ir2==false ){  midObj();  }
//                    dist = sonar.ping_cm();
//                    if (dist == 0) {dist = 40;}
//                     ir1 = digitalRead(A0); ir2 = digitalRead(A1);
//                    if ( ir1==false && (dist<5 && ir2==true )){  
//                        temp = Z-45;//slightly left
//                        rotation( temp );
//                        Bot(HIGH,LOW,200,HIGH,LOW,200);
//                    }
//                   dist= sonar.ping_cm();
//                    if (dist == 0) {dist = 40;}
//                    ir1 = digitalRead(A0);
//                    ir2 = digitalRead(A1);
//                    if ( ir2==false && (dist<5 && ir1==true )){  
//                        temp = Z+45;//slightly left
//                        rotation( temp );
//                        Bot(HIGH,LOW,200,HIGH,LOW,200);
//                    }
//                 }
//                 ir5 = digitalRead(a4);
//                 if (ir5 == false){ 
//                    Bot(LOW,HIGH,200,LOW,HIGH,200);
//                    temp = Z+45;//slightly Right
//                    rotation( temp );
//                    Bot(HIGH,LOW,200,HIGH,LOW,200);}
//                 ir6 = digitalRead(a5);
//                 if (ir6 == false){ 
//                    Bot(LOW,HIGH,200,LOW,HIGH,200);
//                    temp = Z-45;//slightly left
//                    rotation( temp );
//                    Bot(HIGH,LOW,200,HIGH,LOW,200);}
//                break;  
//    case 1 :    Serial.println('b');
//                dist= sonar.ping_cm();
//                if (dist == 0) {dist = 40;}
//                if(((dist>=7)&&(dist < 14))||dist>=30){ Bot( LOW, LOW,  0, LOW, LOW,  0); }
//                dist= sonar.ping_cm();
//                if (dist == 0) {dist = 40;}
//                ir2 = digitalRead(A1);
//                if((ir2==1) && (dist>=15)){ Bot(HIGH, LOW,255, LOW,HIGH,100); }  //slightly right
//                dist= sonar.ping_cm();
//                if (dist == 0) {dist = 40;}
//                ir1 = digitalRead(A0); 
//                if((dist>=15)&&(ir1==1)){ Bot( LOW,HIGH,100,HIGH, LOW,255); }  //slightly left
//                dist= sonar.ping_cm();
//                if (dist == 0) {dist = 40;}
//                if(dist>=25 && dist<=29){ Bot(HIGH,LOW,255,HIGH,LOW,255); }  //stright with high speed
//                dist= sonar.ping_cm();
//                if (dist == 0) {dist = 40;}
//                if (dist>=20 && dist<=24){ Bot(HIGH,LOW,200,HIGH,LOW,200); } //stright with medium speed
//                dist= sonar.ping_cm();
//                if (dist == 0) {dist = 40;}
//                else if(dist>=15 && dist<=19){ Bot(HIGH,LOW,150,HIGH,LOW,150); }         //stright with low speed
//                ir1 = digitalRead(A0); ir2 = digitalRead(A1);
//                if((ir2==0) && (ir1==1)) { Bot(LOW,HIGH,100,HIGH,LOW,255); }     //left
//                ir1 = digitalRead(A0); ir2 = digitalRead(A1);
//                if((ir2==1)&&(ir1==0)) { Bot(HIGH,LOW,255,LOW,HIGH,100); }       //right.    
//                dist= sonar.ping_cm();
//                    if (dist == 0) {dist = 40;}
//                if((dist>=0 && dist<=7)|| (dist>=0 && dist<=8)){ Bot(LOW,HIGH,255,LOW,HIGH,255); } //back  
//                dist= sonar.ping_cm();
//                    if (dist == 0) {dist = 40;}
//                ir1 = digitalRead(A0); 
//                if((dist<=6)&&(ir1==1)){ Bot( LOW,HIGH,100, LOW,HIGH,255);}      //slightly back left
//                dist= sonar.ping_cm();
//                    if (dist == 0) {dist = 40;}
//                 ir1 = digitalRead(A0); ir2 = digitalRead(A1);
//                if(dist<=6 && (ir2==1)){ Bot( LOW,HIGH,255, LOW,HIGH,100);}         //stright back right
//                break;
//    case 2 : 
//                Serial.println('c');
//               /* dist= sonar.ping_cm();
//                if (dist == 0) {dist = 40;}
//                if(dist <=15) {
//                    Bot( LOW, LOW,  0, LOW, LOW,  0);
//                    delay(500);
//                    mpu.update(); Z=mpu.getAngleZ();
//                    temp = Z+45;//turnRight
//                    rotation( temp );
//                    Bot(HIGH, LOW,200,HIGH, LOW,200);
//                    delay(500);
//                    mpu.update(); Z=mpu.getAngleZ();
//                    temp = Z-45;//turnLeft
//                    rotation( temp );
//                    Bot(HIGH, LOW,200,HIGH, LOW,200);
//                    delay(500);
//                    mpu.update(); Z=mpu.getAngleZ();
//                    temp = Z-45;
//                    rotation( temp );
//                    Bot(HIGH, LOW,200,HIGH, LOW,200);
//                    delay(500);
//                    mpu.update(); Z=mpu.getAngleZ();
//                    temp = Z+45;
//                    rotation( temp );
//                }*/
//                ir7= digitalRead(a6); ir8= digitalRead(a7);
//                if (ir7==HIGH && ir8==HIGH)        { Bot(HIGH, LOW,150,HIGH, LOW,150); }
//                ir7= digitalRead(a6); ir8= digitalRead(a7);
//                if ( ir7==HIGH && ir8== LOW ) { Bot( LOW,HIGH,1500,HIGH, LOW,150);}
//                ir7= digitalRead(a6); ir8= digitalRead(a7);
//                if ( ir7== LOW && ir8==HIGH ) { Bot( HIGH,LOW,150, LOW,HIGH,150); }
//                ir7 = digitalRead(a6); 
//                ir8 = digitalRead(a7);
//                if ( ir7== LOW && ir8== LOW ) { Bot( LOW, LOW,  0, LOW, LOW,  0);}
//                break;
//    case 3 :    Serial.println('d');
//                if(Serial.available()){
//                  rC=Serial.read();
//                  if(rC=='F'){ Bot(HIGH, LOW,255,HIGH, LOW,255);}
//                  if(rC=='B'){ Bot( LOW,HIGH,255, LOW,HIGH,255);}
//                  if(rC=='R'){ Bot( HIGH, LOW,255, LOW, HIGH,255);}
//                  if(rC=='L'){ Bot( LOW,HIGH,255,HIGH, LOW,255);}
//                  if(rC=='S'){ Bot(LOW, LOW,255, LOW,LOW,255);}
//                }
//                else Bot(LOW, LOW,255, LOW,LOW,255);
//                
//                break;
//    case 4 :    Serial.println('e');
//                Bot( LOW, LOW,  0, LOW, LOW,  0); 
//                break;
//    }
    }              
 
