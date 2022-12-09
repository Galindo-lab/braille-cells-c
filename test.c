

#include <stdio.h>
#include "es-braille-cells.h"

#define OUTPUT_BUFFER_SIZE 255


/**
 * Imprime la representacion en braille del caracter
 * @param caracter
 */
void print_braille_character(BrailleCell chr) {

  if (chr.dots == 0) {
    putchar('.');
  } else {
    for (int i = 0; i < 6; i++) {
      if (get_dot(chr, i))
        printf("%c", i + '1');
    }
  }

  putchar(' ');
}

/**
 * Cantidad de celdas necesarios para representar un 
 * string en braille
 * @param  str 
 * @return numero de caracteres
 */
unsigned int braille_rep_size(char str[]) {
  unsigned int size = 0;

  char prev;
  char curr = '\0';

  for (int i = 0; str[i] != 0; i++) {
    prev = curr;
    curr = str[i];

    /* modificador de mayuscula */
    if (is_capital(curr))
      size++;                   
    
    /* prefijo numerico */
    if (is_numeric(curr) && !is_numeric(prev)) 
      size++;                   
    
    /* interruptor numerico braille */
    if (is_alphabetic(curr) && is_numeric(prev))
      size++;                   
  
    size++;
  }

  /* caracter terminador */
  size++;                       
  return size;
}


/**
 * 
 * @param  
 * @return 
 */
void str_to_braille(char output[], char str[]){
  int buff_pos= 0;
  char prev;
  char curr = '\0';

  if(braille_rep_size(str) > OUTPUT_BUFFER_SIZE) {
    /* si no cabe el string de salida en el buffer se termina */
    goto clear;
  }

  for (int i = 0; str[i] != 0; i++) {
    prev = curr;
    curr = str[i];
    
    /* modificador de mayuscula */
    if (is_capital(curr)){
      output[buff_pos] = dots(braille_char[UPCASE_PREFIX]);
      buff_pos++;
    }
    
    /* prefijo numerico */
    if (is_numeric(curr) && !is_numeric(prev)){
      output[buff_pos] = dots(braille_char[NUMBER_PREFIX]);
      buff_pos++;
    }
    
    /* interruptor numerico braille */
    if (is_alphabetic(curr) && is_numeric(prev)){
      output[buff_pos] = dots(braille_char[NUMBER_INTERRUPTOR]);
      buff_pos++;
    }

    output[buff_pos] = dots(char_to_braille(str[i]));
    buff_pos++;
  }

  /* caracter terminador */
  buff_pos++;                  
  
 clear:
  output[buff_pos] = '\0';
}


int main() {
  char test_output[OUTPUT_BUFFER_SIZE];
  char test[] = "Hola Mundo6";

  puts(test);
  str_to_braille(test_output,test);

  for(int i=0;test_output[i]!=0; i++){
    printf("%d\n",test_output[i]);
  }


  return 0;
}
