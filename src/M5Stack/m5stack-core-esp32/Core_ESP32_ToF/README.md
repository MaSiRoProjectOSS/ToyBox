## ToF with Http request-post (ゲート通過センサー)

### 用意したもの

* M5Stack Basic V2.6
* M5Stack用ToF測距センサユニット


### 動作

* 前回検知した距離から```setting.h```の```SETTING_TOF_DETECT_RANG```の移動を検知したら、Wifi経由で検知したことを通知する


### 設定

| 定義名(define名)                 | 概要                                                                 | デフォルト値                               |     |
| -------------------------------- | -------------------------------------------------------------------- | ------------------------------------------ | --- |
| SETTING_WIFI_SSID                | 接続したいWiFiのSSIDを指定してください。                             | "(wifi ssid)"                              |
| SETTING_WIFI_PASS                | 接続したいWiFiのパスワードを指定してください。                       | "(wifi password)"                          |
| SETTING_URL_ENDPOINT             | Http requestをするURLを指定してください。                            | "(URL : http://---.com/---?set_data.html)" |
| SETTING_URL_ENDPOINT_KEY         | Postデータを指定してください。                                       | "{\"flag\" : %d, \"distance\" : %d }"      |
| SETTING_TOF_DETECT_RANG          | 前回の値からの変化量を指定してください。                             | 500                                        |
| SETTING_LOOP_TIME_NORMAL         | 検知する間隔を指定してください。                                     | 250                                        |
| SETTING_LOOP_TIME_SLEEP_DETECT   | 検知後のWait時間を指定してください。                                 | 2000                                       |
| SETTING_LOOP_TIME_WIFI_CONNECTED | Wifiが切断された場合、次の再接続のトライする時間を指定してください。 | 10000                                      |


### 特記事項

* ```SETTING_LOOP_TIME_NORMAL```で指定した間隔で値の比較をします。そのためToFが読み取れる範囲内を```SETTING_LOOP_TIME_NORMAL```以上の速さ通過する場合は、認識できません。
