void combustivel() {
  
  Valor = analogRead(Reed);
  
  if (Valor > 3000)
  {
    Cont++;
  }

  if ((Valor > 2210) && (Valor < 2900))
  {
    Cont2++;
  }

  if (Valor < 2200)
  {
    Cont3++;
  }

  if (Cont == 5)
  {
    Serial.println("Nivel alto");
    Cont = 0;
    Cont2 = 0;
    Cont3 = 0;
    digitalWrite(ledComb, LOW);
    comb = 3;
  }

  else if (Cont2 == 5)
  {
    Serial.println("Nivel medio");
    Cont = 0;
    Cont2 = 0;
    Cont3 = 0;
    digitalWrite(ledComb, LOW);
    comb = 2;
  }

   else if (Cont3 == 5)
  {
    Serial.println("Nivel baixo");
    Cont = 0;
    Cont2 = 0;
    Cont3 = 0;
    digitalWrite(ledComb, HIGH);
    comb = 1;
  }
  Serial.print("Nivel do combustivel:");
  Serial.println(comb);
}
