/*************************************************************************
* File Name          : ejemploClase.ino
* Author             : Pacual Arroyo
* Updated            : Pascual Arroyo
* Version            : V1.0.0
* Date               : 28/04/2014
* Description        : Control del robot mediante mando IR.
* License            : CC-BY-SA 3.0
**************************************************************************/



#include <Me_BaseShield.h> //Librerias Makeblock Base
#include <SoftwareSerial.h> //comunicacion
#include <Me_InfraredReceiverDecode.h> //libreria para el uso de IR
#include <Me_BaseShieldMotorDriver.h>  //libreria para el manejo de motores

Me_BaseShieldMotorDriver baseShieldMotorDriver; //Inicializacion de los motores en los puertos base de motores
Me_InfraredReceiverDecode infraredReceiverDecode(PORT_3); //Inicializacion del sensor de infrarojos en el puerto 3

//Definimos la velocidad de los motores
int velocidadRuedaIzquierda = 200;
int velocidadRuedaDerecha = 200;


void setup()
{
    Serial.begin(9600);//Establecemos comunicacion con el puerto serie para utlizar la consola
    
    baseShieldMotorDriver.begin(); //Inicializamos los motores
    infraredReceiverDecode.begin(); //Inicializamos los infrarojos
}

void loop()
{
    if(infraredReceiverDecode.available()) //Si se recibe algun dato por el puerto de infrarojos
    {
        switch(infraredReceiverDecode.read()) //lo leemos y segun cual sea se realizara un movimiento u otro
        {
            case IR_BUTTON_PLUS: 
                 avanzar();
                 while(infraredReceiverDecode.buttonState());
                 parar();
                 break;
            case IR_BUTTON_PREVIOUS: 
                 girarIzquierda();
                 while(infraredReceiverDecode.buttonState());
                 parar();
                 break;
            case IR_BUTTON_NEXT: 
                 girarDerecha();
                 while(infraredReceiverDecode.buttonState());
                 parar();
                 break;
            case IR_BUTTON_MINUS: 
                 retroceder();
                 while(infraredReceiverDecode.buttonState());
                 parar();
                 break;
            default:break;
        }
    }
}

void avanzar()
{
    Serial.println("avanzar");
    baseShieldMotorDriver.runMotors(velocidadRuedaIzquierda,velocidadRuedaDerecha);
}

void girarIzquierda()
{
    Serial.println("Girar Izquierda");
    baseShieldMotorDriver.runMotors(velocidadRuedaIzquierda,-velocidadRuedaDerecha);
}
void girarDerecha()
{
    Serial.println("Girar Derecha");
    baseShieldMotorDriver.runMotors(-velocidadRuedaIzquierda,velocidadRuedaDerecha);
}
void parar()
{
    Serial.println("Parar");
    baseShieldMotorDriver.stopMotors();
}
void retroceder()
{
    Serial.println("Retroceder");
    baseShieldMotorDriver.runMotors(-velocidadRuedaIzquierda,-velocidadRuedaDerecha);
}

