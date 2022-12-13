#include <Arduino.h>
#include <SPI.h>
#include <mcp_can.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128]; // Array to store serial string

const byte CAN_MODE  = MCP_STDEXT;
const byte CAN_SPEED = CAN_250KBPS;
const byte CAN_CLOCK = MCP_8MHZ;

#define CAN0_INT 2 // Set INT to pin 2
MCP_CAN CAN0(3);   // Set CS to pin 3
/*
|     0      | --         | digitalWrite_CS
|     1      | --         | digitalWrite_CS
|     2      | --         | digitalWrite_CS
|     3      | --         | digitalWrite_CS
|     8      | --         | SPI_SCK
|     9      | --         | SPI_MISO
|     10     | --         | SPI_MOSI
*/

void output_message(bool message_type_is_error, const char *message, bool add_header = true)
{
    if (true == add_header) {
        char buffer[300];
        unsigned long tm    = millis();
        unsigned long tm_s  = tm / 1000;
        unsigned long tm_ms = tm % 1000;

        if (true == message_type_is_error) {
            sprintf(buffer, "[Error] [%7ld.%03ld] : %s", tm_s, tm_ms, message);
        } else {
            sprintf(buffer, "[     ] [%7ld.%03ld] : %s", tm_s, tm_ms, message);
        }
        SerialUSB.println(buffer);
    } else {
        SerialUSB.println(message);
    }
}

void receive()
{
    char buffer[255];
    while (CAN_MSGAVAIL == CAN0.checkReceive()) {
        while (CAN_OK == CAN0.readMsgBuf(&rxId, &len, rxBuf)) {
            unsigned long tm    = millis();
            unsigned long tm_s  = tm / 1000;
            unsigned long tm_ms = tm % 1000;
            sprintf(buffer, "[     ] [%7ld.%03ld] : ", tm_s, tm_ms);
            SerialUSB.print(buffer);
            if ((rxId & 0x80000000) == 0x80000000) { // Determine if ID is standard (11 bits) or extended (29 bits)
                sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
            } else {
                sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);
            }
            SerialUSB.print(msgString);

            if ((rxId & 0x40000000) == 0x40000000) { // Determine if message is a remote request frame.
                sprintf(msgString, " REMOTE REQUEST FRAME");
                SerialUSB.print(msgString);
            } else {
                for (byte i = 0; i < len; i++) {
                    sprintf(msgString, " 0x%.2X", rxBuf[i]);
                    SerialUSB.print(msgString);
                }
            }
            SerialUSB.println();
        }
    }
}
void send(unsigned long id, byte len)
{
    byte buf[8];
    buf[0] = id;
    for (int i = 1; i < 8; i++) {
        buf[i] = 0x10 + i;
    }
    for (int i = 3; i < 8; i++) {
        buf[i] = random(0x10, 0x50);
    }
    CAN0.sendMsgBuf(id, len, buf);
    char buffer[255];
    sprintf(buffer, "send[0x%lx]", id);
    output_message(false, buffer, true);
}

void setup()
{
    SerialUSB.begin(115200);

    // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
    if (CAN0.begin(CAN_MODE, CAN_SPEED, CAN_CLOCK) == CAN_OK) {
        SerialUSB.println("MCP2515 Initialized Successfully!");
    } else {
        SerialUSB.println("Error Initializing MCP2515...");
    }

    CAN0.setMode(MCP_NORMAL); // Set operation mode to normal so the MCP2515 sends acks to received data.

    pinMode(CAN0_INT, INPUT); // Configuring pin for /INT input
    attachInterrupt(CAN0_INT, receive, FALLING);

    SerialUSB.println("MCP2515 Library Receive Example...");
}

void loop()
{
#if 1
    static int cnt      = 0;
    static bool flag_id = false;
    static int flag_len = 1;
    switch (cnt) {
        case 0:
            //output_message(false, "----------", true);
            if (true == flag_id) {
                send(0x50, flag_len);
            } else {
                send(0x55, flag_len);
            }
            flag_id = !flag_id;
            flag_len++;
            if (8 < flag_len) {
                flag_len = 1;
            }
            receive();
            break;
#if 0
        case 24:
            send(0x51,7);
            break;
        case 49:
            send(0x52,6);
            break;
        case 74:
            send(0x53,5);
            break;
        case 99:
            send(0x54,4);
            break;
#endif

        default:
            break;
    }
    cnt++;
    if (cnt >= (2000 / 10)) {
        cnt = 0;
    }
#endif
    (void)delay(10);
}