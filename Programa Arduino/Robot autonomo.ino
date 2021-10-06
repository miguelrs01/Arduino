#include <SoftwareSerial.h>
SoftwareSerial miBT(2,3);
int motorderatras = 6;
int motorderadel = 5;
int motorizqdel = 8;
int motorizqdet = 7;

int luces = 4;

const int sensorIR = 9; //sensor IR frontal pin 9
const int finCizq = 11; //final de carrera izquierdo 10
const int finCder = 10; //final de carrera derecho 11

int valueIR;
int valueizq;
int valueder;
long time;

char leer = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  miBT.begin(9600);
  Serial.println("HOLA!");

  pinMode(motorderatras, OUTPUT);
  pinMode(motorderadel, OUTPUT);
  pinMode(motorizqdet, OUTPUT);
  pinMode(motorizqdel, OUTPUT);
  pinMode(luces, OUTPUT);

    //inicializo inputs
  pinMode(finCizq, INPUT_PULLUP);
  pinMode(finCder, INPUT_PULLUP);
  pinMode(sensorIR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(miBT.available()>0){
    leer = miBT.read();
    switch(leer) {
      case 'B':
        //digitalWrite(motorderadel, HIGH);
        digitalWrite(motorderatras, HIGH);
        digitalWrite(motorizqdet, HIGH);
        digitalWrite(motorizqdel, LOW);
        digitalWrite(motorderadel, LOW);
        break;
      case 'F':
        digitalWrite(motorizqdel, HIGH);
        digitalWrite(motorderadel, HIGH);
        digitalWrite(motorderatras, LOW);
        digitalWrite(motorizqdet, LOW);
        break;
      case 'L':
        digitalWrite(motorizqdet, LOW);
        digitalWrite(motorderadel, LOW);
        digitalWrite(motorizqdel, HIGH);
        digitalWrite(motorderatras, HIGH);
      break;
      case 'R':
        digitalWrite(motorizqdel, LOW);
        digitalWrite(motorderatras, LOW);
        digitalWrite(motorderadel, HIGH);
        digitalWrite(motorizqdet, HIGH);
      break;
      case 'S':
        digitalWrite(motorizqdel, LOW);
        digitalWrite(motorderatras, LOW);
        digitalWrite(motorizqdet, LOW);
        digitalWrite(motorderadel, LOW);
      break;
      case 'W':
        digitalWrite(luces, HIGH);
      break;
      case 'w':
        digitalWrite(luces,LOW);
      break; 
      case 'P':
         valueIR = digitalRead(sensorIR);
         Serial.print(valueIR);
         valueizq = digitalRead(finCizq);
         Serial.print(valueizq);
         valueder = digitalRead(finCder);
         Serial.print(valueder);
         if(valueizq == 0 || valueder == 0 ||valueIR == 1) {
          Serial.print("me choco");
          time = millis() + random(10)*200;
          while(millis() > time){
            digitalWrite(motorderatras, HIGH);
            digitalWrite(motorizqdet, HIGH);
            digitalWrite(motorizqdel, LOW);
            digitalWrite(motorderadel, LOW);
            } 
           if(valueizq==0) {
            time = millis() + random(10)*200;
            while(millis() > time){
              digitalWrite(motorizqdel, LOW);
              digitalWrite(motorderatras, LOW);
              digitalWrite(motorderadel, HIGH);
              digitalWrite(motorizqdet, HIGH);
              }
            }
            else if(valueder==0) {
              time = millis() + random(10)*200;
              while(millis() > time){
                digitalWrite(motorizqdet, LOW);
                digitalWrite(motorderadel, LOW);
                digitalWrite(motorizqdel, HIGH);
                digitalWrite(motorderatras, HIGH);
              }
             } else {
              int z = random(1);
              if (z == 0){
                time = millis() + random(1)*500;
                while(millis() > time){
                  //gira a la derecha para no volver a chocar
                  digitalWrite(motorizqdel, LOW);
                  digitalWrite(motorderatras, LOW);
                  digitalWrite(motorderadel, HIGH);
                  digitalWrite(motorizqdet, HIGH);
                }
              } else if (z==1){
                time = millis() + random(1)*500;
                while(millis() > time){
                  //gira a la izquierda para no volver a chocar
                  digitalWrite(motorizqdet, LOW);
                  digitalWrite(motorderadel, LOW);
                  digitalWrite(motorizqdel, HIGH);
                  digitalWrite(motorderatras, HIGH);
                }
              }
            }
          
         } else {
          Serial.print("Sigo recto");
          //mientras no detecte objetos hacia delante
          digitalWrite(motorizqdel, HIGH);
          digitalWrite(motorderadel, HIGH);
          digitalWrite(motorderatras, LOW);
          digitalWrite(motorizqdet, LOW);
        } 
        break; 
  }
  }
}
