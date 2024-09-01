// Codigo utilizado no STM32F103C8T6 que atua como escravo 
// O objetivo eh garantir que a comunicação entre os dois dispositivos STM32 (mestre e escravo) esta ocorrendo
// Para isso esse escravo recebe o valor de "x" do mestre e escreve na tela do monitor serial.

// Criado por: Mirela de Oliveira Tomazini em 01 de setembro de 2024
// Código adaptado a partir do arquivo "Wire Peripheral Receiver" by Nicholas Zambetti [http://www.zambetti.com](http://www.zambetti.com) - Created 29 March 2006
// This example code is in the public domain.

// Esse codigo foi testado e funcionou utilizando Arduino IDE versao 2.3.2
// O pino B6 - SCL (clock) do mestre e escravo estao conectados entre si a um ressitor pul-up (vide esquema)
// O pino B7 - SDA (dados) do mestre e escravo estao conectados entre si a um ressitor pul-up (vide esquema)
// Alem disso, os pinos GND de ambas as placas estao conectadas para garantir que ambos tenham a mesma referencia.

#include <Wire_slave.h>
int x = 0;

void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  pinMode(PC13, OUTPUT);        // define PC13 como uma saida
}

void loop()
{
  digitalWrite(PC13, LOW);   // turn the LED off by making the voltage LOW
  delay(200);                // adiciona um delay de 200 ms
  digitalWrite(PC13, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(200);                // adiciona um delay de 200 ms
  Serial.println(x);         // imprime no monitor serial o valor de x
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  x = Wire.read();    // receive byte as an integer porque o x eh um inteiro
}