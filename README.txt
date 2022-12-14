Luis Eduardo Galindo Amaya                                    13-12-2022





Sistema De Lectoescritura Braille
=================================

  Para escribir en braille se utilizan seis puntos para representar los
  símbolos del alfabeto, los números y caracteres de control.

  Cada carácter esta compuesto de seis puntos, para poder especificar
  los relieves del carácter usualmente se utiliza siguiente
  nomenclatura:

  ,----
  | 1 4
  | 2 5
  | 3 6
  `----


Representar Los Caracteres
==========================

  Además de la forma con relieves o visual podemos representar los
  caracteres mediante los números de sus relieves, ejemplo:


Carácter J:
~~~~~~~~~~~

  ,----
  | . o     
  | o o --> 245
  | . .
  `----


Carácter R:
~~~~~~~~~~~

  ,----
  | o .     
  | o o --> 1235
  | o .
  `----


Sistema de BrailleCells
=======================

  Podemos representar los relieves del carácter mediante el sistema
  binario, de manera que el bit menos significativo represente el
  relieve con la posición mas baja:

  - el relieve 1 es el bit 0
  - el relieve 2 es el bit 1
  - el relieve 3 es el bit 2
  - etc...

  ,----
  | 1 4       0 3
  | 2 5  -->  1 4
  | 3 6       2 5
  `----

  Entonces en memoria los caracteres se verían representados de la
  siguiente manera:

   Carácter  Braille  BrailleCell 
  --------------------------------
   a               1       000001 
   b              12       000011 
   j             245       011010 
   r            1235       010111 


Extraer los relieves del carácter
=================================

  Para conocer el estado de cada relieve solo basta con crear una
  mascara con la posición del relieve que nos interesa conocer, cabe
  recordar que [los relieves empiezan desde la posición cero]:

  ,----
  | char get_dot(BrailleCell character, char dot_pos) {
  |   return (character.dots & 1 << dot_pos);
  | }
  `----


[los relieves empiezan desde la posición cero] Vea seccion Sistema de
BrailleCells
