# UFO
Proyecto Arduino

Código para la iluminación de una lámpara bajo el microcontrolador Arduino PRO Micro

https://www.thingiverse.com/thing:3492682

La iluminación está creada con dos fragmentos (24 y 6 leds respectivamente) de una tira led WS2812B. Está creada con dos fases:
- Efecto de Fade
- Giro de la luz creado con un efecto de desplazamiento de registro e iluminación individual.

La parte electrónica implica un Arduino PRO Micro, un RTC (real time clock) conectado por el bus I2C, un potenciómetro y los dos fragmentos de tira led. 

El RTC permite mantener la hora y el efecto de iluminación se producirá a las horas en punto y el número de etapas en la fase de giro irá condicionado por la hora.

El potenciómetro permite controlar la intensidad de la luz permitiendo apagarla y que sólo se ilumine con los efectos de iluminación.
