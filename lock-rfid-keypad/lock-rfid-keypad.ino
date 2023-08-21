#include <SPI.h>
#include <Keypad.h>
  const byte ROWS = 4;    //rows keypad
  const byte COLS = 4;    //cols keypad 
  char Keys[ROWS][COLS] = {   //array keypad
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
  };
  
  byte rowPins[ROWS] = {A3, A2, A1, A0}; //pin deklaration
  byte colPins[COLS] = {5, 6, 7, 8};

  Keypad keypad = Keypad( makeKeymap(Keys), rowPins, colPins, ROWS, COLS);


#include <MFRC522.h>
  #define RST_PIN         9
  #define SS_PIN          10
  MFRC522 mfrc522(SS_PIN, RST_PIN); 


#include <LiquidCrystal_I2C.h>
  int totalColom=16;
  int totalRow=2;
  LiquidCrystal_I2C lcd(0x27,16,2);

#define RELAY 3
#define BUZZER 4

//DATABASE
int status=0; //RELAY/pin status lock
const String UID="05 8A 3F F2 A8 D1 00";
char pin[6]="123456";
char totalInput[6]; //merge input pin
char input;
uint8_t i=0; //index input pin
int j=5; //index lcd cursor for pin
boolean cardMode=true; //system status




//CUSTOM CHARACTER
byte custom0[8]={
  0b11111,
  0b10001,
  0b10000,
  0b10000,
  0b11111,
  0b11011,
  0b11011,
  0b11111,
};

byte custom1[8]={
  0b00011,
  0b00110,
  0b01100,
  0b11111,
  0b01110,
  0b01100,
  0b11000,
  0b10000,
};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, custom0);
  lcd.createChar(1, custom1);
  pinMode(BUZZER, OUTPUT);
  pinMode(RELAY, OUTPUT);
  lcd.setCursor(2, 0);
  lcd.print("SMART SYSTEM");
  delay(1000);
  lcd.clear();
  digitalWrite(RELAY, HIGH);
}

void loop() {
  if(cardMode==true){
    lcd.setCursor(2, 0);
    lcd.print("SMART SWITCH");
    lcd.setCursor(0, 1);
    lcd.print("CONFIRM IDENTITY");

    //find new card
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
        return; 
    }
    //choose a card
    if ( ! mfrc522.PICC_ReadCardSerial()) {
        return;
    }

    //read data card
    lcd.clear();
    Serial.print("UID tag :");
    lcd.setCursor(0, 0);
    lcd.print("scanning");
    String ID= "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      lcd.print(".");//animation
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      ID.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      ID.concat(String(mfrc522.uid.uidByte[i], HEX));
      delay(100);
    }
    Serial.println();
    ID.toUpperCase();

    //check data card
    if(ID.substring(1)==UID){
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("CONFIRMED");
      lcd.setCursor(12, 0);
      lcd.write((byte)0);
      tone(BUZZER, 2000);
      delay(700);
      noTone(BUZZER);
      delay(1000);
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("INPUT PIN!");
      cardMode=false;
    }
    else{
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("UNKNOWN IDCARD");
      for(int i=0; i<3; i++){
        tone(BUZZER, 2000);
        delay(400);
        noTone(BUZZER);
        delay(100);
      }
      delay(1000);
      lcd.clear();
    }
  }

  else if(cardMode==false){
    input=keypad.getKey();
    if(input){
      tone(BUZZER, 2000);
      delay(100);
      noTone(BUZZER);
      totalInput[i]=input;
      lcd.setCursor(j, 1);
      lcd.print("*");
      Serial.println(i);
      Serial.println(totalInput[i]);
      i++;
      j++;
    }
    if(i==6){
      Serial.println(totalInput);
      Serial.println(pin);
      if(!(strncmp(totalInput, pin, 6))){
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("pincorrect");
        if(status==0){
          lcd.clear();
          digitalWrite(RELAY, LOW);
          lcd.setCursor(1, 1);
          lcd.print("ELECTRICAL ON");
          lcd.setCursor(14, 1);
          lcd.write((byte)1);
          tone(BUZZER, 2000);
          delay(2000);
          noTone(BUZZER);
          lcd.clear();
          status=1;
          totalInput[i]="";
          i=0;
          j=5;
          cardMode=true;
        }      
        else{
          lcd.clear();
          digitalWrite(RELAY, HIGH);
          lcd.setCursor(1, 1);
          lcd.print("ELECTRICAL OFF");
          tone(BUZZER, 2000);
          delay(2000);
          noTone(BUZZER);
          lcd.clear();
          status=0;
          totalInput[i]="";
          i=0;
          j=5;
          cardMode=true;
        }
      }
      else{
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("PIN INCORRECT!");
        for(int i=0; i<3; i++){
          tone(BUZZER, 2000);
          delay(400);
          noTone(BUZZER);
          delay(100);
        }
      delay(1000);
      lcd.clear();
      totalInput[i]="";
      i=0;
      j=5;
      cardMode=true;
      }
    }
  }
}
