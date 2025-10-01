/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/DigitalReadSerial/
*/

// digital pin 2 has a pushbutton attached to it. Give it a name:
const int buttonPin = 2;   // 按鈕接腳
const int RledPin = 3;
const int GledPin = 4;
const int BledPin = 5; 

int ledcolor = 0;
int buttonState = 0;

// the setup routine runs once when you press reset:
void setup() {
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) { 
    ledcolor = ledcolor + 1; 
    delay(100); 

    if (ledcolor == 0) { 
      digitalWrite(RledPin, HIGH);
      digitalWrite(GledPin, HIGH);
      digitalWrite(BledPin, HIGH);
    }
    else if (ledcolor == 1) { 
      digitalWrite(RledPin, LOW);
      digitalWrite(GledPin, HIGH);
      digitalWrite(BledPin, HIGH);
    }
    else if (ledcolor == 2) { 
      digitalWrite(RledPin, HIGH);
      digitalWrite(GledPin, LOW);
      digitalWrite(BledPin, HIGH);
    }
    else if (ledcolor == 3) { 
      digitalWrite(RledPin, HIGH);
      digitalWrite(GledPin, HIGH);
      digitalWrite(BledPin, LOW);
    }
    else if (ledcolor == 4) { 
      digitalWrite(RledPin, LOW);
      digitalWrite(GledPin, LOW);
      digitalWrite(BledPin, HIGH);
    }
    else if (ledcolor == 5) { 
      digitalWrite(RledPin, LOW);
      digitalWrite(GledPin, HIGH);
      digitalWrite(BledPin, LOW);
    }
    else if (ledcolor == 6) { 
      digitalWrite(RledPin, HIGH);
      digitalWrite(GledPin, LOW);
      digitalWrite(BledPin, LOW);
    }
    else if (ledcolor == 7) { 
      digitalWrite(RledPin, LOW);
      digitalWrite(GledPin, LOW);
      digitalWrite(BledPin, LOW);
    }
    else if (ledcolor == 8) { 
      ledcolor = 0;
    }
  } // 這是 if(buttonState == HIGH) 的結尾
}   // 這是 void loop() 的結尾
