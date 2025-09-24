// RGB 腳位
int redPin = 3;
int greenPin = 4;
int bluePin = 5;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // 隨機亮度 (0-255)
  int r = random(0, 256);
  int g = random(0, 256);
  int b = random(0, 256);

  // 設定 LED 亮度
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);

  // 隨機閃爍速度
  delay(random(100, 200));
}