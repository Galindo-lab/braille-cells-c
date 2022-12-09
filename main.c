
#include "es-braile.h"
#include <stdio.h>

/**
 * Imprime la representacion en braile del caracter
 * @param caracter
 */
void braile_character_print(BrailleCell chr) {
  for (int i = 0; i < 3; i++) {
    putchar(' ');
    putchar(get_point(chr, i) ? 'o' : '.');
    putchar(' ');
    putchar(get_point(chr, i + 3) ? 'o' : '.');
    putchar('\n');
  }
}

/**
 * 
 * @param  
 * @return 
 */
void print_briale_string(char str[]) {
  char prev = '\0';
  char next = '\0';
  char curr;

  for(int i=0; str[i] != 0 ; i++){
    curr = str[i];

    if (is_numeric(curr) && !is_numeric(prev)) {
      /* prefijo de numero  */
      printf("-NUM-\n");
      braile_character_print(braille_char[NUMBER_PREFIX]);
      goto print_char;
    }

    if (is_alphabetic(curr) && is_numeric(prev)) {
      /* interruptor de numero */
      puts("-IDN-");
      braile_character_print(braille_char[NUMBER_INTERRUPTOR]);
    }

    if (is_capital(curr)) {
      /* añadir el prefijo de las mayusculas */
      printf("-CAP-\n");
      braile_character_print(braille_char[UPCASE_PREFIX]);
      goto print_char;
    }

  print_char:
    printf("--%c-- %d\n", curr, curr);
    braile_character_print(char_to_braille(str[i]));
    prev = curr;
  }

}

int main() {

  print_briale_string("entramos a la ciudad de Toledo en 1920ee");

  return 0;
}
