void setup() {
  // 設置初始化代碼，只運行一次
  Serial.begin(9600);  // 初始化串口通信，波特率為9600
  pinMode(16, INPUT_PULLUP);  // 設置引腳16為輸入模式，啟用內部上拉電阻
  // PULLUP（上拉）是指在Arduino中使用內部上拉電阻的一種輸入模式
  pinMode(4, OUTPUT);  // 設置引腳4為輸出模式
  pinMode(5, OUTPUT);  // 設置引腳5為輸出模式
  pinMode(0, OUTPUT);
  digitalWrite(4, LOW);  // 初始化引腳4為低電平
  digitalWrite(5, LOW);  // 初始化引腳5為低電平
  digitalWrite(0, LOW);
}

bool p16 = digitalRead(16);  // 讀取引腳16的初始狀態
// bool p16 = digitalRead(16); 讀取引腳16的當前狀態
bool led_state = HIGH;  // 設置LED初始狀態為高電平（開啟）
bool flag = LOW;  // 設置標誌位，用於防止按鈕重複觸發

void loop() {
  // 主循環代碼，重複執行
  p16 = digitalRead(16);  // 讀取引腳16的當前狀態
  Serial.println(p16);  // 通過串口輸出引腳16的狀態

  if (p16 == 0 && flag == LOW) {  // 如果引腳16為低電平（按鈕被按下）且標誌位為LOW
    digitalWrite(4, HIGH);  // 將引腳4設置為高電平
    digitalWrite(5, HIGH);
    digitalWrite(0, HIGH);  // 將引腳5設置為高電平
    led_state = !led_state;  // 切換LED狀態
    flag = HIGH;  // 設置標誌位為HIGH，防止重複觸發
  }
  else if (p16 == 1 && flag == HIGH) {  // 如果按鈕釋放且標誌位為HIGH
    flag = LOW;  // 重置標誌位，為下一次按鈕按下做準備
  }

  digitalWrite(4, led_state);  // 根據led_state設置引腳4的狀態
  digitalWrite(5, led_state);  // 根據led_state設置引腳5的狀態
  digitalWrite(0, led_state);
  delay(100);  // 延遲100毫秒
}
