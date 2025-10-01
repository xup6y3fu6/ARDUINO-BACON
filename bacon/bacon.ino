// LED 腳位
const int RledPin = 3;
const int GledPin = 5;
const int BledPin = 4;
const int buttonPin = 2;

int ledcolor = 0;           // 顏色計數器
bool ledOn = true;          // LED 開關
bool buttonPressed = false;

unsigned long lastPressTime = 0;
const unsigned long doubleClickDelay = 400;  // 雙擊判定間隔 (ms)

String colors[] = {"Red","Green","Blue","Yellow","Purple","Cyan","White"};
int states[][3] = {
  {0,1,1}, // Red
  {1,0,1}, // Green
  {1,1,0}, // Blue
  {0,0,1}, // Yellow
  {0,1,0}, // Purple
  {1,0,0}, // Cyan
  {0,0,0}  // White
};

void setup() {
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH && !buttonPressed) {
    unsigned long currentTime = millis();

    if (currentTime - lastPressTime < doubleClickDelay) {
      // 雙擊 → 開/關 LED
      ledOn = !ledOn;
      Serial.println("LED toggled!");
      delay(50);  // 去抖
    } else {
      // 單擊 → 切換顏色
      ledcolor = (ledcolor + 1) % 7;
      Serial.print("Color switched to: ");
      Serial.println(colors[ledcolor]);
      delay(50);  // 去抖
    }

    lastPressTime = currentTime;
    buttonPressed = true;
  }

  if (buttonState == LOW && buttonPressed) {
    buttonPressed = false;
  }

  // 根據 ledOn 與顏色設定 LED
  if (ledOn) {
    digitalWrite(RledPin, states[ledcolor][0]);
    digitalWrite(GledPin, states[ledcolor][1]);
    digitalWrite(BledPin, states[ledcolor][2]);
  } else {
    // LED 關閉
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }
}
