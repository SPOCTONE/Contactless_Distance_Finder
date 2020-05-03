#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

#include <NewPing.h>
#define MAX_DISTANCE 400
const int echoPin = 12;
const int trigPin = 10;
NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

#include <DHT.h>
#define DHTPIN 7      
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

float duration, distance, speed, t, h;

void setup() {
  Serial.begin (9600);
  lcd.init();
  lcd.backlight();
  dht.begin();
}

void loop() {  
 
  h = dht.readHumidity();
  t = dht.readTemperature();
  
  int iterations = 5;
  duration = sonar.ping_median(iterations);
  speed = 331.4 + (0.606 * h) + (0.0124 * t);
  distance = (duration / 2) * (speed / 10000) - 3;
  
  if (distance >= 400 || distance <= 2){
    lcd.setCursor(0,0);
     lcd.print("N a N ");
    lcd.print(t);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print(speed);
    lcd.print("m/s ");
    lcd.print(h);
    lcd.print("%");
  }
   else {
    lcd.setCursor(0,0);
     lcd.print(distance);
     lcd.print("cm ");
    lcd.print(t);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print(speed);
    lcd.print("m/s ");
    lcd.print(h);
    lcd.print("%");
    delay(500);
  } 
  delay(500);
  lcd.clear();
}
