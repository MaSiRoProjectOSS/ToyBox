
## シリーズ

XIAOには搭載しているマイコンは下記のものがあります。
各マイコンにより搭載しているものが違うため利用するデバイスによって適切なものをお選びください。

| Item                            | SAMD21                              | ESP32C3          | RP2040                              | nRF52840                            | nRF52840 (Sense)                    |
| ------------------------------- | ----------------------------------- | ---------------- | ----------------------------------- | ----------------------------------- | ----------------------------------- |
| WiFi                            | --                                  | v                | --                                  | --                                  | --                                  |
| BLE                             | --                                  | Bluetooth 5 (LE) | --                                  | Bluetooth 5 (LE)                    | Bluetooth 5 (LE)                    |
| NFC                             | --                                  | --               | --                                  | v                                   | v                                   |
| Battery Charge Chip             | --                                  | Built-in         | --                                  | BQ25101                             | BQ25101                             |
| Programming Languages           | Arduino/ MicroPython/ CircuitPython | Arduino          | Arduino/ MicroPython/ CircuitPython | Arduino/ MicroPython/ CircuitPython | Arduino/ MicroPython/ CircuitPython |
| 6 DOF IMU (LSM6DS3TR-C)         | --                                  | --               | --                                  | --                                  | v                                   |
| PDM Microphone                  | --                                  | --               | --                                  | --                                  | v                                   |
| 値段(2022/9/16) <br>相場 / 最安 | 1,100                               | 946/940          | 1,067/750                           | 1,980/1,940                         | 2937/2680                           |
| 消費電力                        | --                                  | --               | --                                  | --                                  | --                                  |
| 拡張ボードの利用可非            | 可                                  | 非               | ？                                  | 可                                  | 可                                  |

選択ポイント

結論：対応言語は少ないが、"ESP32C3"を買っておけば問題なし。
IMUなどを使いたい/拡張ボードを使いたいなどがあれば、"nRF52840 (Sense)"


* 安い
  * ESP32C3
* WiFiを使用したい
  * ESP32C3
* BLEを使用したい
  * ESP32C3
  * nRF52840 (Sense)
* IMUを使用したい
  * nRF52840 (Sense)
* マイクを使用したい
  * nRF52840 (Sense)


### 拡張ボード

* Grove Shield for Seeed Studio XIAO with embedded battery management chip

| Item                  | Value                       |
| --------------------- | --------------------------- |
| Operating voltage     | 3.3V / 3.7V Lithium Battery |
| Load Capacity         | 800mA                       |
| Charging current      | 400mA (Max)                 |
| Operating Temperature | - 40°C to 85°C              |
| Storage Temperature   | -55°C to 150°C              |
| Grove Interface       | I2C * 2 / UART * 1          |

* Seeed Studio XIAO Expansion board

| Item                     | Value                                           |
| ------------------------ | ----------------------------------------------- |
| Operating voltage        | 5V / 3.7V Lithium Battery                       |
| Charging current         | 460mA (Max)                                     |
| RTC timer precision      | ± 1.5S/DAY(25°C)                                |
| RTC battery              | CR1220                                          |
| Display                  | 0.96" OLED display                              |
| Expandable memory        | MicroSD card                                    |
| Grove Interface          | Grove IIC*2, Grove UART*1, A0/D0 Grove*1        |
| Other External Equipment | Passive buzzer, user button, 5V servo connector |
