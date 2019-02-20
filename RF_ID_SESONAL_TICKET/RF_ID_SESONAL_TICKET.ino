#include <ESP8266WiFi.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include <FirebaseArduino.h>
float bal;
int amt, x = 0;
String input;
#define FIREBASE_HOST "mybunk-e6f9c.firebaseio.com"
#define FIREBASE_AUTH "y57mVZYNUAe1beRBJbNQGAGJEM5UHNEMxN6yKfCe"
#define WIFI_SSID "mybunk"
#define WIFI_PASSWORD "fuel8266"

void setup()
{
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    lcd.clear();
    lcd.print("Connecting");
    delay(500);
  }
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  lcd.clear();
    lcd.print("Connected");
    delay(500);

}


void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SCAN YOUR CARD");
  delay(500);
  if(Serial.available()>0){
    String input = Serial.readString();
    delay(300);
    lcd.clear();
    lcd.print(input);
    delay(500);
    int bl = Firebase.getInt(input);
    if(bl>0){
      lcdOUT(1,bl);
      bl = bl - 1;
      Firebase.setInt(input,bl);
    }
    else{
      lcdOUT(0,bl);
    }
  }
}

void lcdOUT(int st ,int _bl){
    lcd.clear();
    lcd.setCursor(0, 0);
    if(st == 1){
      lcd.print("     ALLOWED");
    }
    else{
      lcd.print("    DENIED");
    }
    lcd.setCursor(0,1);
    lcd.print("BALENCE :");
    lcd.setCursor(10,1);
    lcd.print(_bl);
    delay(2000);
    return;
}
