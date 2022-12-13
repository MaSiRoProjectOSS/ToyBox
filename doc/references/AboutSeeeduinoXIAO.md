## [Seeeduino XIAO](https://wiki.seeedstudio.com/jp/Seeeduino-XIAO/)�ɂ���

### ���ӎ���

GPIO��3.3V�œ��o�͂��܂��B����ȏ�̓d�����������ꍇ��CPU�j�����������邱�Ƃ�����܂��B

### [Pin](https://github.com/Seeed-Studio/ArduinoCore-samd/blob/master/variants/XIAO_m0/variant.cpp)�̊֌W

|    pin     | UART       | SPI             | Digital I/F  | DAC  | I2C      | Analog I/F | PWM         | SWD       | SWD                   | LED          | ���̑�     |
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
|     13     | --         | --              | --           | --   | --       | --         | --          | --        | --                    | digitalWrite | �I�����W�F |
|     30     | --         | --              | --           | --   | --       | --         | --          | SWCLK(*2) | --                    | --           |            |
|     31     | --         | --              | --           | --   | --       | --         | --          | SWDIO(*2) | --                    | --           |            |
|   RESET    | --         | --              | --           | --   | --       | --         | --          | --        | �O�������GND�V���[�g | --           |            |
|  LED_�d��  | --         | --              | --           | --   | --       | --         | --          | --        | --                    | --           | �ΐF(*4)   |
| LED_RX(*1) | --         | --              | --           | --   | --       | --         | --          | --        | --                    | --           | �F       |
| LED_TX(*1) | --         | --              | --           | --   | --       | --         | --          | --        | --                    | --           | �F       |
|    USB     | SerialUSB  | --              | --           | --   | --       | --         | --          | --        | --                    | --           |            |

*1 : �V���A���ʐM�C���W�P�[�^�[�Ƃ��ĒʐM���ɓ_��
*2 : digitalWrite�炪�ݒ肳��Ă��Ȃ����ߒ��ڃ��W�X�^��ݒ肷��K�v������܂��B�Q�l�F[Seeeduino XIAO �w�ʃp�b�h��GPIO�Ƃ��Ďg��](https://qiita.com/nanase/items/37ecca24aee8fbd4492e)
*3 : 5-pin/7-pin�͓����Ɏg�p���邱�Ƃ͕s��
*4 : �d��LED�̓{�[�h�z���̂��ߑ���͕s�B�����I�ɔr�����Ă�����ɂ͉e���͂Ȃ��B
