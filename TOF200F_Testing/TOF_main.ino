// --------------- GLOBAL DEFINITIONS --------------- //
#define RXD2 16
#define TXD2 17

// ------------------ VARIABLES --------------------- /
int8_t rec_debug_state = 0x01;  // receive state for frame
unsigned char uart[6];          /*----save data measured -------------*/
bool counter = 0;

// Command for TOF sensor

const byte distanceCMD[4][8] = {
  // Change mode
  { 0x01, 0x06, 0x00, 0x04, 0x00, 0x00, 0xC8, 0x0B },  // 0: default, 30ms, 1.2m
  { 0x01, 0x06, 0x00, 0x04, 0x00, 0x01, 0x09, 0xCB },  // 1: High Precision, 200ms, 1.2m
  { 0x01, 0x06, 0x00, 0x04, 0x00, 0x02, 0x49, 0xCA },  // 2: Long Distance, 33ms, 2m
  { 0x01, 0x06, 0x00, 0x04, 0x00, 0x03, 0x88, 0x0A },  // 3: High speed, 20ms, 1.2m
};

const byte timeCMD[4][8] = {
  // Change speed
  { 0x01, 0x06, 0x00, 0x05, 0x00, 0x64, 0x98, 0x20 },  // 100MS
  { 0x01, 0x06, 0x00, 0x05, 0x01, 0xF4, 0x99, 0xDC },  // 500MS
  { 0x01, 0x06, 0x00, 0x05, 0x07, 0xD0, 0x9A, 0x67 },  // 2000MS
  { 0x01, 0x06, 0x00, 0x05, 0x27, 0x10, 0x83, 0xF7 },  // 10000MS
};

const byte CMD[4][8] = {
  // Setting
  { 0x01, 0x06, 0x00, 0x20, 0x00, 0x8C, 0x89, 0xA5 },  // set offcet calibration: 140mm
  { 0x01, 0x06, 0x00, 0x21, 0x00, 0x64, 0x2B, 0xD8 },  // set xtalk calibration: 100mm
  { 0x01, 0x06, 0x00, 0x06, 0x00, 0x01, 0xA8, 0x0B },  // set calibration
  { 0x01, 0x06, 0x00, 0x01, 0x10, 0x00, 0xD5, 0xCA },  // Reset TOF
};

// --------------- INITIALISATION --------------- //
void setup() {
  //delay(2000);
  Serial.begin(115200);
  Serial.println("\nUART LiDAR Program");
  // Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

  delay(100);
  highPrecision();
  //longDistance();
  delay(2000);
  TOFrst();
  delay(2000);
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    Serial.print("Typed: ");
    Serial.println(command);

    if (command == "start") {
      Serial.println("UART LiDAR Program...");
      delay(3000);
      counter = 1;
    }

    if (command == "stop")
      counter = 0;
  }

  if (counter == 1)
    Get_TOF_data();
}
