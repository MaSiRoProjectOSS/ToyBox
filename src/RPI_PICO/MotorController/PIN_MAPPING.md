# Pin Mapping

[link: products/raspberry-pi-pico](https://www.raspberrypi.com/products/raspberry-pi-pico/)
[link: documentation/raspberry-pi-pico](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html)
https://arduino-pico.readthedocs.io/en/latest/platformio.html

| UART   | I2C    | SPI    | GP     | GND    |   No |   -- |   -   | -    | No   | Volt     | GND    | GP     | AD     | SPI    | I2C    | UART   | Other  |
| ------ | ------ | ------ | ------ | ------ | ---: | ---: | :---: | :--- | :--- | -------- | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| TX_0   | SDA_0  | RX_0   | 0      | &nbsp; |    1 |    A |  ---  | --   | 40   | VBUS     | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; |
| RX_0   | SCL_0  | CSn_0  | 1      | &nbsp; |    2 |    A |  ---  | --   | 39   | VSYS     | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; |
| &nbsp; | &nbsp; | &nbsp; | &nbsp; | GND    |    3 |    A |  ---  | --   | 38   | &nbsp;   | GND    | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; |
| &nbsp; | SDA_1  | SCK_0  | 2      | &nbsp; |    4 |    A |  ---  | --   | 37   | 3V3_EN   | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; |
| &nbsp; | SCL_1  | TX_0   | 3      | &nbsp; |    5 |    A |  ---  | --   | 36   | 3V3(OUT) | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; |

| UART   | I2C    | SPI    | GP     | GND    |   No |   -- |   -   | -    | No   | Volt   | GND    | GP     | AD       | SPI    | I2C    | UART   | Other  |
| ------ | ------ | ------ | ------ | ------ | ---: | ---: | :---: | :--- | :--- | ------ | ------ | ------ | -------- | ------ | ------ | ------ | ------ |
| TX_1   | SDA_0  | RX_0   | 4      | &nbsp; |    6 |    B |  ---  | G    | 35   | &nbsp; | &nbsp; | &nbsp; | ADC_VREF | &nbsp; | &nbsp; | &nbsp; | &nbsp; |
| RX_1   | SCL_0  | CSn_0  | 5      | &nbsp; |    7 |    B |  ---  | G    | 34   | &nbsp; | &nbsp; | 28     | ADC2     | &nbsp; | &nbsp; | &nbsp; | &nbsp; |
| &nbsp; | &nbsp; | &nbsp; | &nbsp; | GND    |    8 |    B |  ---  | G    | 33   | &nbsp; | GND    | &nbsp; | AGND     | &nbsp; | &nbsp; | &nbsp; | &nbsp; |
| &nbsp; | SDA_1  | SCK_0  | 6      | &nbsp; |    9 |    B |  ---  | G    | 32   | &nbsp; | &nbsp; | 27     | ADC1     | &nbsp; | SCL_1  | &nbsp; | &nbsp; |
| &nbsp; | SCL_1  | TX_0   | 7      | &nbsp; |   10 |    B |  ---  | G    | 31   | &nbsp; | &nbsp; | 26     | ADC0     | &nbsp; | SDA_1  | &nbsp; | &nbsp; |

| UART   | I2C    | SPI    | GP     | GND    |   No |   -- |   -   | -    | No   | Volt   | GND    | GP     | AD     | SPI    | I2C    | UART   | Other  |
| ------ | ------ | ------ | ------ | ------ | ---: | ---: | :---: | :--- | :--- | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| TX_1   | SDA_0  | RX_1   | 8      | &nbsp; |   11 |    C |  ---  | --   | 30   | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; | RUN    |
| RX_1   | SCL_0  | CSn_1  | 9      | &nbsp; |   12 |    C |  ---  | --   | 29   | &nbsp; | &nbsp; | 22     | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; |
| &nbsp; | &nbsp; | &nbsp; | &nbsp; | GND    |   13 |    C |  ---  | F    | 28   | &nbsp; | GND    | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; |
| &nbsp; | SDA_1  | SCK_1  | 10     | &nbsp; |   14 |    C |  ---  | F    | 27   | &nbsp; | &nbsp; | 21     | &nbsp; | &nbsp; | SCL_0  | &nbsp; | &nbsp; |
| &nbsp; | SCL_1  | TX_1   | 11     | &nbsp; |   15 |    C |  ---  | F    | 26   | &nbsp; | &nbsp; | 20     | &nbsp; | &nbsp; | SDA_0  | &nbsp; | &nbsp; |

| UART   | I2C    | SPI    | GP     | GND    |   No |   -- |   -   | -    | No   | Volt   | GND    | GP     | AD     | SPI    | I2C    | UART   | Other  |
| ------ | ------ | ------ | ------ | ------ | ---: | ---: | :---: | :--- | :--- | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| TX_0   | SDA_0  | RX_1   | 12     | &nbsp; |   16 |    D |  ---  | E    | 25   | &nbsp; | &nbsp; | 19     | &nbsp; | TX_0   | SCL_1  | &nbsp; | &nbsp; |
| RX_0   | SCL_0  | CSn_1  | 13     | &nbsp; |   17 |    D |  ---  | E    | 24   | &nbsp; | &nbsp; | 18     | &nbsp; | SCK_0  | SDA_1  | &nbsp; | &nbsp; |
| &nbsp; | &nbsp; | &nbsp; | &nbsp; | GND    |   18 |    D |  ---  | E    | 23   | &nbsp; | GND    | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; |
| &nbsp; | SDA_1  | SCK_1  | 14     | &nbsp; |   19 |    D |  ---  | E    | 22   | &nbsp; | &nbsp; | 17     | &nbsp; | CSn_0  | SCL_0  | RX_0   | &nbsp; |
| &nbsp; | SCL_1  | TX_1   | 15     | &nbsp; |   20 |    D |  ---  | E    | 21   | &nbsp; | &nbsp; | 16     | &nbsp; | RX_0   | SDA_0  | TX_0   | &nbsp; |


LED / GP25
GP23/24はどこ？

```bash
pio pkg update -g -p https://github.com/maxgerhardt/platform-raspberrypi.git
```

## PICOのドライバーをインストール

PlatFromIOをつかうためにはPICOのドライバーを更新する必要があります。
下記の手順で更新してください。

* Raspberry Pi Pico用のプロジェクトをビルドして、`firmware.uf2`を作成する。
* Raspberry Pi PicoのBOOTSELボタンを押しながらUSBケーブルを接続
* デイバイマネージャを開き「RP2 Boot」でエラーがワーニングが出ていることを確認する。
  * [zadig](https://zadig.akeo.ie/#google_vignette)を使って、「RP2 Boot」をWinUSBとしてインストールする。
  * リムーバルドライバに作成した「firmware.uf2」を書いてソフトを書き込む

上記の手順を実行後はCOMポートとして常に認識するため、PlatformIOから書き込みが可能になります。
