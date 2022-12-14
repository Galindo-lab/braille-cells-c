
#include "es_braille_cells.h"
#include <stdio.h>

/**
 * Tamaño del buffer de salida
 * NOTE: el buffer debe terminar con [\0]
 */
#define OUTPUT_BUFFER_SIZE 255

/**
 * Imprime la representacion del caracter en el siguiente
 * formato: a = 1, f = 124, m = 134
 *
 * @param chr
 */
void put_braille_char(BrailleCell chr);

/**
 * Imprime los caracteres del string
 * @param str el string a imprimr
 */
void display_braille_str(char str[]);

/**
 * 
 * @param  
 * @return 
 */
BrailleCell get_char(char character, char modifier);

/**
 *
 * @param
 * @return
 */
int str_to_braille(char input[], char output[]) ;

int main() {
  char buffer_output[OUTPUT_BUFFER_SIZE];
  char textos_de_prueba[5][255] = {
      "El ping_uino tocaba la guitarra en la ciudad de Toledo.", "pi~na",
      "Fabio me exige, sin tapujos, que a~nada cerveza al whisky.",
      "los numeros son 0,1,2,3,4,5,6,7,8,9,10",
      "interruptor de numero 0xf1120a0"};

  for (int i = 0; i < 5; i++) {
    str_to_braille(textos_de_prueba[i], buffer_output);
    printf("%s \n", textos_de_prueba[i]);
    display_braille_str(buffer_output);
    puts("\n");
  }

  putchar('\n');

  return 0;
}

void put_braille_char(BrailleCell chr) {
  if (chr.dots == 63) {
    /* NOTE: revisar el la tabla de caracteres (Espacio) */
    printf("  ");
  } else {
    for (int i = 0; i < 6; i++) {
      if (get_dot(chr, i))
        putchar(i + '1');
    }
    putchar(' ');
  }
}


void display_braille_str(char str[]) {
  for (char curr = *str; curr != '\0'; curr = *++str) {
    BrailleCell foo = {0, curr};
    put_braille_char(foo);
  }
}

BrailleCell get_char(char character, char modifier) {

  if (modifier == '_' && character == 'u') /* dieresis */
    return get_braille_char(UMLAUT_U);

  if (modifier == '~' && character == 'n') /* eñes */
    return get_braille_char(ACCENT_N);

  if (modifier == '^') { /* acentos */
    switch (character) {
    case 'a':
      return get_braille_char(ACCENT_A);
      break;

    case 'e':
      return get_braille_char(ACCENT_E);
      break;

    case 'i':
      return get_braille_char(ACCENT_I);
      break;

    case 'o':
      return get_braille_char(ACCENT_O);
      break;

    case 'u':
      return get_braille_char(ACCENT_U);
      break;
    }
  }

  return char_to_braille(character);
}

int str_to_braille(char input[], char output[]) {
  /* posicion en el buffer de salida */
  int pos = 0;
  /* caracter previo */
  char prev = '\0';
  /* caracter modificador del texto */
  char modificador = '\0';

  for (char curr = *input; curr != '\0'; curr = *++input) {

    if (curr == '^' || curr == '~' || curr == '_') {
      /* validar si el caracter tiene un modificador, los 
         modificadores no cuentan como caracteres asi que
         se omiten del conteo */
      modificador = curr;
      continue;
    }

    if (pos >= (OUTPUT_BUFFER_SIZE - 5)) {
      /* el - 5 es solo para evitar sobreflujos, si el texto no
         puede ser representado en el espacio del buffer de
         salida entonces retorna error */
      output[pos] = '\0';
      return 1;
    }

    if (is_capital(curr))
      output[pos++] = dots(get_braille_char(UPCASE_PREFIX));

    if (is_numeric(curr) && !is_numeric(prev))
      output[pos++] = dots(get_braille_char(NUMBER_PREFIX));

    if (is_alphabetic(curr) && is_numeric(prev))
      output[pos++] = dots(get_braille_char(NUMBER_INTERRUPTOR));

    output[pos++] = dots(get_char(curr, modificador));
    modificador = '\0';
    prev = curr;
  }

  output[pos++] = '\0';
  return 0;
}
