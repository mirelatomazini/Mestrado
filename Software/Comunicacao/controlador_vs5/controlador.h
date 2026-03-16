#define DEBUG1 1 

// Definindo o ID configurado em cada um dos STM32 perifericos presentes no projeto

#define ID_DEMUX  6
#define ID_MULT   4
#define ID_AQ_U1  7
#define ID_AQ_U4  8
#define ID_AQ_U5  9
#define ID_AQ_U6  5



// Definindo os comandos que cada um dos eletrodos seja usado como eletrodo que aplica a corrente quando usada a fonte de corrente monopolar (ou aplica a corrente 1 na fonte bipolar)

#define I_E0 1
#define I_E1 2
#define I_E2 3
#define I_E3 4
#define I_E4 5
#define I_E5 6
#define I_E6 7
#define I_E7 8
#define I_E8 9
#define I_E9 10
#define I_E10 11
#define I_E11 12
#define I_E12 13
#define I_E13 14
#define I_E14 15
#define I_E15 16


// Definindo os comandos que cada um dos eletrodos seja usado como terra  quando usada a fonte de corrente monopolar (ou aplica a corrente 2, em contrafase na fonte bipolar)

#define O_E0 128
#define O_E1 129
#define O_E2 130
#define O_E3 131
#define O_E4 132
#define O_E5 133
#define O_E6 134
#define O_E7 135
#define O_E8 136
#define O_E9 137
#define O_E10 138
#define O_E11 139
#define O_E12 140
#define O_E13 141
#define O_E14 142
#define O_E15 143




// Definindo os comandos para alterar a frequência de cada um dos geradores

#define F1_1K 65
#define F1_2K 66 
#define F1_3K 67
#define F1_5K 68
#define F1_10K 69
#define F1_20K 70
#define F1_0 90

#define F2_10K 97
#define F2_20K 98
#define F2_30K 99
#define F2_50K 100
#define F2_100K 101
#define F2_150K 102
#define F2_200K 103
#define F2_0 122



// Funcao que sabe o Id do eletrodo com base no ID do periferico e o canal adquirido do periferico

void localizaeletrodo(int ID, byte ch){
  int eletrodo = 99;
  if (ID == ID_AQ_U1){
    if (ch == 1){
      eletrodo = 1;
    }
    else if (ch==2){
      eletrodo = 5;
    }
  }
  else if (ID == ID_AQ_U4){
    if (ch == 1){
      eletrodo = 0;
    }
    else if (ch==2){
      eletrodo = 4;
    }
  }
  else if (ID == ID_AQ_U5){
    if (ch == 1){
      eletrodo = 3;
    }
    else if (ch==2){
      eletrodo = 7;
    }
  }
  else if (ID == ID_AQ_U6){
    if (ch == 1){
      eletrodo = 2;
    }
    else if (ch==2){
      eletrodo = 6;
    }
  }
  Serial.print(" E");
  Serial.print(eletrodo);
}



//Funcao para solicitar a resposta de um periférico e um canal com relacao aos valores de tensão medidos

void resposta(int ID){
  typedef union {
    float floatingPoint;
    byte binary[4];
  } binaryFloat;

  binaryFloat amplitude[2];

  if ((ID == 0x05)||(ID == 0x07)||(ID == 0x08)||(ID == 0x09)){
          Wire.requestFrom(ID, 9);
          int idx = 0; 
          int cont = 0;
          while(Wire.available()) {
            //Serial.print("Perif. ");         // Print ]
            //Serial.print(ID);       // Print 
            //Serial.print("; canal ");       // Print
             
            if (cont == 0){
              byte c = Wire.read();           // Receive a byte 
              //Serial.print(c);                // Print
              localizaeletrodo(ID,c);
              cont = cont +1;
            }
            
            while (idx < 2 && cont>0) {
              for (byte idy = 0; idy < 4; idy++) {
                amplitude[idx].binary[idy] = Wire.read();
              }
              idx++;
            }
            Serial.print(" "); 
            Serial.print(amplitude[0].floatingPoint,4); 
            Serial.print(" "); 
            Serial.print(amplitude[1].floatingPoint,4); 
          }
   }
   else {
          Wire.requestFrom(ID, 3);
          while(Wire.available()) {
            int c = Wire.read();    // Receive a byte as character
            Serial.print(c);         // Print the character
            Serial.print(",");         // Print the character
          }
   }
}

