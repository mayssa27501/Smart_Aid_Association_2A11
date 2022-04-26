
#define PIN_LED1 2 //le numéro de la broche sur laquelle la lampe 1  est branchée
#define PIN_LED2 4 //le numéro de la broche sur laquelle la lampe 2  est branchée

char data;


#include <Servo.h>
Servo myservo;  // create servo object to control a servo

int pos = 0; 
void setup() {
   Serial.begin(9600);// setup Serial Monitor to display information
  pinMode(3, INPUT);// Input from sensor

  pinMode(PIN_LED1, OUTPUT);// OUTPUT to alarm or LED
  pinMode(PIN_LED2,OUTPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

}

void loop() {
      int motion =digitalRead(3);
    if (Serial.available()){    
    data =Serial.read();
    if (motion && data=='1'){
         Serial.write('1'); //envoyer le nouvel état de la lampe
        digitalWrite(PIN_LED1,LOW);
      digitalWrite(PIN_LED2,HIGH);
    }
  else if(data=='1') {
       Serial.write('0'); //envoyer le nouvel état de la lampe
     digitalWrite(PIN_LED1,HIGH);
      digitalWrite(PIN_LED2,LOW);
  }

  else if(data='2')
  {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

    myservo.write(85);              // tell servo to go to position in variable 'pos'
    delay(500);
      myservo.detach();

  }

  
  else if(data='0')
{
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object

       myservo.write(110);              // tell servo to go to position in variable 'pos'
    delay(500);
      myservo.detach();           // tell servo to go to position in variable 'pos'
   }
  }
}
  
