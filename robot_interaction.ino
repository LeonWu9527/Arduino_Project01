#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>

//初始化 LCD1602 (I2C 地址為 0x27，16x2 顯示)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// 定義步進馬達參數
const int stepsPerRevolution = 200; // 每圈步數
Stepper stepper(stepsPerRevolution, 2, 3, 4, 5);

// 定義硬體腳位
const int trigPin = 10;
const int echoPin = 11;
const int redLedPin = 9;
const int greenLedPin = 8;
const int blueLedPin = 12; // 新增藍色 LED 腳位
const int buzzerPin = 7;
const int buttonPin = 6;

// 距離閾值
const int dangerDistance = 20; // 過近的距離 (cm)
const int safeDistance = 50;  // 安全距離 (cm)

void setup() {
  // 初始化硬體
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  // 初始化 LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello! I'm Bot!");

  // 初始化步進馬達
  stepper.setSpeed(60); // 設定馬達速度 (RPM)

  Serial.begin(9600);
}

void loop() {
  // 讀取距離
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // 讀取按鈕狀態
  int buttonState = digitalRead(buttonPin);

  // 根據距離觸發不同反應
  if (distance < dangerDistance) {
    // 過近：生氣表情 + 紅燈 + 警報 + 揮動手臂
    lcd.setCursor(0, 0);
    lcd.print("Stay Away!   ");
    lcd.setCursor(0, 1);
    lcd.print(">:(          ");
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(blueLedPin, LOW);
    tone(buzzerPin, 1000); // 警報聲
    stepper.step(stepsPerRevolution / 2); // 揮動手臂
    stepper.step(-stepsPerRevolution / 2);
  } else if (distance < safeDistance) {
    // 安全距離：平靜表情 + 綠燈
    lcd.setCursor(0, 0);
    lcd.print("Hello :)     ");
    lcd.setCursor(0, 1);
    lcd.print("             ");
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(blueLedPin, LOW);
    noTone(buzzerPin);
  }

  // 按下按鈕：開心表情 + 播放快樂頌音樂 + LED 閃爍
  if (buttonState == LOW) {
    lcd.setCursor(0, 0);
    lcd.print("Yay! I'm :)  ");
    lcd.setCursor(0, 1);
    lcd.print("Ode to Joy! ");
    playOdeToJoyWithLED();
  }

  delay(100);
}

// 播放快樂頌音樂並同步控制 LED 閃爍
void playOdeToJoyWithLED() {
  int melody[] = {262, 262, 294, 330, 330, 294, 262, 247, 262, 262, 294, 330, 330, 294, 262, 247, 247, 262, 247, 220, 247, 262, 294, 262, 220, 247};
  int noteDurations[] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};

  for (int i = 0; i < 26; i++) {
    int noteDuration = 1000 / noteDurations[i];
    tone(buzzerPin, melody[i], noteDuration);

    // LED 閃爍根據音符節奏
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(blueLedPin, HIGH);
    delay(noteDuration / 2); // LED 開啟時間
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(blueLedPin, LOW);
    delay(noteDuration / 2); // LED 關閉時間

    noTone(buzzerPin);
  }
}