void setup() {
  // 設置初始化代碼，只運行一次
  Serial.begin(9600);  // 初始化串口通信，波特率為9600
  pinMode(16, INPUT_PULLUP);  // 設置引腳16為輸入模式，啟用內部上拉電阻
  // PULLUP（上拉）是指在Arduino中使用內部上拉電阻的一種輸入模式
  pinMode(4, OUTPUT);  // 設置引腳4為輸出模式
  digitalWrite(4, LOW);  // 初始化引腳4為低電平
}

bool p16 = digitalRead(16);  // 讀取引腳16的初始狀態
// bool p16 = digitalRead(16); 讀取引腳16的當前狀態
bool led_state = HIGH;  // 設置LED初始狀態為高電平（開啟）

void loop() {
  // 主循環代碼，重複執行
  p16 = digitalRead(16);  // 讀取引腳16的當前狀態
  Serial.println(p16);  // 通過串口輸出引腳16的狀態

  if (p16 == 0) {  // 如果引腳16為低電平（按鈕被按下）
    digitalWrite(4, HIGH);  // 將引腳4設置為高電平
    led_state = !led_state;  // 切換LED狀態
  }

  digitalWrite(4, led_state);  // 根據led_state設置引腳4的狀態
  delay(100);  // 延遲100毫秒
}
