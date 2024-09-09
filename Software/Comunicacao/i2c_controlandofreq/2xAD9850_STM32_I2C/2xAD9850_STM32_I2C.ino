// =============================================================================================================
// --- Mapeamento de Bibliotecas ---
#include <Wire_slave.h>


// =============================================================================================================
// --- Mapeamento de Hardware ---
#define W_CLK_2 PA7  //Pino WCLK  do módulo AD9850 - Gerador 2 (amarelo)
#define FQ_UD_2 PA6  //Pino FQUP  do módulo AD9850 - Gerador 2 (laranja)
#define DATA_2 PA5   //Pino data  do módulo AD9850 - Gerador 2 (preto)
#define RESET_2 PA4  //Pino reset do módulo AD9850 - Gerador 2 (verde)

#define W_CLK_1 PB12  //Pino WCLK  do módulo AD9850 - Gerador 1 (amarelo)
#define FQ_UD_1 PB13  //Pino FQUP  do módulo AD9850 - Gerador 1 (laranja)
#define DATA_1 PB14   //Pino data  do módulo AD9850 - Gerador 1 (preto)
#define RESET_1 PB15  //Pino reset do módulo AD9850 - Gerador 1 (cinza)


// =============================================================================================================
// --- Constantes Auxiliares ---
#define AD9850_CLOCK 125000000  //Frequência do cristal do módulo


// =============================================================================================================
// --- Funções Auxiliares ---
#define pulseHigh(pin) \
  { \
    digitalWrite(pin, HIGH); \
    digitalWrite(pin, LOW); \
  }
//Cria uma função que se chama "pulseHigh", primeiro escreve o valor lógico "HIGH" nesse pino e, em seguida, escreve o valor lógico "LOW" nesse pino.


// =============================================================================================================
// --- Protótipo das Funções ---
//==========================================
void receiveEvent(int howMany);
void tfr_byte_1(byte data);              //transfere um byte de forma serial, pelo pino DATA
void tfr_byte_2(byte data);              //transfere um byte de forma serial, pelo pino DATA
void sendFrequency_1(double frequency);  //envia a frequência configurada pelo usuário
void sendFrequency_2(double frequency);  //envia a frequência configurada pelo usuário

double x = 1;
double freq_1;          //local de definição do valor de frequência do sinal desejado no Gerador 1
long unsigned int freq_2 = 20000;  //local de definição do valor de frequência do sinal desejado no Gerador 2


// =============================================================================================================
// --- Configurações Iniciais ---
void setup() {
  pinMode(FQ_UD_1, OUTPUT);  //Configura pinos como saída que serão enviados para o Gerador 1
  pinMode(W_CLK_1, OUTPUT);
  pinMode(DATA_1, OUTPUT);
  pinMode(RESET_1, OUTPUT);
  pinMode(FQ_UD_2, OUTPUT);  //Configura pinos como saída que serão enviados para o Gera
  pinMode(W_CLK_2, OUTPUT);
  pinMode(DATA_2, OUTPUT);
  pinMode(RESET_2, OUTPUT);

  // --- Configurações da comunicacao I2C ---
  Wire.begin(4);                 // Configura que esse sera o escravo com endereco 4
  Wire.onReceive(receiveEvent);  // Registra o evento
  Serial.begin(9600);            // Inicia o modulo serial

  // Inicializa os módulos AD9850.
  pulseHigh(RESET_1);
  pulseHigh(W_CLK_1);
  pulseHigh(FQ_UD_1);  //Este pulso habilita o AD9850 para funcionar no modo serial (ver datasheet pag 12, figura 10)

  pulseHigh(RESET_2);
  pulseHigh(W_CLK_2);
  pulseHigh(FQ_UD_2);

  //final das configurações iniciais do AD9850
}

// =============================================================================================================
// --- Loop Infinito ---
void loop() {
  delay(200);
  freq_1 = 1000*x;
  sendFrequency1(freq_1);
  sendFrequency2(freq_2);
  Serial.println(x);
  Serial.println(freq_1);
  //freq = freq+1000;   // Após cada 10 segundos de delay, aumenta 1 kHz na freq enviada
}



// =============================================================================================================
// --- Desenvolvimento das Funções ---

// =============================================================================================================

void receiveEvent(int howMany) {
  x = Wire.read();  // receive byte as an integer porque o x eh um inteiro
}

void tfr_byte_1(byte data) {
  for (int i = 0; i < 8; i++, data >>= 1) {
    digitalWrite(DATA_1, data & 0x01);
    pulseHigh(W_CLK_1);  //gera um pulso no W_CLK a cada bit transferido
  }                      //end for
}  //end tfr_byte

void tfr_byte_2(byte data) {
  for (int i = 0; i < 8; i++, data >>= 1) {
    digitalWrite(DATA_2, data & 0x01);
    pulseHigh(W_CLK_2);  //gera um pulso no W_CLK a cada bit transferido
  }                      //end for
}  //end tfr_byte

// =============================================================================================================
void sendFrequency1(double frequency) {
  int32_t freq1 = frequency * 4294967295 / AD9850_CLOCK;  //calcula frequência

  for (int b = 0; b < 4; b++, freq1 >>= 8) tfr_byte_1(freq1 & 0xFF);

  tfr_byte_1(0x000);   //Final, reinicia o valor do byte
  pulseHigh(FQ_UD_1);  //Pronto!

}  //end sendFrequency

void sendFrequency2(double frequency) {
  int32_t freq2 = frequency * 4294967295 / AD9850_CLOCK;  //calcula frequência

  for (int c = 0; c < 4; c++, freq2 >>= 8) tfr_byte_2(freq2 & 0xFF);

  tfr_byte_2(0x000);   //Final, reinicia o valor do byte
  pulseHigh(FQ_UD_2);  //Pronto!

}  //end sendFrequency


// =============================================================================================================
