//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                              //
//                           PROJETO:  CONTROLADOR VIA BLUETOOTH                                                //
//                                     PARA CHASSIS MECANICO COM DUAS RODAS, QUATRO RODAS                       //
//                                     OU PLATAFORMA ROBOTICA ROVER 5                                           //
//                                                                                                              //
//                          FEITO POR: YURI E EMERSON                                                           //
//                                                                                                              //  
//                          APLICATIVOS:                                                                        //
//                            ANDROID  -   ARDUINO BT JOYSTICK                                                  //       
//                               IOS   -   ATECBOT                                                              //  
//                                                                                                              //  
//                                                                                                              //
//                                                                                                              //
//                                                                                                              //
//                                                                                                              //
//  DUVIDAS OU SUGESTÕES, ACESSE    https://www.facebook.com/OlidoMakerClub/                                    //  
//                                  https://www.facebook.com/mamuteeletronica/                                  //
//                                                                                                           .  //
//                                                                                                          . . //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////// CONFIGURAÇÃO DO BLUETOOTH ///////////////////////////////

#include <SoftwareSerial.h>      // Inclui a Biblioteca de Comunicação Serial

//                       RX, TX         
SoftwareSerial Bluetooth(11, 12);    //  Ligar o TX do Modulo Bluetooth no RX (11) e o RX do Modulo no TX (12)      

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


                     // Variavel Que Seleciona a Versão do Aplicativo 
byte Sistema = 0;    // Use "= 0" Para usar o Aplicativo Android e "= 1" Para o Aplicativo de IOS 
                     // Lembrando que os Modulos Bluetooth Para Android e Iphone são Diferentes 
                     // Para Android Use o Modulo HC-05 ou HC-06
                     // Para IOS Use Um Modulo "BLE 4.0" HM-10 ou HC-08  




///////////////////////////////////// DEFINE AS VARIAVEIS DE CONTROLE DA PONTE H /////////////////////////////////

#define IN1 7             //   { Motor                         // Pino 22 no Mega
#define IN2 8             //   Esquerda}                       // Pino 23 no Mega 
#define IN3 9             //   { Motor                         // Pino 24 no Mega
#define IN4 10            //     Direita}                      // Pino 25 no Mega
#define ENA_D 5           //    Enable Motor Direita   (ENA)   // Pino 2 no Mega
#define ENA_E 6           //    Enable Motor Esquerda  (ENB)   // Pino 3 no Mega
int Velocidade = 255;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


char val;        // Variavel que Salva os Valores Lidos Por Bluetooth



void setup() 
{

///////////////////////////INICIALIZAÇÃO DOS PINOS DA PONTE H COMO SAIDA //////////////////////////////////////////  
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);
 pinMode(ENA_D, OUTPUT);
 pinMode(ENA_E, OUTPUT);
 analogWrite(ENA_D, Velocidade);
 analogWrite(ENA_E, Velocidade);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  
  Serial.begin(9600);         // Inicia a Comunicação Serial

  Bluetooth.begin(9600);      // Inicia a Comunicação Serial com o Modulo Bluetooth 
  
 
}




//////////////////////////////////////// FUNÇÕES DO CONTROLE DE DIREÇÃO DOS MOTORES /////////////////////////////////////////////////


void Parado()
{
 digitalWrite(IN1, HIGH);     // { Motor Direita 
 digitalWrite(IN2, HIGH);     //     Freio }
 digitalWrite(IN3, HIGH);     // { Motor Esquerda 
 digitalWrite(IN4, HIGH);     //     Freio }
}


void Frente()
{
 digitalWrite(IN1, HIGH);    // { Motor Direita 
 digitalWrite(IN2, LOW);     //      Frente }
 digitalWrite(IN3, HIGH);    // { Motor Esquerda 
 digitalWrite(IN4, LOW);     //      Frente }
}

void Re()
{
 digitalWrite(IN1, LOW);     //  { Motor Direita 
 digitalWrite(IN2, HIGH);    //          Ré }
 digitalWrite(IN3, LOW);     //  { Motor Esquerda 
 digitalWrite(IN4, HIGH);    //          Ré }
}


void Esquerda()
{
 digitalWrite(IN1, LOW);     // { Motor Direita 
 digitalWrite(IN2, HIGH);    //          Ré }
 digitalWrite(IN3, HIGH);    // { Motor Esquerda 
 digitalWrite(IN4, LOW);     //      Frente }
}

void Direita()
{
 digitalWrite(IN1, HIGH);    // { Motor Direita 
 digitalWrite(IN2, LOW);     //      Frente }
 digitalWrite(IN3, LOW);     // { Motor Esquerda 
 digitalWrite(IN4, HIGH);    //          Ré }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






//////////////////////////// FUNÇÕES DE CONTROLE DE VELOCIDADE //////////////////////////////

 void Velocidade_Menos()
  {
   if (Velocidade >= 1) // ou 10
   {
    Velocidade -= 1;        // ou 10
    analogWrite(ENA_D, Velocidade);
    analogWrite(ENA_E, Velocidade);             
    delay(10); 
   }  
  }
  
  
    void Velocidade_Mais()
  {
     if (Velocidade <= 254)
    {
     Velocidade += 1;      // ou 10
     analogWrite(ENA_D, Velocidade);
     analogWrite(ENA_E, Velocidade);              
     delay(10);  
    }
 
  }

/////////////////////////////////////////////////////////////////////////////////////////////////





 





////////////////////////////////////////////// FUNÇÃO DE COMUNICAÇÃO BLUETOOTH PARA ANDROID /////////////////////////////////////

void Android()
{
  if (Bluetooth.available()) 
  {
    val = Bluetooth.read();
  }
  
  if(val == '0')
  {
    Parado();
  }
      else if (val == '1')
      {
        Frente();
      }
      else if (val == '2')
      {
        Re();
      }
      else if (val == '3')
      {
        Esquerda();
      }
      else if (val == '4')
      {
        Direita();
      }
      
      else if (val == 'A')
      {
        Velocidade_Mais();
      }
       else if (val == '9')
      {
        Velocidade_Menos();
      }
 
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





//////////////////////////////// FUNÇÃO DE COMUNICAÇÃO BLUETOOTH PARA IOS /////////////////////////////////////////////////////



 void IOS() 
 {
  if (Bluetooth.available()) 
 {
    val = Bluetooth.read();
  }
  else
  {
    Parado();
  }
  
  if(val == '0')
  {
    Parado();
  }
      else if (val == '2')
      {
        Frente();
      }
      else if (val == '1')
      {
        Re();
      }
      else if (val == '4')
      {
        Esquerda();
      }
      else if (val == '3')
      {
        Direita();
      }
      
      else if (val == 'A')
      {
        Velocidade_Mais();
      }
       else if (val == '9')
      {
        Velocidade_Menos();
      }
       
    }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










void loop() 
{
 if (Sistema == 0)
 { 
  Android();
 }
  else if (Sistema == 1)
  {
    IOS();
  }


  Serial.println(val);     // Imprime na Serial os Comandos Recebidos Pelo Bluetooth
 





 
}
