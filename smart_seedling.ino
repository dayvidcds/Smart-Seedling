#include <Bounce2.h>
#include "rele.cpp";
#include "sensor_umi_solo.cpp";
#include "MULT4051.cpp"

#define PIN_SOLENOIDE1 2 // Solenoide da caixa
#define NIVEL_LOGICO_RELE_SOLENOIDE1 LOW

#define PIN_BOMBA 3 // Solenoide da bomba
#define NIVEL_LOGICO_RELE_BOMBA LOW

#define SENSORES_UMI_SOLO A0

#define SMS_VCC 7
#define SMS_GND 6

#define VALOR_SOLO_SECO 35

Rele solenoide_caixa(PIN_SOLENOIDE1, NIVEL_LOGICO_RELE_SOLENOIDE1);
Rele bomba(PIN_BOMBA, NIVEL_LOGICO_RELE_BOMBA);

MULT4051 sensores_solo(SENSORES_UMI_SOLO, 9, 10, 11, SMS_VCC, SMS_GND);

#define QUANT_SENSORES_SOLO 1

#define TEMPO_ESPERA 3000
 
Bounce debouncer = Bounce();

int lerSensores(int);
boolean verificarBoia();
 
void setup() {
  pinMode(SMS_VCC, OUTPUT);
  pinMode(SMS_GND, OUTPUT); 
  pinMode(SENSORES_UMI_SOLO, INPUT);
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
  int valor = lerSensores(QUANT_SENSORES_SOLO); 
  Serial.println(valor);
  solenoide_caixa.desligar();
  bomba.desligar();
  
  if (valor < VALOR_SOLO_SECO) {
    solenoide_caixa.desligar();
    bomba.ligar();
    boolean boia = false;
    while (boia == false) {
       boia = verificarBoia();
       delay(100);
    }
    bomba.desligar();
    delay(TEMPO_ESPERA);
    solenoide_caixa.ligar();
    delay(TEMPO_ESPERA);
  }
  
  delay(100);
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
    soma += sensores_solo.ler(false, false, true);
  }
  return soma / quant_sensores;
}

