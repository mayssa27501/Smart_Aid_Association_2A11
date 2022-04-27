
#define PIN_LED1 2 //le numéro de la broche sur laquelle la lampe 1  est branchée
#define PIN_LED2 4 //le numéro de la broche sur laquelle la lampe 2  est branchée


#include <SPI.h> 

#include <MFRC522.h>

#include <Wire.h> 

#include <LiquidCrystal_I2C.h>



#define SS_PIN 10 

#define RST_PIN 9 

#include <Servo.h>
Servo myservo;  // create servo object to control a servo

int pos = 0; 

char data;



LiquidCrystal_I2C lcd(0x27,16,2);


MFRC522 mfrc522(SS_PIN, RST_PIN); // Instance of the class



int code[] = {197,140,113,31}; //This is the stored UID (Unlock Card)

int codeRead = 0;

String uidString;


int redLed = 12;//
int greenLed = 11;
int buzzer = 10;
int smokeA0 = A5;
// Your threshold value
int sensorThres = 700;
int ftime=1;

void setup() {
   Serial.begin(9600);// setup Serial Monitor to display information
  pinMode(3, INPUT);// Input from sensor

  pinMode(PIN_LED1, OUTPUT);// OUTPUT to alarm or LED
  pinMode(PIN_LED2,OUTPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  ////
  

   SPI.begin();       // Init SPI bus

   mfrc522.PCD_Init(); // Init MFRC522 

   Serial.println("13458799");



   lcd.init();

  // Print a message to the LCD.

  lcd.backlight();

  lcd.setCursor(0,0);

  lcd.print("Show your card");
  
   pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);

}

void loop() {
  int analogSensor = analogRead(smokeA0);
//Serial.println(analogSensor);
  if (analogSensor > sensorThres )
  {

   if (ftime==1) Serial.println("4");
    digitalWrite(buzzer,HIGH);
    ftime=0;
   
  }
  else
  {

    noTone(buzzer);
    ftime=1;
  }
  
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
    delay(1000);
           myservo.write(110);              // tell servo to go to position in variable 'pos'
delay(1000);
      myservo.detach();

  }

  
  else if(data='0')
{
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object

       myservo.write(110);              // tell servo to go to position in variable 'pos'
    delay(1000);
    myservo.write(85);              // tell servo to go to position in variable 'pos'
    delay(1000);
      myservo.detach();           // tell servo to go to position in variable 'pos'
   }
   else if(data=='4'){
   
      lcd.clear();
      lcd.setCursor (0,0); // go to start of 2nd line
     lcd.print("-----CLOSED-----");

     
   delay(1500);
    }

     else if (data=='3'){
        
       lcd.clear();
       lcd.setCursor (0,0); // go to start of 2nd line
       lcd.print("------OPEN------");
   delay(1500);
  
     }

else if ( mfrc522.PICC_IsNewCardPresent() && data=='3')

    {
      /**/

        if ( mfrc522.PICC_ReadCardSerial())

        

        {

           lcd.clear();

           Serial.print("Tag UID:");

           lcd.setCursor(0,0);

           lcd.print("Tag UID:");

           lcd.setCursor(0,1);

           for (byte i = 0; i < mfrc522.uid.size; i++) {  

                  Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "); 

                  Serial.print(mfrc522.uid.uidByte[i], HEX);

                  

                  lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");

                  lcd.print(mfrc522.uid.uidByte[i], HEX);

                //  lcd.print(" ");

            }

            

            Serial.println();



            int i = 0;

            boolean match = true;

            while(i<mfrc522.uid.size)

            {

    

               if(!(int(mfrc522.uid.uidByte[i]) == int(code[i])))

               {

                  match = false;

               }

              i++;

            }



            delay(3000);

           lcd.clear();

           lcd.setCursor(0,0);

           

           

           if(match)

           {



              lcd.print("Authorized access");
              uidqt();

              

           

    

           }else{

              lcd.print(" Access denied  "); 

             Serial.println("\nUnknown Card");

           }

             

             Serial.println("============================");

            

             mfrc522.PICC_HaltA();



             delay(3000); 

             reset_state();

        }

        //uidqt();

}
  if (data == '5')  //si le caractère lu est égale à 1
    {
      digitalWrite(buzzer,LOW);  // LED s'éteint et le buzzer s'arrête de sonner
       
  }
  }
    delay(100);
}





void reset_state()

{
    
    lcd.clear();

    lcd.setCursor(0,0);

    lcd.print("Show your card");

}

void uidqt ()
{
  char content;
 /* byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  content=content.substring(1);
    char arr[content.length()+1]; 
 for (int x = 0; x < sizeof(arr); x++) { 
        arr[x] = content[x]; 
        
        }*/
  Serial.write(content);
}
