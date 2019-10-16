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

/*
#define BRILLO_MAXIMO 255
#define BRILLO_MINIMO 50 // Por debajo de este valor se apagará

#define SEGUNDOS_PARA_ANIMACION 60 // Segundos que faltarán para la hora en punto con los que se iniciará el parpadeo
#define SEGUNDOSGIROLUZCOMPLETA 1 // Número de segundos que tardará el halo de luz en dar una vuelta completa

*/
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
/*
  

  bool animando; // Indica si la animación se ha iniciado. Puede estar en espera o girando
  bool girando;  // Estamos dentro de una animación pero ¿girando el halo de luz?
  int limiteAnimacion; // Tiempo máximo para la animación. Al llegar el numero de segundos parará
  int limiteParpadeoLed; // Tiempo que el numLedBrillando tiene para mantenerse iluminado
  int numLedBrillando; // Número del led que está brillando

  bool Animar(bool esperaDescendente, DateTime now);
  

  bool EsNecesarioLanzarAnimacion(DateTime now);


  public:
  AnilloLed();
  void Iluminar(int brillo, DateTime now);    
  */
};
