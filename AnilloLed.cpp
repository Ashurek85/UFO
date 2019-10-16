#include "AnilloLed.h"

AnilloLed::AnilloLed(int brilloInicial)
{
  brillo = brilloInicial;
  FastLED.addLeds<WS2812B, DATA_PIN_LEDS>(leds, NUM_LEDS);  

  luzCentral = new LuzCentral(brilloInicial);
  
  ledActual = 0;
  millisInicioAnimacion = 0;
  brilloAntesAnimacion = 0;
  numeroFades = 0;
  numeroTotalFades = 5; // Valor por defecto
  numeroGiros = 0;
  numeroTotalGiros = 1; // Valor por defecto
  etapaAnimandoConFade = false;
  estado = EstadoEjecucion::On;
  CambiarBrillo(brillo);  
}

bool AnilloLed::LanzarAnimacion(int numFades, int numGiros)
{
  numeroTotalFades = numFades;
  numeroTotalGiros = numGiros;
  
  brilloAntesAnimacion = brillo; // Se almacena el brillo antes de modificarlo en la animación
  numeroFades = 0;
  numeroGiros = 0;
  etapaAnimandoConFade = true;
  fadeDescendente = true;
  fadeInicialDescendente = true;
  
  millisInicioAnimacion = millis();
  ledActual = 0;
  estado = EstadoEjecucion::Animando;
}

bool AnilloLed::Actualizar()
{
  switch(estado)
  {
    case EstadoEjecucion::Animando:
      // Etapa Fades
      if (numeroFades < numeroTotalFades)
      {
        // Si quedan fades por hacer ...
        if (fadeDescendente)
        {
          brillo = brillo - DELTA_FADE;
          if (brillo <= MIN_BRILLO)
          {
            // Final del fade descendente
            brillo = MIN_BRILLO;            
            fadeDescendente = false; // Ahora será ascendente
            if (fadeInicialDescendente == false)
            {
              // Ciclo completo, se incrementa el número de fades
              numeroFades = numeroFades + 1;
            }
          }          
        }
        else
        {
          brillo = brillo + DELTA_FADE;
          if (brillo >= MAX_BRILLO)
          {
            // Final del fade ascendente
            brillo = MAX_BRILLO;
            fadeDescendente = true; // Ahora será descendente
            if (fadeInicialDescendente == true)
            {
              // Ciclo completo, se incrementa el número de fades
              numeroFades = numeroFades + 1;
            }
          }
        }
        CambiarBrilloAnimacion(brillo); // Se cambia el brillo
      }
      else
      {
        // Etapa Giros
        if (numeroGiros < numeroTotalGiros)
        {
          int millisActuales = millis();
          if (millisActuales - millisInicioAnimacion > MILLIS_POR_LED)
          {
            // Paso al siguiente led
            if (ledActual == NUM_LEDS - 1)
            {
              // Fin del giro
              numeroGiros = numeroGiros + 1; 
              ledActual = 0; // Se reinicia
              if(numeroGiros < numeroTotalGiros) // En el último caso no se apaga para luego encender; genera un parpadeo feo
                luzCentral->Apagar();
            }
            else
            {
              ledActual = ledActual + 1;                          
              if(NUM_LEDS / 2 == ledActual )          
              {
                  luzCentral->Encender();
              }  
            }
            EncenderSoloUnLed(ledActual);
          }
        }
        else
        {
          // Fin de la animacion, se vuelve a encendido         
          //AnilloLed::CambiarBrilloAnimacion(brilloAntesAnimacion);
          Encender();          
        }
      }
    break;
  }
}

void AnilloLed::EncenderSoloUnLed(int numLed)
{
  for (int cont=0;cont<NUM_LEDS;cont++)
  {
    if (cont == numLed)
      leds[cont] = CRGB::Blue;   
    else
      leds[cont] = CRGB::Black;
  }
}

void AnilloLed::Apagar()
{
  estado = EstadoEjecucion::Off;
  // Leds en azul
  for (int cont=0;cont<NUM_LEDS;cont++)
    leds[cont] = CRGB::Black;   

  luzCentral->Apagar();
}

void AnilloLed::Encender()
{
  estado = EstadoEjecucion::On;
  // Leds en azul
  for (int cont=0;cont<NUM_LEDS;cont++)
    leds[cont] = CRGB::Blue;   

  luzCentral->Encender();
}

void AnilloLed::CambiarBrillo(int nuevoBrillo)
{
  // Sólo si el estado es on u off
  if (estado == EstadoEjecucion::On || estado == EstadoEjecucion::Off)
    CambiarBrilloAnimacion(nuevoBrillo);  
}

void AnilloLed::CambiarBrilloAnimacion(int nuevoBrillo)
{
  //Serial.print("Cambiar brillo ");
  //Serial.println(nuevoBrillo);
  FastLED.setBrightness(nuevoBrillo);
}

EstadoEjecucion AnilloLed::ObtenerEstado()
{
  return estado;
}
