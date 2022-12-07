

/*
  Para escribir en braile se utilizan seis puntos para
  representar símbolos del alfabeto, los números y caracteres
  de control.
  
  cada carácter esta compuestos de seis puntos, para hablar
  sobre los puntos en relieve del carácter se utiliza la 
  siguiente nomenclatura:
  
                           1 4  
                           2 5  
                           3 6  

  podemos representar los relieves del carácter mediante el 
  sistema binario de numeración binario, de manera que el 
  bit menos significativo represente el relieve con la 
  posición mas baja: 

                      1 4       0 3
                      2 5  -->  1 4
                      3 6       2 5
  
  Entonces:
  - el relieve 1 es el bit 0
  - el relieve 2 es el bit 1 
  - el relieve 3 es el bit 2
  - etc...

  Por utimo es facil concer que relieves estan activos por 
  medio de enmascaramiento de bits.
*/

typedef struct {  
  unsigned char charset : 2;    /* no tiene uso */
  unsigned char dots : 6;       /* los 6 puntos del caracter */
} BraileChar;

/*
  Caracteres especiales para el braile
*/

const BraileChar NUMBER_PREFIX = {0, 0b111100};
const BraileChar UPCASE_PREFIX = {0, 0b101000};
const BraileChar NUMBER_INTERRUPTOR = {0, 0b010000};
const BraileChar SPACE = {0, 0b000000};

/*
  Alfabeto
*/

BraileCharater alphabet[] = {
    {0, 0b000001}, /* a - 1 */
    {0, 0b000011}, /* b - 2 */
    {0, 0b001001}, /* c - 3 */
    {0, 0b011001}, /* d - 4 */
    {0, 0b010001}, /* e - 5 */
    {0, 0b001011}, /* f - 6 */
    {0, 0b011011}, /* g - 7 */
    {0, 0b010011}, /* h - 8 */
    {0, 0b001010}, /* i - 9 */
    {0, 0b011010}, /* j - 0 */
    {0, 0b011010}, /* k */
    {0, 0b000111}, /* l */
    {0, 0b001101}, /* m */
    {0, 0b011101}, /* n */
    {0, 0b010101}, /* o */
    {0, 0b001111}, /* p */
    {0, 0b011111}, /* q */
    {0, 0b010111}, /* r */
    {0, 0b001110}, /* s */
    {0, 0b011110}, /* t */
    {0, 0b100101}, /* u */
    {0, 0b100111}, /* v */
    {0, 0b111010}, /* w */
    {0, 0b101101}, /* x */
    {0, 0b111101}, /* y */
    {0, 0b110101}  /* z */
};
