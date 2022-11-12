void Acelerometro() 
{
  SWire.beginTransmission(MPU);
  SWire.write(0x3B); //Pedir el registro 0x3B - corresponde al AcX
  SWire.endTransmission(false);
  SWire.requestFrom(MPU, 6, true); //A partir del 0x3B, se piden 6 registros

  AcX = SWire.read() << 8 | SWire.read(); //Cada valor ocupa 2 registros
  AcY = SWire.read() << 8 | SWire.read();
  AcZ = SWire.read() << 8 | SWire.read();

  SWire.beginTransmission(MPU);
  SWire.write(0x43);
  SWire.endTransmission(false);
  SWire.requestFrom(MPU, 6, true); //A partir del 0x43, se piden 6 registros

  GyX = SWire.read() << 8 | SWire.read(); //Cada valor ocupa 2 registros
  GyY = SWire.read() << 8 | SWire.read();
  GyZ = SWire.read() << 8 | SWire.read();

  SWire.endTransmission();

  Serial.print(AcX);
  Serial.print(", ");
  Serial.print(AcY);
  Serial.print(", ");
  Serial.print(AcZ);
  Serial.print(", ");
  Serial.print(GyX);
  Serial.print(", ");
  Serial.print(GyY);
  Serial.print(", ");
  Serial.print(GyZ);
  Serial.println(",");

}
