#include "LuzCentral.h"

LuzCentral::LuzCentral(int brilloInicial)
{
  FastLED.addLeds<WS2812B, DATA_PIN_LEDS_CENTRAL>(ledsCentral, NUM_LEDS_CENTRAL);    
  CambiarBrillo(brilloInicial);  
}

void LuzCentral::Apagar()
{
  Serial.println("apagar luz central");
  for (int cont=0;cont<NUM_LEDS_CENTRAL;cont++)
    ledsCentral[cont] = CRGB::Black;   
}

void LuzCentral::Encender()
{
  Serial.println("encender luz central");
  // Leds en azul
  for (int cont=0;cont<NUM_LEDS_CENTRAL;cont++)
    ledsCentral[cont] = CRGB::Blue;   
}

void LuzCentral::CambiarBrillo(int nuevoBrillo)
{
  FastLED.setBrightness(nuevoBrillo);
}
