#define R 9
#define G 10
#define B 11
#define BUTTON 2

int mode = 1;                 // 模式：1紅閃、2藍閃、3綠閃、4亂閃
bool powerOn = true;          // 是否開燈
bool ledState = false;        // 閃爍狀態
unsigned long lastBlinkTime = 0;
unsigned long lastButtonTime = 0;
bool lastButtonState = HIGH;
bool buttonHeld = false;

void setup() {
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  handleButton();
  if (powerOn) runMode();
  else turnOff();
}

void handleButton() {
  int reading = digitalRead(BUTTON);
  unsigned long now = millis();

  // 按下瞬間
  if (lastButtonState == HIGH && reading == LOW) {
    lastButtonTime = now;
    buttonHeld = false;
  }

  // 長按（超過1秒）
  if (reading == LOW && (now - lastButtonTime > 1000) && !buttonHeld) {
    powerOn = !powerOn;
    buttonHeld = true;
    Serial.println(powerOn ? "💡 Power ON" : "💤 Power OFF");
    delay(300); // 防止重複判定
  }

  // 放開時才切換模式（避免長按也切）
  if (lastButtonState == LOW && reading == HIGH && !buttonHeld) {
    mode++;
    if (mode > 4) mode = 1;
    Serial.print("Mode switched to ");
    Serial.println(mode);
  }

  lastButtonState = reading;
}

void runMode() {
  unsigned long now = millis();

  switch (mode) {
    case 1: blinkColor(now, 255, 0, 0, 200); break;  // 紅閃
    case 2: blinkColor(now, 0, 0, 255, 200); break;  // 藍閃
    case 3: blinkColor(now, 0, 255, 0, 200); break;  // 綠閃
    case 4: randomFlash(now, 150); break;            // 亂閃
  }
}

void blinkColor(unsigned long now, int r, int g, int b, int interval) {
  if (now - lastBlinkTime > interval) {
    ledState = !ledState;
    lastBlinkTime = now;
    if (ledState) {
      analogWrite(R, 255 - r);
      analogWrite(G, 255 - g);
      analogWrite(B, 255 - b);
    } else {
      analogWrite(R, 255);
      analogWrite(G, 255);
      analogWrite(B, 255);
    }
  }
}

void randomFlash(unsigned long now, int interval) {
  if (now - lastBlinkTime > interval) {
    lastBlinkTime = now;
    analogWrite(R, 255 - random(0, 256));
    analogWrite(G, 255 - random(0, 256));
    analogWrite(B, 255 - random(0, 256));
  }
}

void turnOff() {
  analogWrite(R, 255);
  analogWrite(G, 255);
  analogWrite(B, 255);
}
