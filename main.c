
#include <stdio.h>

#include "es-braille-cells.h"

void print_braille_character(BrailleCell);
void print_braille_string(char[]);

int main() {

  print_braille_string(
    "El ping_uino tocaba la guitarra en la"
    "ciudad de Toledo en 1920, "

   );
    
  return 0;
}



/**
 * Imprime la representacion en braille del caracter
 * @param caracter
 */
void print_braille_character(BrailleCell chr) {
  for (int i = 0; i < 3; i++) {
    putchar(' ');
    putchar(get_point(chr, i) ? 'o' : '.');
    putchar(' ');
    putchar(get_point(chr, i + 3) ? 'o' : '.');
    putchar('\n');
  }
}


/**
 * Convierte un string ascii en su representacion braille. Al
 * no tener caracteres especiales esta funcion tiene prefijos
 * para ingresar acentos y la letra 'ñ'
 * 
 * para ingresar los acentos solo escribe '^' antes del la 
 * vocal que quieres.
 *
 * para ingresa la 'ñ' solo tienes que poner ~n.
 *
 * para ingresar 'ü' solo tienes que poner _u.
 *
 * @param
 * @return
 */
void print_braille_string(char str[]) {
  char prev;
  char curr = '\0';

  for (int i = 0; str[i] != 0; i++) {
    prev = curr;
    curr = str[i];

    if (curr == '^' || curr == '~' || curr == '_') {
      /* 
         prefijos de caracter *NO* se imprimen, si un caracter
         de los anteriores aparece en el string significa que es
         un caracter especial:

         [^]: es para acentos (á, é, í, ó, ú)
         [~]: para la ñ 
         [_]: para las dieresis (ü)     
      */
      continue;
    }
    
    if (is_capital(curr)) {
      /* 
         los caracteres en braille se vuelven mayúsculas al 
         con el prefijo mayúscula.
       */
      printf("-CAP-\n");
      print_braille_character(braille_char[UPCASE_PREFIX]);
      curr = str[i] | 32;       /* minuscula */
    }

    
    if (prev == '_') {
      /* 
         prefijo dieresis
       */
      switch (curr) {
      case 'u':
        printf("--ü--\n");
        print_braille_character(braille_char[UMLAUT_U]);
        break;
      }
      continue;
    }
    
    
    if (prev == '~') {
      /* 
         prefijo para ñ
       */
      switch (curr) {
      case 'n':
        printf("--ñ--\n");
        print_braille_character(braille_char[ACCENT_N]);
        break;
      }
      continue;
    }

    
    if (prev == '^') {
      /*
        prefijo para acentos
       */
      switch (curr) {
      case 'a':
        printf("--á-- %d\n", curr);
        print_braille_character(braille_char[ACCENT_A]);
        break;

      case 'e':
        printf("--é-- %d\n", curr);
        print_braille_character(braille_char[ACCENT_E]);
        break;

      case 'i':
        printf("--í-- %d\n", curr);
        print_braille_character(braille_char[ACCENT_I]);
        break;

      case 'o':
        printf("--ó-- %d\n", curr);
        print_braille_character(braille_char[ACCENT_O]);
        break;

      case 'u':
        printf("--ú-- %d\n", curr);
        print_braille_character(braille_char[ACCENT_U]);
        break;
      }

      continue;
    }

    if (is_numeric(curr) && !is_numeric(prev)) {
      /*
        prefijo numerico braille
      */
      printf("-NUM-\n");
      print_braille_character(braille_char[NUMBER_PREFIX]);
    }

    if (is_alphabetic(curr) && is_numeric(prev)) {
      /* 
         interruptor numerico braille
      */
      puts("-IDN-");
      print_braille_character(braille_char[NUMBER_INTERRUPTOR]);
    }

    printf("--%c-- %d\n", curr, curr);
    print_braille_character(char_to_braille(curr));
  }
}
