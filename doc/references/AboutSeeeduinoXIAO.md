## [Seeeduino XIAO](https://wiki.seeedstudio.com/jp/Seeeduino-XIAO/)について

### 注意事項

GPIOは3.3Vで入出力します。それ以上の電圧をかけた場合はCPU破損が発生することがあります。

### [Pin](https://github.com/Seeed-Studio/ArduinoCore-samd/blob/master/variants/XIAO_m0/variant.cpp)の関係

|    pin     | UART       | SPI             | Digital I/F  | DAC  | I2C      | Analog I/F | PWM         | SWD       | SWD                   | LED          | その他     |
| :--------: | :--------- | :-------------- | :----------- | :--- | :------- | :--------- | :---------- | :-------- | :-------------------- | :----------- | :--------- |
|     0      | --         | digitalWrite_CS | digitalWrite | DAC  | --       | analogRead | --          | --        | --                    | --           |            |
|     1      | --         | digitalWrite_CS | digitalWrite | --   | --       | analogRead | analogWrite | --        | --                    | --           |            |
|     2      | --         | digitalWrite_CS | digitalWrite | --   | --       | analogRead | analogWrite | --        | --                    | --           |            |
|     3      | --         | digitalWrite_CS | digitalWrite | --   | --       | analogRead | analogWrite | --        | --                    | --           |            |
|     4      | --         | digitalWrite_CS | digitalWrite | --   | Wire_SDA | analogRead | analogWrite | --        | --                    | --           |            |
|   5(*3)    | --         | digitalWrite_CS | digitalWrite | --   | Wire_SCL | analogRead | analogWrite | --        | --                    | --           |            |
|     6      | Serial1_TX | digitalWrite_CS | digitalWrite | --   | --       | analogRead | analogWrite | --        | --                    | --           |            |
|   7(*3)    | Serial1_RX | digitalWrite_CS | digitalWrite | --   | --       | analogRead | analogWrite | --        | --                    | --           |            |
|     8      | --         | SPI_SCK         | digitalWrite | --   | --       | analogRead | analogWrite | --        | --                    | --           |            |
|     9      | --         | SPI_MISO        | digitalWrite | --   | --       | analogRead | analogWrite | --        | --                    | --           |            |
|     10     | --         | SPI_MOSI        | digitalWrite | --   | --       | analogRead | analogWrite | --        | --                    | --           |            |
|     13     | --         | --              | --           | --   | --       | --         | --          | --        | --                    | digitalWrite | オレンジ色 |
|     30     | --         | --              | --           | --   | --       | --         | --          | SWCLK(*2) | --                    | --           |            |
|     31     | --         | --              | --           | --   | --       | --         | --          | SWDIO(*2) | --                    | --           |            |
|   RESET    | --         | --              | --           | --   | --       | --         | --          | --        | 外部からのGNDショート | --           |            |
|  LED_電源  | --         | --              | --           | --   | --       | --         | --          | --        | --                    | --           | 緑色(*4)   |
| LED_RX(*1) | --         | --              | --           | --   | --       | --         | --          | --        | --                    | --           | 青色       |
| LED_TX(*1) | --         | --              | --           | --   | --       | --         | --          | --        | --                    | --           | 青色       |
|    USB     | SerialUSB  | --              | --           | --   | --       | --         | --          | --        | --                    | --           |            |

*1 : シリアル通信インジケーターとして通信時に点灯
*2 : digitalWriteらが設定されていないため直接レジスタを設定する必要があります。参考：[Seeeduino XIAO 背面パッドをGPIOとして使う](https://qiita.com/nanase/items/37ecca24aee8fbd4492e)
*3 : 5-pin/7-pinは同時に使用することは不可
*4 : 電源LEDはボード配線のため操作は不可。物理的に排除しても動作には影響はない。
