
#include "utils.h"

struct braileCharater {
  unsigned char charset : 2;
  /*
     charset al que pertenece el caracter

     0. abecedario
     1. carácter extendido
     2. símbolo
     3. indefinido
  */

  unsigned char character : 6;
  /*
    puntos activos del caracter

    1 4      0 3
    2 5  ->  1 4
    3 6      2 5
  */
};

typedef struct braileCharater BraileCharater;

BraileCharater modificadores[] = {
    {0, 0b111100}, /* prefijo numerico */
    {0, 0b101000}, /* prefijo mayuscula */
    {0, 0b010000}  /* interruptor de numero */
};

BraileCharater abecedario_normal[] = {
    {0, 0b000000}, /* espacio */
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

BraileCharater abecedario_extendido[] = {
    {1, 0b110111}, /* á */
    {1, 0b101110}, /* é */
    {1, 0b001100}, /* í */
    {1, 0b101100}, /* ó */
    {1, 0b111110}, /* ú */
    {1, 0b110011}, /* ü */
    {1, 0b111011}, /* ñ */
};

BraileCharater signos[] = {
    {2, 0b000100}, /* . */
    {2, 0b000010}, /* , */
    {2, 0b100010}, /* ¿? */
    {2, 0b000110}, /* ; */
    {2, 0b010110}, /* ¡! */
    {2, 0b100110}, /* "" */
    {2, 0b100011}, /* ( */
    {2, 0b011100}, /* ) */
    {2, 0b100100}, /* - */
    {2, 0b010100}  /* * */
};

/**
 * Retorna el estado del punto en cada posición, las
 * posiciones corresponden al estándar menos uno:
 *
 *                1 4      0 3
 *                2 5  ->  1 4
 *                3 6      2 5
 *
 * @warning pos no debe ser menor a 0 o mayor a 5
 *
 * @param chr del que queremos extraer el punto
 * @param pos posicion del punto
 * @return estado del punto
 */
char getPoint(BraileCharater chr, char pos) {
  return (chr.character & 1 << pos);
}

/**
 * Verifica que el chr representa un numero
 * @param carácter que se quiere validar
 * @return isNotNumeric
 */
char isNumeric(char ch) { return ch >= '0' && ch <= '9'; }

/**
 * Valida si chr *NO* es alguna de las letras del alfabeto
 * @warning solo funciona para minúsculas
 * @param carácter que se quiere validar
 * @return isNotAlphabetic
 */
char isNotAlphabetic(char ch) { return ch < 'a' && ch > 'z'; }

/**
 * Validar si un caracter es mayuscula
 * @param caracter que se quiere validar
 * @return isCapital
 */
char isCapital(char chr) {
  if (isNotAlphabetic(chr)) {
    /* no puede se mayuscula si no es caracter */
    return 0;
  }

  return !(chr & 32);
}

BraileCharater charToBraile(char chr) {
  /* si es un numero */
  if (isNumeric(chr))
    return abecedario_normal[chr - '0'];

  /* si es un caracter */
  chr = chr | 32; /* downcase */

  if (isNotAlphabetic(chr) || chr == ' ')
    /* validar que sea un caracter valido */
    return abecedario_normal[0];

  /* a = 97 pero en el arreglo espacio = 0 y a = 1*/
  return abecedario_normal[chr - 'a' + 1];
}

/**
 * Imprime la representacion en braile del caracter
 * @param caracter
 */
void braile_character_print(BraileCharater chr) {
  for (int i = 0; i < 3; i++) {
    putchar(' ');
    putchar(getPoint(chr, i) ? 'o' : '.');
    putchar(' ');
    putchar(getPoint(chr, i + 3) ? 'o' : '.');
    putchar('\n');
  }
}

/**
 * imprimir cadena en braile
 * @param
 * @return
 */
void braile_string_print(char s[], size_t foo) {

  for (size_t i = 0; i < foo; i++) {

    if (isNumeric(s[i])) {
      printf("-NUM-\n");
      braile_character_print(modificadores[0]);
    }

    if (isCapital(s[i])) {
      /* añadir el prefijo de las mayusculas */
      printf("-CAP-\n");
      braile_character_print(modificadores[1]);
    }

    printf("--%c--\n", s[i]);
    braile_character_print(charToBraile(s[i]));
  }
}

int main() {

  printf("Size of braileCharater is %lu bytes\n",
         sizeof(struct braileCharater));

  char s[] = "1912 Entramos 456 en la ciudad de Toledo";
  size_t foo = sizeof(s) / sizeof(s[0]) - 1; /* size sin \0 */
  braile_string_print(s, foo);

  /* for(unsigned int i=0;i <
   * (sizeof(abecedario_normal)/sizeof(BraileCharater)); i++){ */
  /*      printf("--%c--\n",97+i); */
  /*      braile_character_print(abecedario_normal[i]); */
  /* } */

  /* for(unsigned int i=0;i <
   * (sizeof(abecedario_extendido)/sizeof(BraileCharater)); i++){ */

  /* } */

  /* putchar(a); */

  /* unsigned char s[] = "ü"; */

  /* for(int i=0;i < (sizeof(s)/sizeof(char)); i++){ */
  /*      printf("%d\n",s[i]); */
  /* } */

  /* printf("%s \n", s); */

  puts("");
  return 0;
}
