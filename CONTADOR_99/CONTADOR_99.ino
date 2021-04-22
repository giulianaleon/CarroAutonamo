//Giuliana Leon - ATIVIDADE DISPLAY - CONTADOR DE 0 A 99

volatile long counter = 0;
volatile long counterDireita = 0;
volatile long counterEsquerda = 0;
int ctrl_timer1;
int ctrl_timer2;

int digitoEsquerda[10][7]= {           //Matriz para controlar os segmentos    LOW = 1 APAGA     HIGH = 0 ACENDE
  {0,0,0,0,0,0,1},  //0
  {1,0,0,1,1,1,1},  //1
  {0,0,1,0,0,1,0},  //2
  {0,0,0,0,1,1,0},  //3
  {1,0,0,1,1,0,0},  //4
  {0,1,0,0,1,0,0},  //5
  {0,1,0,0,0,0,0},  //6
  {0,0,0,1,1,1,1},  //7
  {0,0,0,0,0,0,0},  //8
  {0,0,0,1,1,0,0},  //9
};

int digitoDireita[10][7]= {           //Matriz para controlar os segmentos     LOW = 0 APAGA     HIGH = 1 ACENDE   CATODO
  {0,0,0,0,0,0,1},  //0
  {1,0,0,1,1,1,1},  //1
  {0,0,1,0,0,1,0},  //2
  {0,0,0,0,1,1,0},  //3
  {1,0,0,1,1,0,0},  //4
  {0,1,0,0,1,0,0},  //5
  {0,1,0,0,0,0,0},  //6
  {0,0,0,1,1,1,1},  //7
  {0,0,0,0,0,0,0},  //8
  {0,0,0,1,1,0,0},  //9
};


void setup() {
  
  pinMode(38, OUTPUT); //a_esq
  pinMode(40, OUTPUT); //b_esq
  pinMode(42, OUTPUT); //c_esq
  pinMode(44, OUTPUT); //d_esq
  pinMode(46, OUTPUT); //e_esq
  pinMode(48, OUTPUT); //f_esq
  pinMode(50, OUTPUT); //g_esq

  pinMode(5, OUTPUT); //a_dir
  pinMode(6, OUTPUT); //b_dir
  pinMode(7, OUTPUT); //c_dir
  pinMode(8, OUTPUT); //d_dir
  pinMode(9, OUTPUT); //e_dir
  pinMode(10, OUTPUT); //f_dir
  pinMode(11, OUTPUT); //g_dir

  //TIMER 1 OVERFLOW 
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 |= (1 << TOIE1);
  TCCR1B = 1;
  TCNT1 = 0;

  //TIMER 2 OVERFLOW
  TCCR2A = 0;
  TCCR2B = 7;
  TCNT2 = 0;        //registrador de contagem
  TIMSK2 = 1;       //habilita interrupçao do timer2

}

void letraEsquerda (int n){                           //Função para mostrar o digito solicitado
  
  int let = 0;
  int pin = 38;
  
  for(let = 0 ; let < 7 ; let++){                     //Percorrendo o array para ligar os segmentos correspondentes ao digito
    digitalWrite(pin ,digitoEsquerda[n][let]);
    pin = pin + 2;
  }
}

void letraDireita (int n){      //Função para mostrar o digito solicitado
  
  int let = 0;
  int pin2 = 5;
  
  for(let = 0 ; let < 7 ; let++){            //Percorrendo o array para ligar os segmentos correspondentes ao digito
    digitalWrite(pin2 ,digitoDireita[n][let]);
    ++pin2;
  }
}

void loop() {
}

ISR (TIMER1_OVF_vect){                                              //PERIOCIDADE DE ATUALIZAÇÃO DO DISPLAY (VALOR QUE SERÁ APRESENTADO)
  
  ctrl_timer1++;

  if(ctrl_timer1 == 245){                                                 //1 segundo
    if(counterDireita == 9){                                                //10  20  30  40  50  60  70  80  90  
    counterEsquerda++;
    counterDireita = 0;
  }else{
    counterDireita++;
  }
  if(counterEsquerda == 9 && counterDireita == 9){                                  //Quando chegar em 99 
    counterEsquerda = 0;
    counterDireita = 0;
  }
   ctrl_timer1 = 0; 
  }
  
  TCNT1 = 0;  
}

ISR (TIMER2_OVF_vect){                                  //PERIOCIDADE QUE O LED PISCA (APRESENTAÇÃO DO VALOR NO DISPLAY)

  TCNT2 = 0;
  ctrl_timer2++;

  if(ctrl_timer2 == 50){
    letraEsquerda(counterEsquerda);
    letraDireita(counterDireita);
    ctrl_timer2 = 0;
  }
}
