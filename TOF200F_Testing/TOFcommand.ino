void TOFrst()  //restart TOF
{
  for (int i = 0; i < 8; i++)
    Serial2.write(CMD[3][i]);
}

void highPrecision() {
  for (int i = 0; i < 8; i++)
    Serial2.write(distanceCMD[1][i]);
}

void longDistance() {
  for (int i = 0; i < 8; i++)
    Serial2.write(distanceCMD[2][i]);
}

void highSpeed() {
  for (int i = 0; i < 8; i++)
    Serial2.write(distanceCMD[3][i]);
}

void t_100ms(){
  for (int i = 0; i < 8; i++)
    Serial2.write(timeCMD[0][i]);
}
