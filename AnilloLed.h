#include <FastLED.h>
#include <Wire.h>
#include "RTClib.h"
#include "LuzCentral.h"

#define DATA_PIN_LEDS 10 

#define NUM_LEDS 24

#define MILLIS_POR_LED 100 // En el giro
#define DELTA_FADE 6 // En cada iteración el brillo se modificará en 6 unidades 

#define MIN_BRILLO 0
#define MAX_BRILLO 255

enum EstadoEjecucion {
  On,
  Off,
  Animando,
};

class AnilloLed
{
  
  private:
  int numLeds;
  CRGB leds[NUM_LEDS];
  int ledActual;
  int millisInicioAnimacion;
  EstadoEjecucion estado;  
  int brillo;
  LuzCentral* luzCentral;

  int brilloAntesAnimacion;
  int numeroFades; 
  int numeroTotalFades;
  int numeroGiros;
  int numeroTotalGiros;
  bool fadeDescendente;
  bool fadeInicialDescendente;
  bool etapaAnimandoConFade; 
  
  void EncenderSoloUnLed(int numLed);
  void CambiarBrilloAnimacion(int nuevoBrillo);
 

  public:
  AnilloLed(int brilloInicial);
  
  void Encender();
  void Apagar();
  
  bool LanzarAnimacion(int numFades, int numGiros);
  bool Actualizar();
  EstadoEjecucion ObtenerEstado();
  void CambiarBrillo(int nuevoBrillo);  

};
