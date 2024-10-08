

# sketch_oct8a解析

這個Arduino程式實現了一個簡單的按鈕控制LED的功能。每次按下按鈕，LED的狀態就會切換一次（開啟或關閉）。

## 程式結構

程式主要分為三個部分：
1. 全局變數宣告
2. `setup()` 函數
3. `loop()` 函數

## 全局變數

```cpp
bool p16 = digitalRead(16);  // 讀取引腳16的初始狀態
bool led_state = HIGH;  // 設置LED初始狀態為高電平（開啟）
```

- `p16`：用於存儲引腳16（按鈕）的狀態
- `led_state`：用於記錄LED的當前狀態，初始設為高電平（開啟）

## setup() 函數

```cpp
void setup() {
  Serial.begin(9600);  // 初始化串口通信，波特率為9600
  pinMode(16, INPUT_PULLUP);  // 設置引腳16為輸入模式，啟用內部上拉電阻
  pinMode(4, OUTPUT);  // 設置引腳4為輸出模式
  digitalWrite(4, LOW);  // 初始化引腳4為低電平
}
```

`setup()` 函數只在Arduino啟動時執行一次，用於初始化設置：

- 初始化串口通信，波特率為9600
- 設置引腳16為輸入模式，並啟用內部上拉電阻（用於連接按鈕）
- 設置引腳4為輸出模式（用於控制LED）
- 初始化引腳4為低電平，確保LED最初是關閉的

## loop() 函數

```cpp
void loop() {
  p16 = digitalRead(16);  // 讀取引腳16的當前狀態
  Serial.println(p16);  // 通過串口輸出引腳16的狀態

  if (p16 == 0) {  // 如果引腳16為低電平（按鈕被按下）
    digitalWrite(4, HIGH);  // 將引腳4設置為高電平
    led_state = !led_state;  // 切換LED狀態
  }

  digitalWrite(4, led_state);  // 根據led_state設置引腳4的狀態
  delay(100);  // 延遲100毫秒
}
```

`loop()` 函數會不斷重複執行，實現主要功能：

1. 讀取引腳16（按鈕）的狀態
2. 通過串口輸出按鈕狀態（用於調試）
3. 如果檢測到按鈕被按下（引腳16為低電平）：
   - 將引腳4（LED）設置為高電平
   - 切換 `led_state` 的狀態
4. 根據 `led_state` 設置LED的狀態
5. 延遲100毫秒，以防止按鈕彈跳和降低CPU負載

## 程式邏輯說明

- 使用 `INPUT_PULLUP` 模式為按鈕提供內部上拉電阻，簡化了外部電路設計
- 當按鈕未按下時，引腳16讀取為高電平（1）；按下時為低電平（0）
- 每次檢測到按鈕按下，就會切換LED的狀態
- 使用 `led_state` 變數來記錄和控制LED的開關狀態
- 通過串口輸出按鈕狀態，方便監控和調試





# sketch_oct8b 程式解析

這個Arduino程式實現了一個改進版的按鈕控制LED功能，增加了防止按鈕重複觸發的機制。

## 程式結構

程式主要分為三個部分：
1. 全局變數宣告
2. `setup()` 函數
3. `loop()` 函數

## 全局變數

```cpp
bool p16 = digitalRead(16);  // 讀取引腳16的初始狀態
bool led_state = HIGH;  // 設置LED初始狀態為高電平（開啟）
bool flag = LOW;  // 設置標誌位，用於防止按鈕重複觸發
```

- `p16`：用於存儲引腳16（按鈕）的狀態
- `led_state`：用於記錄LED的當前狀態，初始設為高電平（開啟）
- `flag`：新增的標誌位，用於實現防彈跳機制

## setup() 函數

```cpp
void setup() {
  Serial.begin(9600);  // 初始化串口通信，波特率為9600
  pinMode(16, INPUT_PULLUP);  // 設置引腳16為輸入模式，啟用內部上拉電阻
  pinMode(4, OUTPUT);  // 設置引腳4為輸出模式
  digitalWrite(4, LOW);  // 初始化引腳4為低電平
}
```

`setup()` 函數只在Arduino啟動時執行一次，用於初始化設置：

- 初始化串口通信，波特率為9600
- 設置引腳16為輸入模式，並啟用內部上拉電阻（用於連接按鈕）
- 設置引腳4為輸出模式（用於控制LED）
- 初始化引腳4為低電平，確保LED最初是關閉的

## loop() 函數

```cpp
void loop() {
  p16 = digitalRead(16);  // 讀取引腳16的當前狀態
  Serial.println(p16);  // 通過串口輸出引腳16的狀態

  if (p16 == 0 && flag == LOW) {  // 如果引腳16為低電平（按鈕被按下）且標誌位為LOW
    digitalWrite(4, HIGH);  // 將引腳4設置為高電平
    led_state = !led_state;  // 切換LED狀態
    flag = HIGH;  // 設置標誌位為HIGH，防止重複觸發
  }
  else if (p16 == 1 && flag == HIGH) {  // 如果按鈕釋放且標誌位為HIGH
    flag = LOW;  // 重置標誌位，為下一次按鈕按下做準備
  }

  digitalWrite(4, led_state);  // 根據led_state設置引腳4的狀態
  delay(100);  // 延遲100毫秒
}
```

`loop()` 函數會不斷重複執行，實現主要功能：

1. 讀取引腳16（按鈕）的狀態
2. 通過串口輸出按鈕狀態（用於調試）
3. 使用改進的按鈕檢測邏輯：
   - 當按鈕被按下且標誌位為LOW時，切換LED狀態並設置標誌位為HIGH
   - 當按鈕釋放且標誌位為HIGH時，重置標誌位為LOW
