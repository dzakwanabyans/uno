#define enA 11
#define in1 10
#define in2 9
#define enB 5
#define in3 4
#define in4 3
#define trig 12
#define echo 13

int motorSpeedA = 0;
int motorSpeedB = 0;
char data;
int pwm=255; //set default
long waktu,jarak; //read from us sensor

void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
}

int length(){
  digitalWrite(trig, LOW);
  delay(1);
  digitalWrite(trig, HIGH);
  delay(5);
  digitalWrite(trig, LOW);
  waktu=pulseIn(echo, HIGH);
  jarak=waktu/58.2;
  return jarak;
}


void forward(){
  motorSpeedA = pwm; 
  motorSpeedB = pwm; 
  digitalWrite(enA, motorSpeedA); // Send PWM signal to motor A
  digitalWrite(enB, motorSpeedB); // Send PWM signal to motor B
  // Set Motor A forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // Set Motor B forward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(25);
}

void backward(){
  motorSpeedA = pwm; 
  motorSpeedB = pwm; 
  digitalWrite(enA, motorSpeedA); // Send PWM signal to motor A
  digitalWrite(enB, motorSpeedB); // Send PWM signal to motor B
  // Set Motor A backward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // Set Motor B backward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(25);
}

void right(){
  motorSpeedA = pwm; 
  motorSpeedB = pwm; 
  digitalWrite(enA, motorSpeedA); // Send PWM signal to motor A
  digitalWrite(enB, motorSpeedB); // Send PWM signal to motor B
  // Set Motor A backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // Set Motor B backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(25);
}

void left(){
  motorSpeedA = pwm; 
  motorSpeedB = pwm; 
  digitalWrite(enA, motorSpeedA); // Send PWM signal to motor A
  digitalWrite(enB, motorSpeedB); // Send PWM signal to motor B
  // Set Motor A backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  // Set Motor B backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(25);
}

void forwardleft(){
  motorSpeedA = pwm; 
  motorSpeedB = pwm; 
  digitalWrite(enA, motorSpeedA); // Send PWM signal to motor A
  digitalWrite(enB, motorSpeedB); // Send PWM signal to motor B
  // Set Motor B forward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(25);
  // Set Motor B forward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // Set Motor A forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(10);
}

void forwardright(){
  motorSpeedA = pwm; 
  motorSpeedB = pwm; 
  digitalWrite(enA, motorSpeedA); // Send PWM signal to motor A
  digitalWrite(enB, motorSpeedB); // Send PWM signal to motor B
  // Set Motor A forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(25);
  // Set Motor A forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // Set Motor B forward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(10);
}

void backleft(){
  motorSpeedA = pwm; 
  motorSpeedB = pwm; 
  digitalWrite(enA, motorSpeedA); // Send PWM signal to motor A
  digitalWrite(enB, motorSpeedB); // Send PWM signal to motor B
  // Set Motor B backward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(25);
  // Set Motor B backward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // Set Motor A backward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(10);
}

void backright(){
  motorSpeedA = pwm; 
  motorSpeedB = pwm; 
  digitalWrite(enA, motorSpeedA); // Send PWM signal to motor A
  digitalWrite(enB, motorSpeedB); // Send PWM signal to motor B
  // Set Motor A backward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(25);
  // Set Motor A backward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // Set Motor B backward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(10);
}

void stop(){
  digitalWrite(enA, 0); // Send PWM signal to motor A
  digitalWrite(enB, 0); // Send PWM signal to motor B
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void turn(){
  //set backward
  digitalWrite(enA, 255); // Send PWM signal to motor A
  digitalWrite(enB, 255); // Send PWM signal to motor B
  // Set Motor A backward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // Set Motor B backward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(500);

  //set turn back
  /*digitalWrite(enA, 255); // Send PWM signal to motor A
  digitalWrite(enB, 255); // Send PWM signal to motor B
  // Set Motor A forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // Set Motor B backward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(20);*/
}




void loop() {
  Serial.print(length());
  Serial.print("cm\n");
  if (jarak>15){
    if(Serial.available()>0){
      data=Serial.read();
      Serial.print(data);
      Serial.print("\n");
      switch(data){
        case '0':
          pwm=0;
          break;
        case '1':
          pwm=26;
          break;
        case '2':
          pwm=51;
          break;
        case '3':
          pwm=77;
          break;
        case '4':
          pwm=102;
          break;
        case '5':          
          pwm=128;
          break;
        case '6':
          pwm=153;
          break;
        case '7':
          pwm=179;
          break;
        case '8':
          pwm=204;
          break;
        case '9':
          pwm=230;
          break;
        case 'q':
          pwm=255;
          break;
      }
 
      if(data=='F'){
        forward();
      }

      else if(data=='B'){
        backward();
      }

      else if(data=='R'){
        right();
      }

      else if(data=='L'){
        left();
      }

      else if(data=='G'){
        forwardleft();
      }

      else if(data=='I'){
        forwardright();
      }

      else if(data=='H'){
        backleft();
     }

      else if(data=='J'){
        backright();
      }
      stop();
    }
  }
  
  else{
    turn();
    stop();
  }
}
