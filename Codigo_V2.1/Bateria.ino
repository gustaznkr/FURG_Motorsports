void bateria()
{ 
//1.35V  == 1705 na porta
  val = analogRead(Ref_Bateria);
  tensao = map(val, 0, 4095, 0, 12);
  Serial.print("Tensao da bateria:");
  Serial.println(tensao);
  // 
  if(tensao < 5){
    digitalWrite(alarme_bateria, HIGH);
  } else {
    digitalWrite(alarme_bateria, LOW);
  }
}