4. 根據 `led_state` 設置LED的狀態
5. 延遲100毫秒，以進一步減少按鈕彈跳的影響

## 程式邏輯說明

### 防彈跳機制
- 引入 `flag` 變數實現簡單的軟件防彈跳
- 確保每次按鈕按下只觸發一次動作，避免因按鈕彈跳導致的多次觸發

### 狀態切換邏輯
- 只有在按鈕從未按下狀態變為按下狀態時才切換LED
- 按鈕釋放時重置標誌位，為下一次按下做準備

### 輸入輸出處理
- 使用 `INPUT_PULLUP` 模式簡化按鈕電路設計
- 通過串口輸出按鈕狀態，方便監控和調試






# sketch_oct8c 程式分析

這個程式實現了使用一個按鈕控制多個LED的功能，包含防彈跳機制。

## 硬體設置

- 使用引腳16作為輸入，連接到一個按鈕
- 使用引腳4、5和0作為輸出，分別連接到三個LED

## 程式結構

程式主要分為兩個部分：`setup()` 函數和 `loop()` 函數。

### setup() 函數

```cpp
void setup() {
  Serial.begin(9600);
  pinMode(16, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(0, OUTPUT);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(0, LOW);
}
```

這個函數負責初始化：
- 設置串口通信
- 配置引腳模式
- 初始化LED狀態

### 全局變數

```cpp
bool p16 = digitalRead(16);
bool led_state = HIGH;
bool flag = LOW;
```

- `p16`: 存儲按鈕（引腳16）的狀態
- `led_state`: 記錄LED的當前狀態
- `flag`: 用於實現防彈跳機制

### loop() 函數

```cpp
void loop() {
  p16 = digitalRead(16);
  Serial.println(p16);

  if (p16 == 0 && flag == LOW) {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(0, HIGH);
    led_state = !led_state;
    flag = HIGH;
  }
  else if (p16 == 1 && flag == HIGH) {
    flag = LOW;
  }

  digitalWrite(4, led_state);
  digitalWrite(5, led_state);
  digitalWrite(0, led_state);
  delay(100);
}
```

這個函數實現主要邏輯：
1. 讀取並輸出按鈕狀態
2. 檢測按鈕按下事件並處理
3. 更新所有LED的狀態

## 程式邏輯說明

1. **按鈕讀取**：
   - 持續讀取引腳16的狀態，即按鈕的狀態

2. **防彈跳機制**：
   - 使用 `flag` 變數來防止一次按鈕按下被誤認為多次
   - 只有在按鈕從未按下變為按下狀態時才觸發動作

3. **LED控制**：
   - 當檢測到有效的按鈕按下時，切換 `led_state`
   - 根據 `led_state` 同時控制三個LED（引腳4、5和0）

4. **狀態更新**：
   - 每次循環結束時，根據 `led_state` 更新所有LED的狀態
   - 使用100毫秒的延遲來減少CPU負載和按鈕彈跳的影響




# sketch_oct8d 程式分析
## 硬體設置

- 使用引腳 16 作為第一個按鈕的輸入
- 使用引腳 2 作為第二個按鈕的輸入
- 使用引腳 4、5 和 0 作為 LED 輸出

## 程式結構

程式主要分為三個部分：`setup()` 函數、`loop()` 函數和 `changeLEDState()` 函數。

### setup() 函數

```cpp
void setup() {
  Serial.begin(9600);
  pinMode(16, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(0, OUTPUT);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(0, LOW);
}
```

這個函數負責初始化：
- 設置串口通信
- 配置按鈕引腳為輸入模式（使用內部上拉電阻）
- 配置 LED 引腳為輸出模式
- 初始化所有 LED 為關閉狀態

### 全局變數

```cpp
bool p16 = digitalRead(16);
bool flag = LOW;
int led_sequence = 0;
```

- `p16`: 存儲第一個按鈕的狀態
- `flag`: 用於實現第一個按鈕的防彈跳機制
- `led_sequence`: 記錄當前 LED 顯示序列

### loop() 函數

```cpp
void loop() {
  p16 = digitalRead(16);
  bool button2State = digitalRead(2);
  
  Serial.println(p16);

  if (button2State == LOW) {
    changeLEDState();
    delay(500);
  }
  else if (p16 == 0 && flag == LOW) {
    changeLEDState();
    flag = HIGH;
  }
  else if (p16 == 1 && flag == HIGH) {
    flag = LOW;
  }

  delay(100);
}
```

這個函數實現主要邏輯：
1. 讀取兩個按鈕的狀態
2. 如果第二個按鈕被按下，持續改變 LED 狀態
3. 如果第一個按鈕被按下，單次改變 LED 狀態
4. 實現第一個按鈕的防彈跳機制

### changeLEDState() 函數

```cpp
void changeLEDState() {
  // LED 狀態切換邏輯
}
```

這個函數負責改變 LED 的顯示狀態：
- 根據 `led_sequence` 設置不同的 LED 亮滅組合
- 每次調用後增加 `led_sequence`，實現循環顯示效果

## 程式邏輯說明

1. **雙按鈕控制**：
   - 第一個按鈕（引腳 16）：每次按下觸發一次 LED 狀態變化
   - 第二個按鈕（引腳 2）：按住時持續觸發 LED 狀態變化

2. **防彈跳機制**：
   - 使用 `flag` 變數來防止第一個按鈕的重複觸發

3. **LED 控制**：
   - 使用 `led_sequence` 變數來追蹤當前 LED 顯示狀態
   - 共有 8 種不同的 LED 顯示組合

4. **自動循環**：
   - 當第二個按鈕被按住時，LED 狀態每 500 毫秒變化一次

5. **延遲處理**：
   - 主循環中有 100 毫秒的延遲，用於減少 CPU 負載和按鈕彈跳影響
