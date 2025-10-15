// ==== Pin 腳定義 ====
const int BUTTON_PIN = 2;
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;
const bool COMMON_ANODE = true;

// ==== 心情分數 ====
float moodPoints = 100;           // 實際心情分數
float targetMoodPoints = 100;     // 目標分數
const float MAX_POINTS = 100;
const float MIN_POINTS = 0;

// 按鈕參數
unsigned long lastPressTime = 0;
const unsigned long NO_PRESS_PERIOD = 5000; // 久不碰後開始回復
const float MOOD_STEP = 0.5;               
const int PRESS_DECREASE = 5;              

// 呼吸變數
float breathValue = 0;
unsigned long lastBreathUpdate = 0;
const float MIN_BREATH_STEP = 0.02; // 平靜呼吸
const float MAX_BREATH_STEP = 0.12; // 生氣心跳

// ==== SETUP ====
void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  setColor(0,0,0);
  lastPressTime = millis();
}

// ==== LOOP ====
void loop() {
  handleButton();
  updateMood();
  updateMoodLED();
}

// ==== 按鈕偵測 ====
void handleButton() {
  int reading = digitalRead(BUTTON_PIN);
  if (reading == LOW) {
    if (millis() - lastPressTime > 50) { // 防抖
      targetMoodPoints -= PRESS_DECREASE;
      if (targetMoodPoints < MIN_POINTS) targetMoodPoints = MIN_POINTS;
      lastPressTime = millis();
    }
  }
}

// ==== 心情分數平滑更新 ====
void updateMood() {
  unsigned long now = millis();
  // 久不碰 → 目標分數慢慢回升
  if ((now - lastPressTime) > NO_PRESS_PERIOD) {
    targetMoodPoints += MOOD_STEP;
    if (targetMoodPoints > MAX_POINTS) targetMoodPoints = MAX_POINTS;
  }

  // moodPoints 平滑追蹤 targetMoodPoints (線性插值)
  moodPoints = moodPoints + (targetMoodPoints - moodPoints) * 0.02;
}

// ==== LED 更新 (平滑顏色 + 呼吸) ====
void updateMoodLED() {
  float r,g,b;
  // 使用連續中間過渡色
  if (moodPoints <= 25) { // 紅 → 紫
    float t = moodPoints / 25.0;
    r = 255;
    g = 0;
    b = t * 255;
  } else if (moodPoints <= 50) { // 紫 → 綠
    float t = (moodPoints - 25) / 25.0;
    r = 255*(1.0 - t);
    g = t * 255;
    b = 255*(1.0 - t);
  } else if (moodPoints <= 75) { // 綠 → 青
    float t = (moodPoints - 50) / 25.0;
    r = 0;
    g = 255;
    b = t * 255;
  } else { // 青 → 深藍
    float t = (moodPoints - 75) / 25.0;
    r = 0;
    g = 255*(1.0 - t);
    b = 255 - t * 127; // 255 → 128
  }

  // 呼吸速度: 心情越低 → 呼吸越快
  float step = MIN_BREATH_STEP + (1.0 - moodPoints/100.0) * (MAX_BREATH_STEP - MIN_BREATH_STEP);
  float amplitude = 0.2 + (1.0 - moodPoints/100.0) * 0.6; // 呼吸幅度

  breathingEffect(step,r,g,b,10);
}

// ==== 呼吸效果 ====
void breathingEffect(float step,float baseR,float baseG,float baseB,int updateInterval){
  if (millis() - lastBreathUpdate >= updateInterval) {
    float factor = (sin(breathValue)+1.0)/2.0*0.8 + 0.2; // 亮度 20%~100%
    int r = (int)(baseR * factor);
    int g = (int)(baseG * factor);
    int b = (int)(baseB * factor);
    setColor(r,g,b);
    breathValue += step;
    if (breathValue > 2*PI) breathValue -= 2*PI;
    lastBreathUpdate = millis();
  }
}

// ==== 設定 RGB 顏色 ====
void setColor(int r,int g,int b){
  if (COMMON_ANODE){
    analogWrite(RED_PIN,255-r);
    analogWrite(GREEN_PIN,255-g);
    analogWrite(BLUE_PIN,255-b);
  } else {
    analogWrite(RED_PIN,r);
    analogWrite(GREEN_PIN,g);
    analogWrite(BLUE_PIN,b);
  }
}
