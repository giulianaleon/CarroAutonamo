//Giuliana Leon - 161151191 - Projeto Supervisionado 2

#include <Ultrasonic.h>
#include <Servo.h>

  const int motorA1 = 9;                 //ESQUERDA
  const int motorA2 = 3;
  const int motorB1 = 11;               //DIREITA
  const int motorB2 = 10;
  const int trig = 41;                  //SENSOR
  const int echo = 43;                  //SENSOR

  Ultrasonic ultrasonic(trig,echo);       //Objeto criado para controlar o sensor ultrassonico
  Servo servoSensor;                      //Objeto criado para controlar o servo motor

  float distanciaD;
  float distanciaE;
  float distancia;

void setup() { 
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  servoSensor.attach(45); 
}

int Obstaculo (void){
  float cm;
  long micro;
  micro = ultrasonic.timing();
  cm = ultrasonic.convert(micro, Ultrasonic::CM);
  return cm;
}

void loop() {
  delay(100);                            //Assim o sensor não gira no primeiro momento 
  distancia = Obstaculo();                //Mede a distancia
  delay(10);
  if(distancia >= 20){                  //Se a distancia for maior que 15
    frente();
  }else  {                              //Se a distancia for menor que 15
    parar();  
    servoSensor.write(180);
    delay(500);
    distanciaE = Obstaculo();
    delay(500);
    servoSensor.write(0);
    delay (500);
    distanciaD = Obstaculo();
    delay(200);
    servoSensor.write(90);
    if(distanciaD > distanciaE){
      direita();
      parar();
      frente();
    }else{
      esquerda();
      parar();
      frente();
    }
  }
}

void frente(){
  digitalWrite(motorA1, LOW);              //TRAS A
  analogWrite(motorA2, 200);               //FRENTE A
  digitalWrite(motorB1, LOW);              //TRAS B
  analogWrite(motorB2, 250);               //FRENTE B
}
void parar(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
  delay(400);
}
void esquerda(){
  analogWrite(motorA1, 250);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
  delay(400);
}
void direita(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  analogWrite(motorB1, 230);
  digitalWrite(motorB2,LOW);
  delay(400);
}
