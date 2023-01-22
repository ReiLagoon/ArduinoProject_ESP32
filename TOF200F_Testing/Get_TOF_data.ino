/**
 * @brief Read data from Serial2, Display distance
 * @ref https://github.com/ibrahimqazi/TFmini-S-interfacing-with-ESP32
 * @return None
 */
void Get_TOF_data() {

  // Using TOF200F
  if (Serial2.available())  //check if serial port has data input
  {
    if (rec_debug_state == 0x01) {  //slave address
      uart[0] = Serial2.read();     // 01

      if (uart[0] == 0x01) {
        rec_debug_state = 0x02;
      } else {
        rec_debug_state = 0x01;
      }

    } else if (rec_debug_state == 0x02) {  //function number
      uart[1] = Serial2.read();            //03

      if (uart[1] == 0x03) {
        rec_debug_state = 0x03;
      } else {
        rec_debug_state = 0x01;
      }
    } else if (rec_debug_state == 0x03) {
      uart[2] = Serial2.read();  //02

      if (uart[2] == 0x02) {
        rec_debug_state = 0x04;
      } else {
        rec_debug_state = 0x01;
      }

    } else if (rec_debug_state == 0x04) {  //number of data bytes
      uart[3] = Serial2.read();

      if (uart[3] != 0xFF) {  
        rec_debug_state = 0x05;
      } else {
        rec_debug_state == 0x01;  // Out of range
      }

    } else if (rec_debug_state == 0x05) {
      uart[4] = Serial2.read();  // max = 255 mm
    }

    if (uart[4] > 0) {
      int dist = (uart[3] * 256 + uart[4]);
      float d = dist ;
      if (dist == 47604) {
        Serial.println("Object too far");
      } else {
        Serial.print(F("distance = "));
        Serial.print(d / 10);
        Serial.println(F(" cm"));
      }
      
      /* // uncomment to view raw data
      Serial.println();
      for (int i = 0; i < 5; i++) {
        Serial.print(uart[i]);
        Serial.print(" ");
      }  //*/

      while (Serial2.available()) { Serial2.read(); }  // This part is added becuase some previous packets are there in the buffer so to clear serial buffer and get fresh data.
      delay(100);
      rec_debug_state = 0x01;
      memset(uart, 0, sizeof(uart));  // reset the array
    }
  }
}
