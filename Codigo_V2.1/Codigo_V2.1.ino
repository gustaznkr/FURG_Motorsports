#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <SoftWire.h>
#include <stdio.h>
#include <stdlib.h>

//**********DEFINIÇÃO PARA A MPU**************
//Deve-se utilziar a softwire pq apararentemente da conflito entre a Wire e o RF24,
//ao testar com a SoftWire não tivemos problema.
SoftWire SWire(PB6, PB7, SOFT_FAST);
#define MPU 0x68
int AcX, AcY, AcZ, GyX, GyY, GyZ;

//*******************DEFINIÇÕES DO RADIO *************************
RF24 radio(PA12, PA15); // CE, CSN on Blue Pill
const uint64_t address = 0xF0F0F0F0E1LL;
#define writingPipe    0xF0F0F0F0E1LL        // nrf24 communication address
#define dataRate       RF24_250KBPS          // nrf24 data rate (lower == more distance)
#define paLevel        RF24_PA_HIGH          // nrf24 power level (black ebay models have some problems with PA_MAX)

//*******************DEFINIÇÕES DO DISPLAY *************************
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341_STM.h"
#define TFT_CS     PB12
#define TFT_DC     PA11
#define TFT_RST    PA8

//*******************DEFINIÇÕES DOS SENSORES DE TEMPERATURA *************************
#include <Thermistor.h>
#include <NTC_Thermistor.h>
Thermistor* t_CVT;
Thermistor* t_motor;

//************DEFINIÇÃO DE PORTAS UTILIZADAS****************
#define sensor_vel PA3  //Sensor de velocidade
#define Ref_Bateria PA0
#define alarme_motor PC15
#define alarme_cvt PB9
#define alarme_bateria PB8
#define ledComb PC14 //Combustivel critico
#define Reed PA4

//**********DEFINIÇÃO DE VARIÁVEIS**************

//Sensor de velocidade
int rpm;
float velocidade;
float rpm_roda;
int diametro = 0.51;  //Diâmetro da roda do carro em metros
volatile byte pulsos;
unsigned long timeold;
unsigned int pulsos_por_volta = 8;  //Numero de cristas no encoder

float temp_motor = 0; //Definição da variável de temperatura do Motor
float temp_cvt = 0; //Definição da vairável de temperatura do CVT

//Definição das variáveis do sensor de combustível
int Valor = 0, Cont = 0, Cont2 = 0, Cont3 = 0, comb = 0;

//Definição das variáveis do sensor de tensão
const int referenceVolts = 5; //Tensão de referência
int val = 0;
int tensao = 0;

//Definição para os sensores de temperatura
#define R0 220 //resistência de referência
#define Rn 5000 //Resistência nominal do thermistor
#define Tn 25// Temperatura
#define B 3950 //Constante
#define STM32_ANALOG_RESOLUTION 4095 //Resolução do ADC
int nivel;

int media[6], cont7 = 0, velocidademedia, soma, flag = 0;

void contador()
{
  //Incrementa contador
  pulsos++;
}

char msg[13];

Adafruit_ILI9341_STM tft = Adafruit_ILI9341_STM(TFT_CS, TFT_DC, TFT_RST); // Use hardware SPI

void setup() {
  //*******************DEFINIÇÕES DA IMU *************************
  SWire.begin();
  SWire.endTransmission();

  //*******************DEFINIÇÕES DO RADIO *************************
  afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY); // PB3 free
  afio_remap(AFIO_REMAP_SPI1);
  SPI.setModule(1);
  Serial.begin(9600);
  radio.begin();                  //Starting the Wireless communication
  radio.setPALevel(paLevel);
  //radio.setDataRate(dataRate);
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.stopListening();          //This sets the module as transmitter
  
  //*******************DEFINIÇÕES DO DISPLAY *************************
  SPI.setModule(2);
  tft.begin();
  
  //*******************SENSOR DE VELOCIDADE*************************
  pinMode(sensor_vel, INPUT);
  //Aciona o contador a cada pulso
  attachInterrupt(digitalPinToInterrupt(sensor_vel), contador, RISING);
  pulsos = 0;
  rpm = 0;
  timeold = 0;

  pinMode(Ref_Bateria, INPUT); //Sensor da bateria
  pinMode(alarme_motor, OUTPUT); //Alarme
  pinMode(alarme_cvt, OUTPUT);  //Alarme
  pinMode(alarme_bateria, OUTPUT); //Alarme

  //****************DEFINIÇÃO DE TEMPERATURAS***********************
  t_motor = new NTC_Thermistor(PA1, R0, Rn, Tn, B,STM32_ANALOG_RESOLUTION);
  t_CVT = new NTC_Thermistor(PA2, R0, Rn, Tn, B,STM32_ANALOG_RESOLUTION);
  
  //********************COMBUSTIVEL*********************************
  pinMode(Reed, INPUT);
  pinMode(ledComb, OUTPUT);
  
}

void loop() {

  bateria();

  combustivel();
  
  temp();

  getVelocidade();

  Acelerometro();
  
  Display();
  
  Radio();

  delay(1000);

}
