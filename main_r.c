
// AUTHOR: Luis Eduardo Galindo Amaya
//   DATE: 27-11-2022
//   DESC: Convertidor de texto a braile

#include "utils.h"

#define NUMBER_PREFIX 0
#define UPCASE_PREFIX 1
#define NUMBER_INTERRUPTOR 2

struct braileCharater {
  unsigned char charset : 2;
  /*
     Charset al que pertenece el caracter
     0. modificador
     1. abecedario
     2. abecedario extendido
     3. simbolos
  */

  unsigned char character : 6;
  /*
    Puntos activos del caracter

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
    {1, 0b000000}, /* espacio */
    {1, 0b000001}, /* a - 1 */
    {1, 0b000011}, /* b - 2 */
    {1, 0b001001}, /* c - 3 */
    {1, 0b011001}, /* d - 4 */
    {1, 0b010001}, /* e - 5 */
    {1, 0b001011}, /* f - 6 */
    {1, 0b011011}, /* g - 7 */
    {1, 0b010011}, /* h - 8 */
    {1, 0b001010}, /* i - 9 */
    {1, 0b011010}, /* j - 0 */
    {1, 0b011010}, /* k */
    {1, 0b000111}, /* l */
    {1, 0b001101}, /* m */
    {1, 0b011101}, /* n */
    {1, 0b010101}, /* o */
    {1, 0b001111}, /* p */
    {1, 0b011111}, /* q */
    {1, 0b010111}, /* r */
    {1, 0b001110}, /* s */
    {1, 0b011110}, /* t */
    {1, 0b100101}, /* u */
    {1, 0b100111}, /* v */
    {1, 0b111010}, /* w */
    {1, 0b101101}, /* x */
    {1, 0b111101}, /* y */
    {1, 0b110101}  /* z */
};

BraileCharater abecedario_extendido[] = {
    {2, 0b110111}, /* á */
    {2, 0b101110}, /* é */
    {2, 0b001100}, /* í */
    {2, 0b101100}, /* ó */
    {2, 0b111110}, /* ú */
    {2, 0b110011}, /* ü */
    {2, 0b111011}, /* ñ */
};

BraileCharater signos[] = {
    {3, 0b000100}, /* . */
    {3, 0b000010}, /* , */
    {3, 0b100010}, /* ¿? */
    {3, 0b000110}, /* ; */
    {3, 0b010110}, /* ¡! */
    {3, 0b100110}, /* "" */
    {3, 0b100011}, /* ( */
    {3, 0b011100}, /* ) */
    {3, 0b100100}, /* - */
    {3, 0b010100}  /* * */
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
 * Verifica que el carácter representa un numero
 * @param carácter que se quiere validar
 * @return isNotNumeric
 */
char isNumeric(char ch) { return ch >= '0' && ch <= '9'; }

/**
 * Valida si el carácter es alguna de las letras del alfabeto
 * @warning solo funciona para minúsculas
 * @param carácter que se quiere validar
 * @return isNotAlphabetic
 */
char isAlphabetic(char ch) {
  ch = ch | 32;
  return ch >= 'a' && ch <= 'z';
}

/**
 * Validar si un carácter es mayúscula
 * @param caracter que se quiere validar
 * @return isCapital
 */
char isCapital(char chr) {
  if (isAlphabetic(chr))
    return !(chr & 32);

  /* no puede se mayuscula si no es caracter */
  return 0;
}

BraileCharater charToBraile(char chr) {
  /* si es un numero */
  if (isNumeric(chr)){
    if(chr == '0')              /* la j=0 en braile */
      return abecedario_normal['j' - 'a' + 1];
    
    return abecedario_normal[chr - '0'];
  }

  /* validar si esta en el alfabeto */
  if (!isAlphabetic(chr) || chr == ' ')
    /* Si no esta en el alfabeto se imprime un espacio */
    return abecedario_normal[0];

  /* downcase */
  chr = chr | 32;
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
  /*
    TODO:
    - Soporte para caracteres: 'ñ','á','é','í','ó','ú' y 'ü'.
    - Soporte para caracteres: '.',',','&','-',';','*'.
  */

  char prev = '\0';

  for (size_t i = 0; i < foo; i++) {
    unsigned short curr = s[i];

    if (isNumeric(curr) && !isNumeric(prev)) {
      /* prefijo de numero  */
      printf("-NUM-\n");
      braile_character_print(modificadores[NUMBER_PREFIX]);
      goto print_char;
    }

    if (isAlphabetic(curr) && isNumeric(prev)) {
      /* interruptor de numero */
      puts("-IDN-");
      braile_character_print(modificadores[NUMBER_INTERRUPTOR]);
    }

    if (isCapital(curr)) {
      /* añadir el prefijo de las mayusculas */
      printf("-CAP-\n");
      braile_character_print(modificadores[UPCASE_PREFIX]);
      goto print_char;
    }

  print_char:
    printf("--%c-- %d\n", curr, curr);
    braile_character_print(charToBraile(s[i]));
    prev = curr;
  }
}

int main() {

  printf("Tamaño del BraileCharater es: %lu bytes\n",
         sizeof(struct braileCharater));

  /* char s[] = "01912 Entramos en la ciudad de Toledo"; */

  /* char s[] = "xilofoNo ñ á é í ó ú Ñ Á É Í Ó Ú "; */

  char s[] = "HoLa";
  
  size_t foo = sizeof(s) / sizeof(s[0]) - 1; /* size sin \0 */
  braile_string_print(s, foo);


  puts("");
  return 0;
}
