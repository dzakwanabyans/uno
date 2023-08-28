#include <LiquidCrystal_I2C.h>
  LiquidCrystal_I2C lcd(0x27,16,2);

const int sensor=12;
const int buzzer=11;
const int add=10;
const int del=9;
const int rst=8;

//data
int value=0;


void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode (sensor, INPUT);
  pinMode (add, INPUT);
  pinMode (buzzer, OUTPUT);
}

void loop() {
  lcd.setCursor(4, 0);
  lcd.print("COUNTER:");
  lcd.setCursor(0, 1);
  lcd.print(value);
  int btn_add=digitalRead(add);
  int btn_del=digitalRead(del);
  int btn_rst=digitalRead(rst);
  int R=digitalRead(sensor);
  if(R==LOW){
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("COUNTER:");
    value++;
    lcd.setCursor(0, 1);
    lcd.print(value);
    tone(buzzer, 2000);
    delay(500);
    noTone(buzzer);
    while(R==LOW){
      R=digitalRead(sensor);
    }
  }
  if(btn_add==HIGH){
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("COUNTER:");    
    value++;
    lcd.setCursor(0, 1);
    lcd.print(value);
    tone(buzzer, 2000);
    delay(500);
    noTone(buzzer);
  }
  if(btn_del==HIGH){
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("COUNTER:");
    value--;
    lcd.setCursor(0, 1);
    lcd.print(value);
    tone(buzzer, 2000);
    delay(500);
    noTone(buzzer);
  }
  if(btn_rst==HIGH){
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("COUNTER:");
    value=0;
    lcd.setCursor(0, 1);
    lcd.print(value);
    tone(buzzer, 2000);
    delay(500);
    noTone(buzzer);
  }
}
