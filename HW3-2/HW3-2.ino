// 定義引腳
const int buttonPin = 2; // D2 按鈕輸入
const int ledPin = 3;    // D3 LED 輸出

// 狀態變數
int mode = 0; // 0: 恆亮, 1: 慢閃, 2: 中速閃, 3: 快閃
int lastButtonState = HIGH; 
// 這裡假設按鈕仍使用 INPUT_PULLUP (按下 LOW 觸發)

// 計時變數
unsigned long previousMillis = 0;
// *** 注意：ledState 初始值也要反轉，LOW 代表亮 ***
bool ledState = LOW; 

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
  // *** 修正！初始狀態 (Mode 0) 恆亮：使用 LOW 來點亮 LED ***
  digitalWrite(ledPin, LOW); 
}

void loop() {
  // 1. 處理按鈕輸入 (邏輯不變)
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    if (reading == LOW) {
      mode++;
      if (mode > 3) {
        mode = 0; // 模式循環：0 -> 1 -> 2 -> 3 -> 0
      }
      
      // 切換模式時，將 LED 狀態重置為 LOW (即亮起狀態，為恆亮或下一次閃爍做準備)
      ledState = LOW; 
    }
    lastButtonState = reading;
  }

  // 2. 根據當前模式控制 LED 輸出
  unsigned long currentMillis = millis(); 

  switch (mode) {
    case 0: // 恆亮
      // *** 修正！恆亮時輸出 LOW ***
      digitalWrite(ledPin, LOW);
      break;

    case 1: // 慢閃
    case 2: // 中速閃
    case 3: // 快閃
      
      long interval = 0;
      if (mode == 1) interval = 500;
      else if (mode == 2) interval = 200;
      else if (mode == 3) interval = 50;

      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis; 
        
        // 切換 LED 狀態 (LOW<->HIGH)
        ledState = !ledState;
        // *** 修正！輸出 ledState (LOW 是亮, HIGH 是滅) ***
        digitalWrite(ledPin, ledState);
      }
      break;
  }
}