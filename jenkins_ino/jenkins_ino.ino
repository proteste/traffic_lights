int red = 13;
int yellow = 12;
int green = 11;

int switchPin = 10;

int inByte;
long lastTx = 0;

void setup() {

  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  pinMode(switchPin, INPUT);
  digitalWrite(switchPin, HIGH);  
}


void loop() {
  
  if (digitalRead(switchPin) == HIGH){

    // check serial buffer
    if (Serial.available() > 0){
      // read serial byte
      inByte = Serial.read();
      // print serial byte
      Serial.println(inByte);
      lastTx = millis();
  
      digitalWrite(red, LOW);
      digitalWrite(yellow, LOW);
      digitalWrite(green, LOW);
      
      switch(inByte){
        // if serial value received is "49", blink yellow light
        case 49:
          blink(red);
          digitalWrite(red, HIGH);
          Serial.println("red on");
          break;
        case 50:
          blink(yellow);
          blink(yellow);
          digitalWrite(yellow, HIGH);
          Serial.println("yellow on");
          break;
        case 51:
          blink(green);
          digitalWrite(green, HIGH);
          Serial.println("green on");
          break;
        case 52:
          blink(red);
          blink(red);
          blink(red);
          digitalWrite(red, HIGH);
          Serial.println("server error");
          break;
        case 53:
          blink_cycle();
          blink_cycle();
          blink_cycle();
          Serial.println("building");
          break;
      }
      Serial.println(inByte);
    }
    else {
      if ((millis() - lastTx) > 30000) {
        alert();
      }
    }
  }    
  else {
    Serial.println("lights off");
  }
  
  delay(500);
}

void blink_cycle(){
  digitalWrite(red, LOW); 
  digitalWrite(yellow, LOW);
  digitalWrite(green, HIGH);
  delay(1000);
  digitalWrite(red, LOW);
  digitalWrite(yellow, HIGH);
  digitalWrite(green, LOW);
  delay(1000);
  digitalWrite(red, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
  delay(1000);
  digitalWrite(red, LOW);
}

void blink(int light){
  digitalWrite(light, HIGH);
  delay(1000);
  digitalWrite(light, LOW);
  delay(1000);
}

void alert() {
  digitalWrite(red, HIGH); 
  digitalWrite(yellow, HIGH);
  digitalWrite(green, HIGH);
  delay(1000);
  digitalWrite(red, LOW); 
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
  delay(1000);
}

