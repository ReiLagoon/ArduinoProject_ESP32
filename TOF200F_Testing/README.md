# Testing of TOF200F using UART connection

## Connection
#### 
    ESP-WROOM-32            TOFxxxF
    ------------            --------
      5V/3.3V        ---      VIN  
       GND           ---      GND 
     (TXD2) 17       ---      RXD 
     (RXD2) 16       ---      TXD  


## Error Case
### If Serial2.available() returns 0, 
  It is possible that the current is unstable. Examine the TOF200F's VIN pin.
