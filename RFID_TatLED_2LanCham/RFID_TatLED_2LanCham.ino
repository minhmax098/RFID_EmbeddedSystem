/*
  Ket noi voi Arduino Uno hoac Mega
  ------------------------------------------------------------
   Pin layout should be as follows:
   Signal     Pin              Pin               Pin
              Arduino Uno      Arduino Mega      MFRC522 board
  ------------------------------------------------------------
   Reset      9                5                 RST
   SPI SS     10               53                SDA
   SPI MOSI   11               51                MOSI
   SPI MISO   12               50                MISO
   SPI SCK    13               52                SCK

*/

#include <SPI.h>
#include <MFRC522.h> // thu vien "RFID".

const int LED1 = 2; // LED do
unsigned long time_lan1;
int count = 0;

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);
unsigned long uidDec, uidDecTemp; // hien thi so UID dang thap phan

void setup() {
  pinMode(LED1, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Waiting for card...");
}

void blinkLED1() {
  delay(1000);
  digitalWrite(LED1, HIGH);
  delay(200);
  digitalWrite(LED1, LOW);
}

void blinkLED2() {
    delay(1000);
  digitalWrite(LED1, HIGH);
  delay(200);
  digitalWrite(LED1, LOW);
  delay(200);
  digitalWrite(LED1, HIGH);
  delay(200);
  digitalWrite(LED1, LOW);
}

void loop() {
  // Tim the moi
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Doc the
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  uidDec = 0;
  Serial.println("================================================");

  // Hien thi so UID cua the
  Serial.print("Card UID: ");
  uidDec = addDec(mfrc522);
  unsigned long t = (millis() - time_lan1);
 
  Serial.println(uidDec);

  if (uidDec == 688952409) {
    /*
    if (digitalRead(LED1) == LOW){
      digitalWrite(LED1, HIGH);
      delay(1000);
    }
    else{
    */
    
  
      count++;
      if (count == 1) time_lan1 = millis();
      Serial.print("count: ");
      Serial.print(count);
      Serial.print("\t time(s): ");
      Serial.println(t);
      if (count == 2) {
        //digitalWrite(LED1, LOW);
        blinkLED2();
        count = 0;
        return;
      }
       if ( t > 1000){
    blinkLED1();
  }
      delay(500);
    //}
  }
}
