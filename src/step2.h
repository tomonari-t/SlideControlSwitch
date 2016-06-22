#include <SoftwareSerial.h>

#define BT_RX 10 // Arduinohは10番で通信を受け付けるRN42ではTXD
#define BT_TX 11 // Arduinohは11番で通信を送信するRN42ではRXD

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

    if(c == 's'){
      // 設定モードスタート
        Serial.write("$$$\n");
        btSerial.print("$$$");
    }
    if(c == 'e'){
      // 設定モード終了
        Serial.write("-\n");
        btSerial.print("-");
        btSerial.print('\r');
    }
    if(c == 'f'){
      // 工場出荷時の状態にする
        Serial.write("SF,1\n");
        btSerial.print("SF,1");
        btSerial.print('\r');
    }
    if(c == 'm'){
      //pairing modeにする
        Serial.write("SM,6\n");
        btSerial.print("SM,6");
        btSerial.print('\r');
    }
    if(c == 'p'){
      //プロファイルをHIDに変更
        Serial.write("S~,6\n");
        btSerial.print("S~,6");
        btSerial.print('\r');
    }
    if(c == 'r'){
       //モジュールをリブート
        Serial.write("R,1\n");
        btSerial.print("R,1");
        btSerial.print('\r');
    }
    if(c == 'd'){
        //current
        Serial.write("D\n");
        btSerial.print("D");
        btSerial.print('\r');
    }
    if(c == 'k'){
        //Descriptor typeをKeyboardにする
        Serial.write("SH,0220\n");
        btSerial.print("SH,0200");// keyboard
        btSerial.print('\r');
    }
    if(c == 'b'){
        Serial.write("SU,9600\n");
        btSerial.print("SU,9600");
        btSerial.print('\r');
    }
  }
     delay(10);
}
