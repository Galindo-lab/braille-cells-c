
#ifndef ES_BRAILLE_CELLS_DOT_H
#define ES_BRAILLE_CELLS_DOT_H

/**
 * Caracteres especiales para el español
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

/**
 * Caracteres especiales para el braille
 */

#define NUMBER_PREFIX 26
#define UPCASE_PREFIX 27
#define NUMBER_INTERRUPTOR 28

/**
 * Representa los datos de la celda braille
 * @param charset dos bits libres
 * @param dots relieves del carácter 
 */
typedef struct {
  unsigned char charset : 2; 
  unsigned char dots : 6;    /* los 6 puntos del caracter *
} BrailleCell;

/**
 * Retorna el caracter correspondiente a la posicion en 
 * el charset
 *
 * @param  pos posición
 * @return BrailleCell caracter
 */
BrailleCell get_braille_char(int pos);

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
char get_dot(BrailleCell character, char dot_pos);

/**
 * Retorna el valor numerico de los relieves, está función
 * se usa para guardar el caracter como numero
 * @param
 * @return
 */
char dots(BrailleCell character);

/**
 * Verifica que el carácter representa un numero (ascii)
 *
 * @param carácter que se quiere validar
 * @return isNumeric
 */
char is_numeric(unsigned int ch);

/**
 * Valida si el carácter es alguna de las letras del
 * alfabeto (ascii)
 *
 * @param carácter que se quiere validar
 * @return isNotAlphabetic
 */
char is_alphabetic(unsigned int ch);

/**
 * Validar si un carácter es mayúscula (ascii)
 *
 * @param carácter que se quiere validar
 * @return isCapital
 */
char is_capital(unsigned int chr);

/**
 * Convierte un carácter ascii en su equivalente en BrailleCell
 * Si no existe un equivalente al carácter en braille se inserta
 * Un espacio vació
 *
 * NO puede convertir caracteres con símbolos de puntuación.
 *
 * @param chr caracter a convertir
 * @return BrialleCell el caracter en braille
 */
BrailleCell char_to_braille(unsigned int chr);

#endif
