
#include "es_braille_cells.h"

/**
 * Alfabeto, esta ordenado por grupos continuos en la tabla del
 * código ascii, esto para simplificar obtener un carácter
 * mediante una formula con los caracteres
 */
const BrailleCell braille_charset[] = {
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
    {0, 0b000101}, /* 10: k */
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

    /* Segundo bloque de caracteres completo */
    {0, 0b111111}, /* 29: espacio */
    /* El espacio se representa con todos los bits activados
       para que no se confunda con el caracter terminador. */
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

BrailleCell get_braille_char(int pos) {
  return braille_charset[pos];
}

char get_dot(BrailleCell character, char dot_pos) {
  return (character.dots & 1 << dot_pos);
}

char dots(BrailleCell character) { return character.dots; }

char is_numeric(unsigned int ch) { return ch >= '0' && ch <= '9'; }

char is_alphabetic(unsigned int ch) {
  ch = ch | 32;
  return ch >= 'a' && ch <= 'z';
}

char is_capital(unsigned int chr) {
  if (!is_alphabetic(chr))
    /* no puede ser mayúscula si no es un carácter */
    return 0;

  /* valida si el bit 5 esta activo, si el bit esta desactivado
     significa que es un carácter ṕero no es mayúscula */
  return !(chr & 32);
}

BrailleCell char_to_braille(unsigned int chr) {

  if (is_alphabetic(chr)) {
    /* caracteres alfabeticos */
    return braille_charset[(chr | 32) - 'a'];
  }

  if (is_numeric(chr)) {
    /* caracteres numericos */

    if (chr == '0')
      return braille_charset[9]; /* caracter j */

    return braille_charset[chr - '1'];
  }

  if (chr >= ' ' && chr <= '/') {
    /* segundo bloque de caracteres */
    return braille_charset[chr - ' ' + SPACE];
  }

  if (chr >= ':' && chr <= '@') {
    /* tercer bloque de caracteres */
    return braille_charset[chr - ':' + COLON];
  }

  /* si el caracter es desconocido retorna espacio */
  return braille_charset[SPACE];
}
