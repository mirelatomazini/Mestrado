// Codigo utilizado no STM32F103C8T6 que atua como mestre
// O objetivo é garantir que a comunicação entre os dois dispositivos STM32 (mestre e escravo) esta ocorrendo
// Para isso esse mestre atualiza e envia o valor de "x" periodicamente para que o escravo receba e imprima no monitor serial

// Criado por: Mirela de Oliveira Tomazini em 01 de setembro de 2024
// Código adaptado a partir do arquivo "Wire Peripheral Receiver" by Nicholas Zambetti [http://www.zambetti.com](http://www.zambetti.com) - Created 29 March 2006
// This example code is in the public domain.

// Esse codigo foi testado e funcionou utilizando Arduino IDE versao 2.3.2
// O pino B6 - SCL (clock) do mestre e escravo estao conectados entre si a um ressitor pul-up (vide esquema)
// O pino B7 - SDA (dados) do mestre e escravo estao conectados entre si a um ressitor pul-up (vide esquema)
// Alem disso, os pinos GND de ambas as placas estao conectadas para garantir que ambos tenham a mesma referencia.


#include <Wire_slave.h>

double i=1;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PC13, OUTPUT);      // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);         // start serial for output
  Wire.begin();               // join i2c bus (address optional for master)
}

// the loop function runs over and over again forever
void loop() {
  if (i<20){
    i = i+1;
  }
  else{
    i = 1;
  }

                     // a cada loop que ocorre o i aumenta em uma unidade seu valor
  Wire.beginTransmission(4);  // transmit to device #4       
  Wire.write(i);              // sends one byte
  Wire.endTransmission();     // stop transmitting
  digitalWrite(PC13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                 // adiciona um delay de 400 ms
  digitalWrite(PC13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                 // adiciona um delay de 400 ms

}
