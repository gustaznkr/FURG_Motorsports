float getVelocidade() {

  velocidade = 0;
  float tempo = ((pulseIn(sensor_vel, HIGH))) / 100000.0;

  if (tempo == 0) {
    velocidade = 0;
  }
  else {
    Serial.print("Tempo:");
    Serial.println(tempo);
    float vel_linear = (0.3) / tempo;
    rpm_roda = ( (vel_linear * 60) / (2*PI))/0.0375; // ( (vel_linear * 60seg) / (2*PIrad))/Raio do flange
    velocidade = rpm_roda * 1.66 * 0.06; //rpm_roda * Circ. roda * 0.06 conv para km/hora;
  }
   if (flag == 0)
  {
    media[cont7] = velocidade;
    cont7++;
    if (cont7 == 5)
      flag = 1;
  }
  if (flag == 1)
  {
    media[0] = media[1];
    media[1] = media[2];
    media[2] = media[3];
    media[3] = media[4];
    media[4] = media[5];
    media[5] = velocidade;

    soma = media[0] + media[1] + media[2] + media[3] + media[4] + media[5];

    velocidademedia = soma / 6;
  }
  Serial.print("RPM:");
  Serial.println(rpm_roda);
  Serial.print("Velocidade:");
  Serial.println(velocidademedia);
  //mostragem = velocidademedia;


}
