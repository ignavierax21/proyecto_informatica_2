# Código Morse

**Traductor bidireccional de código Morse mediante Arduino y Processing.**

## Descripción

Código Morse es un proyecto que busca desarrollar un traductor capaz de convertir texto convencional a código Morse y viceversa.

El sistema utiliza Arduino UNO para gestionar los componentes físicos y Processing para desarrollar una interfaz gráfica que permita la comunicación con la computadora.

## Componentes

- Arduino UNO.
- Pantalla LCD 1602.
- Pulsadores.
- LED.
- Buzzer pasivo.
- Resistencias.
- Cables de conexión.

## Funcionamiento actual

El prototipo inicial en Tinkercad permite:

- Ingresar código Morse mediante un pulsador.
- Diferenciar puntos y rayas según la duración de la pulsación.
- Traducir letras, números y algunos signos de puntuación.
- Visualizar los mensajes en una pantalla LCD.
- Agregar espacios mediante un segundo pulsador.
- Recibir caracteres por comunicación Serial.
- Reproducir código Morse mediante un buzzer.

## Tecnologías utilizadas

- Arduino IDE.
- Arduino UNO.
- Tinkercad Circuits.
- Processing.
- Git y GitHub.

## Estado del proyecto

Actualmente se encuentra en etapa de desarrollo y pruebas iniciales en Tinkercad:

Prototipo en Tinkercad

Durante el desarrollo inicial se utilizó una pantalla LCD 1602 para visualizar los caracteres decodificados. Su incorporación fue temporal y tuvo como objetivo facilitar las pruebas del circuito.

En el montaje físico, la visualización se realizará mediante la comunicación Serial con la computadora y, posteriormente, a través de una interfaz gráfica desarrollada en Processing. Por lo tanto, la LCD no forma parte del montaje físico definitivo.

https://www.tinkercad.com/things/fJj2nTK7r6Q-prototipo-base-code-morse-info-2?sharecode=z52Q0O8Aea-w10cjqUkd_ehLvOKU1zZu55Wkhw3r3fk (Link para verlo en tinkercad).

Quedan pendientes la integración con Processing, las pruebas con el Arduino físico y la implementación de la calibración automática mediante regresión lineal por mínimos cuadrados y otros temas referidos a la programación.
