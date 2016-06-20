#include <SoftwareSerial.h>

#define FORWARD_SWITCH 13
#define BT_RX 10 // Arduinohは10番で通信を受け付けるRN42ではTXD
#define BT_TX 11 // Arduinohは11番で通信を送信するRN42ではRXD

#define PWM_WIDTH 500
#define PORATE 115200

SoftwareSerial btSerial(BT_RX, BT_TX); // Bluetoothとやりとりするためのシリアル設定

void setup()
{
  // ボタン用のピンの初期化
  pinMode(FORWARD_SWITCH, INPUT);
  // Mac側のシリアルポートの初期化
  Serial.begin(PORATE);
  // Bluetooth側のシリアルポートの初期化
  btSerial.begin(PORATE);
}

void loop()
{
  byte current = B00000;
  char c;
  if (digitalRead(FORWARD_SWITCH) == HIGH) {
      //スイッチの状態を調べる
      Serial.print("Forward");
      sendKey((byte)0x52); // 「↑」の信号を送信
  }
    // Read from internal serial port (with PC)
  // Read from internal serial port (with PC)
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
        //SH,0200 //Descriptor typeをKeyboardにする（デフォルトだから変更しなくてもよい）
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

void sendKeyModifier(byte key, byte modifier){
  sendKeyCode(key, modifier);
  delay(100);
  sendKeyCode((byte)0x00, (byte)0x00);
}

void sendKey(byte key){
  sendKeyModifier(key, (byte)0x00);
}

void sendKeyCode(byte key, byte modifier){
    btSerial.write(0xFD);
    btSerial.write(0x09);
    btSerial.write(0x01);
    btSerial.write(modifier);
    btSerial.write((byte)0x00);
    btSerial.write(key);
    btSerial.write((byte)0x00);
    btSerial.write((byte)0x00);
    btSerial.write((byte)0x00);
    btSerial.write((byte)0x00);
    btSerial.write((byte)0x00);
}
