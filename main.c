
/**
 * AUTHOR: Luis Eduardo Galindo Amaya
 * DATE: 12-12-2022
 *
 * DESC: Funciones y Lookups para escribir en braille, esta
 * bibloteca esta especialmente pensada para usarse en
 * microcontroladores por lo que trato de ahorrar la mayor
 * cantidad de memoria posible.
*/

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

/**
 * Caracteres especiales para el braille
 */

#define ACCENT_N 52
#define ACCENT_A 53
#define ACCENT_E 54
#define ACCENT_I 55
#define ACCENT_O 56
#define ACCENT_U 57
#define UMLAUT_U 58

#define SPACE 29
#define COLON 45

#define NUMBER_PREFIX 26
#define UPCASE_PREFIX 27
#define NUMBER_INTERRUPTOR 28

/**
 * Estructura para el caracter braille
 */
typedef struct {
  unsigned char charset : 2; /* no tiene uso */
  unsigned char dots : 6;    /* los 6 puntos del caracter */
} BrailleCell;

/*
  Alfabeto, esta ordenado por grupos continuos en la
  tabla del código ascii, esto para simplificar obtener un
  carácter mediante una formula con los caracteres
*/

const BrailleCell braille_char[] = {

    /* Primer bloque de caracteres completo */
    {0, 0b000001}, /*  0: a - 1 */
    {0, 0b000011}, /*  1: b - 2 */
    {0, 0b001001}, /*  2: c - 3 */
    {0, 0b011001}, /*  3: d - 4 */
    {0, 0b010001}, /*  4: e - 5 */
    {0, 0b001011}, /*  5: f - 6 */
    {0, 0b011011}, /*  6: g - 7 */
    {0, 0b010011}, /*  7: h - 8 */
    {0, 0b001010}, /*  8: i - 9 */
    {0, 0b011010}, /*  9: j - 0 */
    {0, 0b011010}, /* 10: k */
    {0, 0b000111}, /* 11: l */
    {0, 0b001101}, /* 12: m */
    {0, 0b011101}, /* 13: n */
    {0, 0b010101}, /* 14: o */
    {0, 0b001111}, /* 15: p */
    {0, 0b011111}, /* 16: q */
    {0, 0b010111}, /* 17: r */
    {0, 0b001110}, /* 18: s */
    {0, 0b011110}, /* 19: t */
    {0, 0b100101}, /* 20: u */
    {0, 0b100111}, /* 21: v */
    {0, 0b111010}, /* 22: w */
    {0, 0b101101}, /* 23: x */
    {0, 0b111101}, /* 24: y */
    {0, 0b110101}, /* 25: z */

    /* Caracteres modificadores */
    {0, 0b111100}, /* 26: prefijo numerico */
    {0, 0b101000}, /* 27: mayusculas */
    {0, 0b010000}, /* 28: interruptor de numero */

    /*
       Segundo bloque de caracteres completo

       El espacio se representa con todos los bits activados
       para que no se confunda con el caracter terminador.
    */
    {0, 0b111111}, /* 29: espacio */
    {0, 0b010110}, /* 30: ! */
    {0, 0b100110}, /* 31: " */
    {0, 0b111100}, /* 32: # */
    {0, 0b110010}, /* 33: $ */
    {0, 0b111000}, /* 34: % */
    {0, 0b111111}, /* 35: & */
    {0, 0b100110}, /* 36: ' */
    {0, 0b100011}, /* 37: ( */
    {0, 0b011100}, /* 38: ) */
    {0, 0b010100}, /* 39: * */
    {0, 0b010110}, /* 40: + */
    {0, 0b000010}, /* 41: , */
    {0, 0b100100}, /* 42: - (menos) */
    {0, 0b000100}, /* 43: . (punto)*/
    {0, 0b001100}, /* 44: / */

    /* Tercer bloque de caracteres completo */
    {0, 0b010010}, /* 45: : */
    {0, 0b000110}, /* 46: ; */
    {0, 0b101010}, /* 47: < */
    {0, 0b110110}, /* 48: = */
    {0, 0b010101}, /* 49: > */
    {0, 0b100010}, /* 50: ¿? */
    {0, 0b010000}, /* 51: @ */

    /* Caracteres extras para el español */
    {0, 0b111011}, /* 52: ñ */
    {0, 0b110111}, /* 53: á */
    {0, 0b101110}, /* 54: é */
    {0, 0b001100}, /* 55: í */
    {0, 0b101100}, /* 56: ó */
    {0, 0b111110}, /* 57: ú */
    {0, 0b110011}, /* 58: ü */
};

