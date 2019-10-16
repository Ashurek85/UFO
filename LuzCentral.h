#include <FastLED.h>
#include <Wire.h>

#define DATA_PIN_LEDS_CENTRAL 9

#define NUM_LEDS_CENTRAL 6

#define MIN_BRILLO 0
#define MAX_BRILLO 255

class LuzCentral
{
  
  private:
  CRGB ledsCentral[NUM_LEDS_CENTRAL];
  
  public:
  LuzCentral(int brilloInicial);
  
  void Encender();
  void Apagar();
    
  void CambiarBrillo(int nuevoBrillo);
};
