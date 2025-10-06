

int R=3, G=4, B=5;
int buttonPin=2;

int mode=1;
bool lastButtonState=HIGH;
unsigned long lastDebounceTime=0;
unsigned long debounceDelay=200;

// LED 當前亮度
int currentR=0, currentG=0, currentB=0;

// SOS 狀態
unsigned long sosDurations[9] = {200,200,200,800,800,800,200,200,200};
bool sosOn[9] = {true,false,true,false,true,false,true,false,true};
int sosStep = 0;
unsigned long sosTimer = 0;

// 鬼計時
unsigned long madnessStartTime=0;
unsigned long madnessDuration=8000; // 鬼總時間
bool fading=false;

// Fade記錄
int fadeVal=0;
bool fadeUp=true;
unsigned long fadeTimer=0;

void setup(){
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(buttonPin,INPUT_PULLUP);
  madnessStartTime = millis();
  sosTimer = millis();
}

void loop(){
  checkButton();
  switch(mode){
    case 1: heartbeat(); break;
    case 2: ghostFlicker(); break;
    case 3: sosBlink(); break;
    case 4: madness(); break;
    case 5: fadeIn(); break;
  }
}

void checkButton(){
  bool reading = digitalRead(buttonPin);
  if(reading==LOW && lastButtonState==HIGH && (millis()-lastDebounceTime)>debounceDelay){
    mode++;
    if(mode>5) mode=1;
    lastDebounceTime = millis();
    fading=false;
    fadeVal=0;
    fadeUp=true;
    sosStep=0;
    sosTimer=millis();
    madnessStartTime=millis();
  }
  lastButtonState=reading;
}

// 1️⃣ 燈塔
void heartbeat(){
  static int i=50;
  static int delta=5;
  i+=delta;
  if(i>=255 || i<=50) delta=-delta;
  setColor(i,0,0);
  delay(20);
}

// 2️⃣ 靈異
void ghostFlicker(){
  int brightness=random(30,255);
  setColor(brightness,brightness,brightness);
  delay(random(30,100));
}

// 3️⃣ SOS
void sosBlink(){
  if(millis() - sosTimer >= sosDurations[sosStep]){
    if(sosOn[sosStep]) setColor(0,0,255); // 紅光亮
    else setColor(255,0,255);             // 完全暗
    sosStep++;
    if(sosStep >= 9) sosStep = 0;
    sosTimer = millis();
  }
}

// 3️⃣ 鬼
void madness() {
  int r, g, b;

  int type = random(0, 5); // 五種隨機效果
  switch(type) {
    case 0: // 紅色刺眼
      r = 0; g = 0; b = 255; 
      break;
    case 1: // 白光
      r = 0; g = 255; b = 255; 
      break;
    case 2: // 暗紅
      r = 0; g = 0; b = random(50, 150);
      break;
    case 3: // 短暫熄滅
      r = 255; g = 0; b = 255;
      break;
    case 4: // 隨機閃爍
      r = random(0,2)*0; 
      g = random(0,2)*255; 
      b = random(0,2)*255; 
      break;
  }

  setColor(r, g, b);

  // 閃爍間隔隨機 20~200ms
  delay(random(20, 200));
}


// 5️⃣ fade
void fadeIn() {
  if (millis() - fadeTimer >= 50) {
    fadeTimer = millis();

    if (fadeVal < 255) {
      fadeVal += 5;
      if (fadeVal > 255) fadeVal = 255;

      // 紅光亮到無光
      setColor(fadeVal, 0, 255); // R 從0→255，B固定255
    }
  }
}





// 設定 LED 顏色
void setColor(int r,int g,int b){
  analogWrite(R,r);
  analogWrite(G,g);
  analogWrite(B,b);
  currentR=r;
  currentG=g;
  currentB=b;
}
