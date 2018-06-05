#include <Bounce2.h>
#include "rele.cpp";
#include "sensor_umi_solo.cpp";

#define PIN_SOLENOIDE1 2 // Solenoide da caixa
#define NIVEL_LOGICO_RELE_SOLENOIDE1 LOW

#define PIN_BOMBA 3 // Solenoide da bomba
#define NIVEL_LOGICO_RELE_BOMBA LOW

#define SENSOR_UMI_SOLO1 A1

#define SMS_VCC 7
#define SMS_GND 6

#define VALOR_SOLO_SECO 35

Rele solenoide_caixa(PIN_SOLENOIDE1, NIVEL_LOGICO_RELE_SOLENOIDE1);
Rele bomba(PIN_BOMBA, NIVEL_LOGICO_RELE_BOMBA);

Solo solo1(SENSOR_UMI_SOLO1, SMS_VCC, SMS_GND);

Solo sensores_solo[] = { solo1 };

#define QUANT_SENSORES_SOLO 1

#define TEMPO_ENCHARCAMENTO 3000
#define TEMPO_DRENAGEM 3000
 
Bounce debouncer = Bounce();

int lerSensores(int);
boolean verificarBoia();
 
void setup() {
  pinMode(SMS_VCC, OUTPUT);
  pinMode(SMS_GND, OUTPUT); 
  pinMode(SENSOR_UMI_SOLO1, INPUT);
  pinMode(PIN_SOLENOIDE1, OUTPUT);
  pinMode(PIN_BOMBA, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(8, INPUT_PULLUP); // Configura pino 8 como entrada e habilita pull up interno;
  debouncer.attach(8); // Informa que o tratamento de debouce será feito no pino 8;
  debouncer.interval(10); // Seta o intervalo de trepidação;
  Serial.begin(9600);
}
 
void loop() {

  solenoide_caixa.desligar();
  bomba.desligar();
  
  int valor = lerSensores(QUANT_SENSORES_SOLO); 
  Serial.println(valor);
  
  if (valor < VALOR_SOLO_SECO) {
    solenoide_caixa.desligar();
    bomba.ligar();
    boolean boia = false;
    while (boia == false) {
       boia = verificarBoia();
       delay(100);
    }
    bomba.desligar();
    delay(TEMPO_ENCHARCAMENTO);
    solenoide_caixa.ligar();
    delay(TEMPO_DRENAGEM);
  }
  
  delay(50);
}

boolean verificarBoia() {
  debouncer.update();
  int valor = debouncer.read();
  if (valor == HIGH) {
    return false;
  } 
  else {
    return true;
  }
}

int lerSensores(int quant_sensores) {
  int soma = 0;
  for (int i = 0; i < quant_sensores; i++) {
    soma += sensores_solo[i].ler();
  }
  return soma / quant_sensores;
}
