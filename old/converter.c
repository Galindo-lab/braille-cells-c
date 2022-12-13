
/**
 * AUTHOR: Luis Eduardo Galindo Amaya
 * DATE: 12-12-2022
 * DESC: Ejemplo de uso de las funciones de es-braile-cells.h
 */

#include "es-braille-cells.h"
#include <stdio.h>

/**
 * Tamaño del buffer de salida
 * NOTE: el buffer debe terminar con [\0]
 */
#define OUTPUT_BUFFER_SIZE 255

/**
 * Son caracteres que se dejan al final del buffer para evitar
 * el sobreflujo del buffer
 */
#define BUFFER_BORDER 3

void put_braille_char(BrailleCell chr);
int str_to_braille(char input_buff[], char output_buff[]);
void display_braille_str(char input_buffer[]);

int main() {

  char buffer_output[OUTPUT_BUFFER_SIZE];
  char buffer_input[] = "Muy Feliz Cumple!!!";
  
  int b = str_to_braille(buffer_input, buffer_output);
  printf("%d\n", b);

  display_braille_str(buffer_output);

  putchar('\n');
  return 0;
}

/**
 * Imprime los caracteres del string 
 * @param 
 * @return 
 */
void display_braille_str(char input_buffer[]) {
  for (char curr = *input_buffer; curr != '\0'; curr = *++input_buffer) {
    BrailleCell foo = {0, curr};
    put_braille_char(foo);
  }
}

/**
 * Imprime la representacion del caracter en el siguiente
 * formato: a = 1, f = 124, m = 134
 *
 * @param chr
 */
void put_braille_char(BrailleCell chr) {
  if (chr.dots == 63) {
    /* NOTE: revisar el la tabla de caracteres (Espacio) */
    printf(". ");
  } else {
    for (int i = 0; i < 6; i++) {
      if (get_dot(chr, i))
        putchar(i + '1');
    }
    putchar(' ');
  }
}

/**
 * Convierte un string de caracteres ascii a su representacion
 * braille binaria, se pueden usar modificadores para los
 * caracteres faltantes, [^] para acentos, [~] seguido de [n]
 * para la [ñ] y [_] seguido de [u] para [ü].
 *
 * TODO: Esta funcion se beneficiaria de tener un diagrama
 *       de flujo para explicar como funciona
 *
 * @param output_buff
 * @param input_buff
 * @return verdadero si hay errores de conversion
 */
int str_to_braille(char input_buffer[], char output_buffer[]) {
  int buffer_pos = 0;           /* posicion en el buffer */
  BrailleCell character;        /* caracter a insertar */
  char prev;                    /* caracter de la iteracion previa */

  for (char curr = *input_buffer; curr != '\0'; curr = *++input_buffer) {

    if (curr == '^' || curr == '~' || curr == '_')
      /* Si es un modificador se pasa al siguiente caracter */
      continue;

    if (buffer_pos > (OUTPUT_BUFFER_SIZE - BUFFER_BORDER - 1))
      /* si el string resultante es mayor que el tamaño
         máximo del buffer mas el terminador retorna error */
      return 1;

    prev = curr;
    character = char_to_braille(curr); /* carácter sin modificadores */

    if (is_alphabetic(curr)) {
      /* Aquí va todo lo que tenga que ver con
         caracteres alfabéticos */

      if (is_numeric(prev)) {
        /* si el carácter anterior es numérico insertar
           interruptor numérico braille */
        output_buffer[buffer_pos] = dots(braille_char[NUMBER_INTERRUPTOR]);
        buffer_pos++;
      }

      if (is_capital(curr)) {
        /* modificador de mayúscula */
        output_buffer[buffer_pos] = dots(braille_char[UPCASE_PREFIX]);
        buffer_pos++;
      }

      /* En esta seccion se agregan los modificadores */

      if (prev == '_') {
        /* dieresis */
        switch (curr) {
        case 'u':
          character = braille_char[UMLAUT_U];
          break;
        }
      }

      if (prev == '~') {
        /* eñes */
        switch (curr) {
        case 'n':
          character = braille_char[ACCENT_U];
          break;
        }
      }

      if (prev == '^') {
        /* acentos */
        switch (curr) {
        case 'a':
          character = braille_char[ACCENT_A];
          break;

        case 'e':
          character = braille_char[ACCENT_E];
          break;

        case 'i':
          character = braille_char[ACCENT_I];
          break;

        case 'o':
          character = braille_char[ACCENT_O];
          break;

        case 'u':
          character = braille_char[ACCENT_U];
          break;
        }
      }
    }

    if (is_numeric(curr)) {
      /* Aquí va todo lo que tenga que ver con
         caracteres numericos */

      if (!is_numeric(prev)) {
        /* si el caracter anterior no es numerico, inserta el
           prefijo numerico */
        output_buffer[buffer_pos] = dots(braille_char[NUMBER_PREFIX]);
        buffer_pos++;
      }
    }

    output_buffer[buffer_pos] = dots(character);
    buffer_pos++;
  }

  /* Conversión exitosa */
  output_buffer[buffer_pos + 1] = '\0';
  return 0;
}
