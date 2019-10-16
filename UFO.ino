/* BIBLIOTECAS NECESARIAS:
 *  FastLed by Daniel Garcia
 *  RTClib by Adafruit
 */

#include <Wire.h>
#include "RTClib.h"
#include "AnilloLed.h"

#define PIN_POTENCIOMETRO 18 // A0

/* CONFIGURACION PRO MICRO
 * PIN LEDS ANILLO: 10
 * PIN LEDS CENTRAL: 18
 * PIN POTENCIOMETRO: 8
 *  
 * SDA: PIN 2
 * SCL: PIN 3
 */

RTC_DS3231 rtc;
AnilloLed *anilloLed;

CRGB leds[24];

void setup() 
{
  Serial.begin(9600);          // configuración serie
  
  delay(1500);

  anilloLed = new AnilloLed(255); // Brillo inicial al máximo

 
  // Inicialización del rtc
  if (!rtc.begin()) 
  {
    while(true)
    {
      Serial.println("¡No se ha encontrado el RTC!");
      delay(2000);
    }
  } 

  // Se pone en hora. Solo sería necesario ejecutarlo una vez hasta que se le acabe la pila
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  anilloLed->Encender();
}

void loop() 
{    
  
  int brillo = map(analogRead(PIN_POTENCIOMETRO), 0, 1023, 0, 255); // Se mapea a 256 valores  
  anilloLed->CambiarBrillo(brillo);
  
  DateTime now = rtc.now();
  //printDate(now);
  //Serial.print(now.hour());
  if (now.second() == 0 && now.minute() == 0 && anilloLed->ObtenerEstado() == EstadoEjecucion::On)
  {
    // Lanzar animación
    int numGiros = now.hour();
    if(numGiros > 12)
      numGiros = numGiros - 12;
    anilloLed->LanzarAnimacion(12,numGiros);
  }
  else
  {
    //Serial.println("Actualizar");
    anilloLed->Actualizar();
  }
  //printDate(now);
  
  FastLED.show();
  delay(50);
}


void printDate(DateTime date)
{   
   Serial.print(date.hour(), DEC);
   Serial.print(':');
   Serial.print(date.minute(), DEC);
   Serial.print(':');
   Serial.print(date.second(), DEC);
   Serial.println();
}
