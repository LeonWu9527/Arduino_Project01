# 電路接線說明

## LCD1602 (I2C 模組)
- **SDA (資料線)：** 接 Arduino 的 `A4` 腳位。
- **SCL (時鐘線)：** 接 Arduino 的 `A5` 腳位。
- **VCC：** 接 Arduino 的 `5V`。
- **GND：** 接 Arduino 的 `GND`。

## 超音波感應器 (HC-SR04)
- **Trig 腳：** 接 Arduino 的數位腳位 `10`。
- **Echo 腳：** 接 Arduino 的數位腳位 `11`。
- **VCC：** 接 Arduino 的 `5V`。
- **GND：** 接 Arduino 的 `GND`。

## 步進馬達 (ULN2003 驅動模組)
- **IN1-IN4：** 分別接 Arduino 的數位腳位 `2`, `3`, `4`, `5`。
- **VCC：** 接 Arduino 的 `5V`。
- **GND：** 接 Arduino 的 `GND`。
- **步進馬達輸出：** 按模組上的標示接入步進馬達。

## LED燈
- **紅燈 (LED)：**
  - 正極接 Arduino 的數位腳位 `9`。
  - 負極接 220Ω 電阻，再接 Arduino 的 `GND`。
- **綠燈 (LED)：**
  - 正極接 Arduino 的數位腳位 `8`。
  - 負極接 220Ω 電阻，再接 Arduino 的 `GND`。
- **藍燈 (LED)：**
  - 正極接 Arduino 的數位腳位 `12`。
  - 負極接 220Ω 電阻，再接 Arduino 的 `GND`。

## 蜂鳴器
- **正極 (長腳)：** 接 Arduino 的數位腳位 `7`。
- **負極 (短腳)：** 接 Arduino 的 `GND`。

## 按鈕
- **一端：** 接 Arduino 的數位腳位 `6`。
- **另一端：** 接 Arduino 的 `GND`。
- **注意：** 在按鈕與數位腳位之間加一個 10kΩ 的上拉電阻，將按鈕另一端接到 `5V`。

---

完成接線後，請將程式碼上傳至 Arduino，並開始測試互動效果！