// 設置第二個按鈕的引腳
const int button2Pin = 14;  // 假設第二個按鈕連接到引腳14

void setup() {
  // 設置初始化代碼，只運行一次
  Serial.begin(9600);  // 初始化串口通信，波特率為9600
  pinMode(16, INPUT_PULLUP);  // 設置引腳16為輸入模式，啟用內部上拉電阻
  pinMode(2, INPUT_PULLUP);  // 設置第二個按鈕引腳為輸入模式，啟用內部上拉電阻
  pinMode(4, OUTPUT);  // 設置引腳4為輸出模式
  pinMode(5, OUTPUT);  // 設置引腳5為輸出模式
  pinMode(0, OUTPUT);  // 設置引腳0為輸出模式
  digitalWrite(4, LOW);  // 初始化引腳4為低電平
  digitalWrite(5, LOW);  // 初始化引腳5為低電平
  digitalWrite(0, LOW);  // 初始化引腳0為低電平
}

// 讀取引腳16的初始狀態
bool p16 = digitalRead(16);
// 設置標誌位，用於防止按鈕重複觸發
bool flag = LOW;
// 設置LED序列計數器
int led_sequence = 0;

void loop() {
  // 主循環代碼，重複執行
  // 讀取引腳16的當前狀態
  p16 = digitalRead(16);
  // 讀取第二個按鈕的狀態
  bool button2State = digitalRead(2);
  
  // 通過串口輸出引腳16的狀態
  Serial.println(p16);

  // 如果第二個按鈕被按下，自動循環LED狀態
  if (button2State == LOW) {
    changeLEDState();
    delay(500);  // 延遲500毫秒，控制自動循環的速度
  }
  // 如果引腳16為低電平（按鈕被按下）且標誌位為LOW
  else if (p16 == 0 && flag == LOW) {
    changeLEDState();
    // 設置標誌位為HIGH，防止重複觸發
    flag = HIGH;
  }
  // 如果按鈕釋放且標誌位為HIGH
  else if (p16 == 1 && flag == HIGH) {
    // 重置標誌位，為下一次按鈕按下做準備
    flag = LOW;
  }

  // 延遲100毫秒
  delay(100);
}

// 改變LED狀態的函數
void changeLEDState() {
  // 重置所有LED
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(0, LOW);
  
  // 根據序列點亮LED
  if (led_sequence == 0) {
    digitalWrite(4, HIGH);  // 點亮引腳4的LED
  } else if (led_sequence == 1) {
    digitalWrite(5, HIGH);  // 點亮引腳5的LED
  } else if (led_sequence == 2) {
    digitalWrite(0, HIGH);  // 點亮引腳0的LED
    digitalWrite(5, HIGH);  // 同時點亮引腳5的LED
  } else if (led_sequence == 3) {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(0, LOW);
  } else if (led_sequence == 4) {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(0, HIGH);
  } else if (led_sequence == 5) {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(0, LOW);
  } else if (led_sequence == 6) {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(0, HIGH);
  } else {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(0, LOW);
  }
  
  // 增加序列計數
  led_sequence++;
  // 如果序列計數超過7，重置為0
  if (led_sequence > 7) {
    led_sequence = 0;
  }
}