// Funcoes para solicitar a medicao para cada um dos eletrodos

void medir_E0 (){
   Wire.beginTransmission(ID_AQ_U4);
   Wire.write(3);              
   Wire.endTransmission();
}
void medir_E1 (){
   Wire.beginTransmission(ID_AQ_U1);
   Wire.write(3);              
   Wire.endTransmission();
}
void medir_E2 (){
   Wire.beginTransmission(ID_AQ_U6);
   Wire.write(3);              
   Wire.endTransmission();
}
void medir_E3 (){
   Wire.beginTransmission(ID_AQ_U5);
   Wire.write(3);              
   Wire.endTransmission();
}
void medir_E4 (){
   Wire.beginTransmission(ID_AQ_U4);
   Wire.write(8);              
   Wire.endTransmission();
}
void medir_E5 (){
   Wire.beginTransmission(ID_AQ_U1);
   Wire.write(8);              
   Wire.endTransmission();
}
void medir_E6 (){
   Wire.beginTransmission(ID_AQ_U6);
   Wire.write(8);              
   Wire.endTransmission();
}
void medir_E7 (){
   Wire.beginTransmission(ID_AQ_U5);
   Wire.write(8);              
   Wire.endTransmission();
}





// Funcoes para solicitar a o resultado da medição para cada um dos eletrodos

void retornar_E0 (){
   Wire.beginTransmission(ID_AQ_U4);
   Wire.write(13);              
   Wire.endTransmission();
   resposta(ID_AQ_U4);
}
void retornar_E1 (){
   Wire.beginTransmission(ID_AQ_U1);
   Wire.write(13);              
   Wire.endTransmission();
   resposta(ID_AQ_U1);
}
void retornar_E2 (){
   Wire.beginTransmission(ID_AQ_U6);
   Wire.write(13);              
   Wire.endTransmission();
   resposta(ID_AQ_U6);
}
void retornar_E3 (){
   Wire.beginTransmission(ID_AQ_U5);
   Wire.write(13);              
   Wire.endTransmission();
   resposta(ID_AQ_U5);
}
void retornar_E4 (){
   Wire.beginTransmission(ID_AQ_U4);
   Wire.write(18);              
   Wire.endTransmission();
   resposta(ID_AQ_U4);
}
void retornar_E5 (){
   Wire.beginTransmission(ID_AQ_U1);
   Wire.write(18);              
   Wire.endTransmission();
   resposta(ID_AQ_U1);
}
void retornar_E6 (){
   Wire.beginTransmission(ID_AQ_U6);
   Wire.write(18);              
   Wire.endTransmission();
   resposta(ID_AQ_U6);
}
void retornar_E7 (){
   Wire.beginTransmission(ID_AQ_U5);
   Wire.write(18);              
   Wire.endTransmission();
   resposta(ID_AQ_U5);
}

// Funcao que envia o comando para retornar o valor medido por todos os eletrodos

void retornar_todos(){
  retornar_E0();
  retornar_E1();
  retornar_E2();
  retornar_E3();
  retornar_E4();
  retornar_E5();
  retornar_E6();
  retornar_E7();
}

// Funcao que envia o comando para medir o valor por todos os eletrodos

void medir_todos(){
  Serial.println("I");
  delay(100);
  medir_E0();
  delay(100);
  medir_E1();
  delay(100);
  medir_E2();
  delay(100);
  medir_E3();
  delay(100);
  medir_E4();
  delay(100);
  medir_E5();
  delay(100);
  medir_E6();
  delay(100);
  medir_E7();
  delay(100);
  Serial.println("F");
}


