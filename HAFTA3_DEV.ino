#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>
#include <SPI.h>

constexpr uint8_t SS_PIN = D4 
constexpr uint8_t RST_PIN = D3

#define yesilLed D1
#define kirmiziLed D2

MFRC522 mfrc522(SS_PIN, RST_PIN);   
MFRC522 :: MIFARE_Key key;
String tag;

void setup() 
{
  pinMode(yesilLed, OUTPUT);
  pinMode(kirmiziLed, OUTPUT);
  
  Serial.begin(9600);   
  SPI.begin();      
  mfrc522.PCD_Init();  
  Serial.println ("Kart okundu");
   
}

void loop() 
{
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
   for (byte i = 0; i<4;i++) {
    tag + = mfrc522.uid.uidByte [i];
   
  }
 
  Serial.println(tag);
  if (tag == "kart bulunamadı") {
  Serial.println("Hoşgeldiniz Eda Hanım ");
    digitalWrite(yesilLed, HIGH);
    delay(1000);
    
    digitalWrite(yesilLed, LOW);
    delay(1000);
  }
  
  else   {
    
    Serial.println(" Giris Basarisiz. ");
    digitalWrite(kirmiziLed, HIGH);
      delay(1000);
    digitalWrite(kirmiziLed, LOW);
      
  }

  tag= "";
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCryptol();
