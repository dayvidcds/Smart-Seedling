#include <Arduino.h>

class MULT4051 {
  private:
    unsigned char analogPin; // Guarda o pino em que o Sensor estará conectado (Usar entradas analógicas)
    unsigned char A;
    unsigned char B;
    unsigned char C;
    unsigned char vcc;
    unsigned char gnd;
    unsigned char valor;
   public:
    MULT4051(const unsigned char pin, const unsigned char A, const unsigned char B, const unsigned char C, unsigned char vcc, unsigned char gnd) { // Construtor, Método iniciado quando se cria a variável (Objeto)
      this->analogPin = pin; // Setando variável pin
      this->vcc = vcc;
      this->gnd = gnd;
      this->A = A;
      this->B = B;
      this->C = C;
    }
    int ler(boolean A, boolean B, boolean C) {
      int anaValue;
      digitalWrite(this->A, C);
      digitalWrite(this->B, B);
      digitalWrite(this->C, A);
      digitalWrite(this->vcc, LOW);
      digitalWrite(this->gnd, HIGH);
      delay(1000);
      anaValue = analogRead(this->analogPin);
      digitalWrite(this->vcc, HIGH);
      digitalWrite(this->gnd, LOW);
      delay(1000);
      digitalWrite(this->vcc, LOW);
      anaValue = map(anaValue, 1023, 0, 0, 100);
      this->valor = anaValue;
      return anaValue;
    }
    unsigned char getValor() {
      return this->valor;
    }
};
