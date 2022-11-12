void temp()
{
  temp_motor = t_motor->readCelsius();
  temp_cvt = t_CVT->readCelsius();
  Serial.print("Temperatura no Sensor do Motor: ");
  Serial.println(temp_motor);
  Serial.print("Temperatura no Sensor do CVT: ");
  Serial.println(temp_cvt);
  if(temp_motor > 95){
    digitalWrite(alarme_motor, HIGH);
  } else{
    digitalWrite(alarme_motor, LOW);
  }
  if(temp_cvt > 150){
    digitalWrite(alarme_cvt, HIGH);
  } else{
    digitalWrite(alarme_cvt, LOW);
  }
}