char get_dot(BrailleCell character, char dot_pos);
char dots(BrailleCell character);
char is_numeric(unsigned int ch);
char is_alphabetic(unsigned int ch);
char is_capital(unsigned int chr);
BrailleCell char_to_braille(unsigned int chr);

void put_braille_char(BrailleCell chr);
int str_to_braille(char input_buff[], char output_buff[]);
void display_braille_str(char input_buffer[]);

int main() {
  char buffer_output[OUTPUT_BUFFER_SIZE];
  char textos_de_prueba[5][255] = {
    "El ping_uino tocaba la guitarra en la ciudad de Toledo.", /* las dieresis se agregan con _ */
    "Quiere la fugaz boca exhausta vid, kiwi, pi~na y jam^on.", /* las eñes con ~ y los acentos con ^ */
    "Fabio me exige, sin tapujos, que a~nada cerveza al whisky.",
    "los numeros son 0,1,2,3,4,5,6,7,8,9,10",
    "interruptor de numero 0xf1120a0"
  };
  
  

  for(int i=0;i < 5; i++){
    str_to_braille(textos_de_prueba[i], buffer_output);
    printf("%s \n", textos_de_prueba[i]);
    display_braille_str(buffer_output);
    puts("\n");
  }

  

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
  int buffer_pos = 0;    /* posicion en el buffer */
  BrailleCell character; /* caracter a insertar */
  char prev;             /* caracter de la iteracion previa */

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
 * @param character del que queremos extraer el punto
 * @param dot_pos posición del punto
 * @return relieve del punto
 */
char get_dot(BrailleCell character, char dot_pos) {
  return (character.dots & 1 << dot_pos);
}

/**
 * Retorna el valor numerico de los relieves, está función
 * se usa para guardar el caracter como numero
 *
 * @return
 */
char dots(BrailleCell character) { return character.dots; }

/**
 * Verifica que el carácter representa un numero (ascii)
 *
 * @param carácter que se quiere validar
 * @return isNumeric
 */
char is_numeric(unsigned int ch) { return ch >= '0' && ch <= '9'; }

/**
 * Valida si el carácter es alguna de las letras del
 * alfabeto (ascii)
 *
 * @warning solo funciona para minúsculas
 *
 * @param carácter que se quiere validar
 * @return isNotAlphabetic
 */
char is_alphabetic(unsigned int ch) {
  ch = ch | 32;
  return ch >= 'a' && ch <= 'z';
}

/**
 * Validar si un carácter es mayúscula (ascii)
 *
 * @param carácter que se quiere validar
 * @return isCapital
 */
char is_capital(unsigned int chr) {
  if (!is_alphabetic(chr))
    /* no puede ser mayúscula si no es un carácter */
    return 0;

  /*
     valida si el bit 5 esta activo, si el bit esta desactivado
     significa que es un carácter ṕero no es mayúscula
  */
  return !(chr & 32);
}

/**
 * Convierte un carácter ascii en su equivalente en BrailleCell
 * Si no existe un equivalente al carácter en braille se inserta
 * Un espacio vació
 * @param  chr caracter a convertir
 * @return el caracter en braille
 */
BrailleCell char_to_braille(unsigned int chr) {

  if (is_alphabetic(chr)) {
    /* caracteres alfabeticos */
    return braille_char[(chr | 32) - 'a'];
  }

  if (is_numeric(chr)) {
    /* caracteres numericos */

    if (chr == '0')
      return braille_char[9]; /* caracter j */

    return braille_char[chr - '1'];
  }

  if (chr >= ' ' && chr <= '/') {
    /* segundo bloque de caracteres */
    return braille_char[chr - ' ' + SPACE];
  }

  if (chr >= ':' && chr <= '@') {
    /* tercer bloque de caracteres */
    return braille_char[chr - ':' + COLON];
  }

  /* si el caracter es desconocido retorna espacio */
  return braille_char[SPACE];
}