void troca_frequencia_demodulacao(byte freq1, byte freq2){
  freq1 = freq1-44;
  freq2 = freq2-66;
  
  
  Wire.beginTransmission(ID_AQ_U1);
  Wire.write(freq1);              
  Wire.endTransmission();
  Serial.print("Enviado o comando para AQ_U1: ");
  Serial.println(freq1);

  Wire.beginTransmission(ID_AQ_U4);
  Wire.write(freq1);              
  Wire.endTransmission();
  Serial.print("Enviado o comando para AQ_U5: ");
  Serial.println(freq1);


  Wire.beginTransmission(ID_AQ_U5);
  Wire.write(freq1);              
  Wire.endTransmission();
  Serial.print("Enviado o comando para AQ_U5: ");
  Serial.println(freq1);

  Wire.beginTransmission(ID_AQ_U6);
  Wire.write(freq1);              
  Wire.endTransmission();
  Serial.print("Enviado o comando para AQ_U6: ");
  Serial.println(freq1);

  Wire.beginTransmission(ID_AQ_U1);
  Wire.write(freq2);              
  Wire.endTransmission();
  Serial.print("Enviado o comando para AQ_U1: ");
  Serial.println(freq2);

  Wire.beginTransmission(ID_AQ_U4);
  Wire.write(freq2);              
  Wire.endTransmission();
  Serial.print("Enviado o comando para AQ_U5: ");
  Serial.println(freq2);


  Wire.beginTransmission(ID_AQ_U5);
  Wire.write(freq2);              
  Wire.endTransmission();
  Serial.print("Enviado o comando para AQ_U5: ");
  Serial.println(freq2);

  Wire.beginTransmission(ID_AQ_U6);
  Wire.write(freq2);              
  Wire.endTransmission();
  Serial.print("Enviado o comando para AQ_U6: ");
  Serial.println(freq2);
  
}


// Funcao que seleciona as frequências de cada um dos geradores e altera o valor da frequência que será utilizada para realização da FFT na placa de aquisicao

void seleciona_2_freq(byte freq1, byte freq2){
   Wire.beginTransmission(ID_MULT);
   Wire.write(freq2);              
   Wire.endTransmission();
   Serial.print("Enviado o comando para freq2 ");
   Serial.println(freq2);
   delay(300);
   troca_frequencia_demodulacao(freq1,freq2);
   // Esse delay entre alteracao de freq testei com 300 e funcionou, com 250 ja eh necessario enviar duas vezes o mesmo comando
   Wire.beginTransmission(ID_MULT);
   Wire.write(freq1);              
   Wire.endTransmission();
   Serial.print("Enviado o comando para freq1 ");
   Serial.println(freq1);   
}

void controla_injecao(int in1, int in2, int delayy){
  Wire.beginTransmission(ID_DEMUX);
  Wire.write(in1);              
  Wire.endTransmission();
  delay(delayy);
  Wire.beginTransmission(ID_DEMUX);
  Wire.write(in2);              
  Wire.endTransmission();
  delay(delayy);
}

void aquisicao_completa(int delayy, int mydelay2){ //delayy eh o atraso entre trocar os canais de aquisicao e o mydelay2 eh o atraso para enviar os comandos para o multiplexador 
  controla_injecao(I_E1,O_E0,mydelay2);
  #ifdef DEBUG1
     Serial.println();
     Serial.println("E1 I1 e E0 Terra");
  #endif 
  medir_todos();
  retornar_todos();
  delay(delayy);
        
  controla_injecao(I_E2,O_E1,mydelay2);
  #ifdef DEBUG1
     Serial.println();
     Serial.println("E2 I1 e E1 Terra");
  #endif 
  medir_todos();
  retornar_todos();
  delay(delayy);
        
  controla_injecao(I_E3,O_E2,mydelay2);
  #ifdef DEBUG1
    Serial.println();
    Serial.println("E3 I1 e E2 Terra");
  #endif 
  medir_todos();
  retornar_todos();
  delay(delayy);

  
  controla_injecao(I_E4,O_E3,mydelay2);
  #ifdef DEBUG1
    Serial.println();
    Serial.println("E4 I1 e E3 Terra");
  #endif 
  medir_todos();
  retornar_todos();
  delay(delayy);

  controla_injecao(I_E5,O_E4,mydelay2);
  #ifdef DEBUG1
    Serial.println();
    Serial.println("E5 I1 e E4 Terra");
  #endif 
  medir_todos();
  retornar_todos();
  delay(delayy);

  controla_injecao(I_E6,O_E5,mydelay2);
  #ifdef DEBUG1
    Serial.println();
    Serial.println("E6 I1 e E5 Terra");
  #endif 
  medir_todos();
  retornar_todos();
  delay(delayy);

  controla_injecao(I_E7,O_E6,mydelay2);
  #ifdef DEBUG1
    Serial.println();
    Serial.println("E7 I1 e E6 Terra");
  #endif 
  medir_todos();
  retornar_todos();
  delay(delayy);
  
  controla_injecao(I_E0,O_E7,mydelay2);
  #ifdef DEBUG1
    Serial.println();
    Serial.println("E0 I1 e E7 Terra");
  #endif 
  medir_todos();
  retornar_todos();
  delay(delayy);
}
