## Photosensors(人感センサー)

### 用意したもの

* Seeeduino XIAO
* 赤外線反射センサー
  * 安いものは30cmぐらいの検知距離のものが購入可能。最大8mまでの製品があることを確認済み


### 配線

```plantuml
@startuml
left to right direction
scale 350 height

rectangle "Seeeduino XIAO" as XIAO {
  circle "Pin [0] to [4]_DigitalIN" as Pin_XIAO

  circle "GND" as GND_XIAO
  circle "3V3" as 3V3_XIAO
}
rectangle "赤外線反射センサー×5" as Photosensors {
  circle "OUT" as OUT_Photosensors
  circle "GND" as GND_Photosensors
  circle "3V3" as 3V3_Photosensors
}

3V3_Photosensors -- 3V3_XIAO : " * : 1"
GND_Photosensors -- GND_XIAO : " * : 1"
OUT_Photosensors -- Pin_XIAO : " * : 1"

@enduml
```

### 動作

* 距離の設定は赤外線反射センサーの可変抵抗で行う
* 100ms間隔(LOOP_DELAY_MS)で判定ロジックが動作する
* 検知状態
  * UARTに検知/検知なしを表示する
    * 指定時間(DETECTION_WAITING_TIME_MS)経過後も検知し続けていたら「detection」を表示する
    * 検知後に指定時間(FLAG_RELEASE_TIME_MS)経過しても検知が無かったら「lost」を表示する
  * LED_LIGHTING_ON_BOARDが1ならば検知中は基板上のLED点灯


### 設定

#### PINのLOW/HIGH

検知した時のLOW/HIGHの判定は下記の変数で設定している。

```c++
// LOWの時に検知した
const uint8_t PIN_OUTPUT_STATUS = LOW;
```

#### 判定に使うPINの設定

Pin0～4までの５つで行ている。
下記のコードを'0'にすれば判定をしない。

```c++
#define DETECTION_ENABLE_01 1
#define DETECTION_ENABLE_02 1
#define DETECTION_ENABLE_03 1
#define DETECTION_ENABLE_04 1
#define DETECTION_ENABLE_05 1
```

PINの位置を変更したい場合は下記のコードでPIN番号を設定する。

```c++
const int DigitalAnalogPin_1 = 0;
const int DigitalAnalogPin_2 = 1;
const int DigitalAnalogPin_3 = 2;
const int DigitalAnalogPin_4 = 3;
const int DigitalAnalogPin_5 = 4;
```

#### 検知したときのボードのLED点灯

検知したときにLEDを点灯させたくない場合は下記のコードを'0'に変更する。

```c++
#define LED_LIGHTING_ON_BOARD 1
```


### 特記事項

* 横に並べる場合は中心から凸型になるように検知距離にすると良い感じに検知していた。
* 検知距離を一定以上にすると横の赤外線反射センサーを常時検知するためカバーなので物理的に届かないようにするか話す必要がある。
