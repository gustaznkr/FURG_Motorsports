void Radio() {

  afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY); // PB3 free
  afio_remap(AFIO_REMAP_SPI1);
  SPI.setModule(1);
  //Pàra funcionar com a interface do usuário a mensagem deve ser: 
  //Temp_motor;Velocidade;Temp_CVT;Tensao_bateria(0-12V);Nivel_combustivel (1=Low, 2=Med e 3=High)
  sprintf(msg, "%d;%d;%d;%d;%d",temp_motor,velocidademedia,temp_cvt,tensao,comb);
  Serial.println(msg);
  radio.stopListening();
  bool ok = radio.write(&msg, sizeof(msg));
        if (ok)
        Serial.println("ok\n\r");
      else
        Serial.println("failed\n\r");
  delay(100);

}


