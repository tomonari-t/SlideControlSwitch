#include <SoftwareSerial.h>

#define BT_RX 10
#define BT_TX 11

#define PWM_WIDTH 500
#define PORATE 115200


SoftwareSerial btSerial(BT_RX, BT_TX); // Bluetoothとやりとりするためのシリアル設定

void setup()
{
  // Mac側のシリアルポートの初期化
  Serial.begin(PORATE);
  // Bluetooth側のシリアルポートの初期化
  btSerial.begin(PORATE);
}

void loop()
{
  char c;
  if (Serial.available()){
    c = Serial.read();
    btSerial.print(c);
  }
     delay(10);
}
