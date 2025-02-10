#include <NewPing.h>
 
#include <DFPlayer_Mini_Mp3.h>

#include <Keypad.h>

#include "Servo.h"
Servo servo;
int angle; 
unsigned int pingSpeed = 50;
unsigned long pingTimer;
int flag = 0;

#define  LED1 A0
#define  GER  9
#define SERV 11 
#define NUM_KEYS  4
#define MAGN 10
#define TRIGGER_PIN  12
#define ECHO_PIN     13
#define MAX_DISTANCE 400 

char key; 
char myarraw[NUM_KEYS] = { '1', '3', '3', '7'};
char button_pressed[NUM_KEYS];
int k=0;
int s=0;
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1','2','3'},  
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );  

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

void setup() { 
  pinMode(LED1, OUTPUT);  
  pinMode(GER, INPUT);  

  pinMode(MAGN, OUTPUT);

  Serial.begin(9600);
  mp3_set_serial(Serial);
  delay(100);
  mp3_set_volume(30);

  servo.attach(11);
  pingTimer = millis();
 }

void loop () {

  digitalWrite(MAGN, HIGH);

  key = keypad.getKey();
 
   if (  key != NO_KEY )
  {
   button_pressed [k] =  key;
   k = k + 1;
   if(k == NUM_KEYS)
   {for ( uint8_t i = 0; i < NUM_KEYS; i++)
    { 
  if (button_pressed[i] == myarraw[i])
     {s = s + 1;
     
  
      }
      
     }
    
    if(s == NUM_KEYS)
      {
     digitalWrite (MAGN, LOW);
     delay(100);
     mp3_play(3);
     delay(100);
     for (angle = 110; angle >= 20; angle--) {
       servo.write(angle);
       delay(20);
    }
     delay(2000);
     while (flag == 0){
       if (millis() >= pingTimer) {
       pingTimer += pingSpeed;
      sonar.ping_timer(echoCheck);
      }
     }
     if (flag == 1){
      delay(2000);
      for (angle = 20; angle <= 110; angle++) {
       servo.write(angle);
       delay(20);
       }
       if (digitalRead(GER) == HIGH){
        digitalWrite(MAGN, HIGH);}
     }
       k=0;
       s=0;
       flag = 0;
       delay(2000);
     
     
  
  
    
       
   } else {
       digitalWrite (LED1, HIGH);
       delay(100);
       mp3_play(2);
       delay(100);
       delay (2000);
       mp3_stop();
       digitalWrite (LED1, LOW);
       
       k=0;
       s=0;
       }
       }
  }
 }
void echoCheck() { 
  if (sonar.check_timer()) {
    Serial.print(flag);
    if ((sonar.ping_result / US_ROUNDTRIP_CM) < 20)
      flag = 1;
    else if ((sonar.ping_result / US_ROUNDTRIP_CM) > 20)
      flag = 0;
  }}