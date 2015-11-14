#include <display/NumberToString.h>

/*
 * �talak�tja a megadott eg�sz sz�mot karakterl�ncc� a megadott sz�mrendszerben
 * kifejezve.
 */
char* intToString(int32_t value, uint8_t base) {
  static const char DIGIT_MAP[] = "0123456789ABCDEF";
  static char result[17];
  uint8_t max_length = 14;
  
  /* Az el�jel elv�laszt�sa az �talak�tani k�v�nt sz�mt�l. */
  bool isNegative = value < 0 ? true : false;
  if(isNegative) value = -value;
  
  /* Az �talak�t�s megszak�t�sa �s nulla eredm�ny visszaad�sa, ha a megadott
  sz�mrendszer k�v�l esik a megendegett intervallumon, vagy a sz�m �rt�ke
  nulla. */
  if(base < 2 || base > 16 || !value) return "0";
  
  /* A megadott sz�m �talak�t�sa karakterl�ncc�. */
  result[max_length + isNegative + 1] = '\0';
  for(; value && max_length ; --max_length, value /= base)
    result[max_length + isNegative] = DIGIT_MAP[value % base];
  
  /* Az elv�laszott el�jel hozz�ad�sa a karakterl�nchoz, majd az eredm�ny els�
  karakter�re mutat� pointer visszaad�sa. */
  if(isNegative) result[max_length + 1] = '-';
  return &result[max_length + 1];
}

/*
 * �talak�tja a megadott lebeg�pontos sz�mot karakterl�ncc� a megadott
 * pontoss�gnak megfelel�en.
 */
char* floatToString(float value, uint8_t precision) {
  static char result[15];
  char* result_ptr;
  int32_t mantissa, int_part = 0, frac_part = 0;
  int8_t exponent;
  uint8_t length, max_length;
  char* str_ptr;
  
  /* A megadott lebeg�pontos sz�m kitev�j�nek �s mantissz�j�nak kinyer�se a
  v�ltoz� bitjeib�l. */
  union { int32_t raw_value; float float_value; } _value;
  _value.float_value = value;
  exponent = (uint8_t)(_value.raw_value >> 24) - 127;
  mantissa = (_value.raw_value & 0xFFFFFF) | 0x800000;
  
  /* Az �talak�t�s megszak�t�sa, amennyiben a megadott sz�m kitev�je t�l kicsi,
  vagy t�l nagy, esetleg maga a megadott sz�m null�val egyenl�. */
  if(exponent >= 31 || exponent < -23 || !_value.raw_value) return "0.0";

  /* A megadott sz�m eg�sz �s t�rt r�szeinek meghat�roz�sa a kitev� alapj�n. */
  if(exponent >= 23) {
    int_part = mantissa << (exponent - 23);
  }
  else if(exponent >= 0) {
    int_part = mantissa >> (23 - exponent);
    frac_part = (mantissa << (exponent + 1)) & 0xFFFFFF;
  }
  else {
    frac_part = (mantissa & 0xFFFFFF) >> -(exponent + 1);
  }
  
  /* A negat�v el�jel hozz��r�sa a karakterl�nchoz, ha a megadott sz�m kisebb,
  mint nulla. */
  result_ptr = result;
  if(_value.raw_value & 0x800000) *result_ptr++ = '-';

  /* A megadott sz�m eg�sz r�sz�nek �talak�t�sa karakterl�ncc�. */
  if(int_part == 0) {
    *result_ptr++ = '0';
  }
  else {
    str_ptr = intToString(int_part, 10);
    while(*str_ptr)
      *result_ptr++ = *str_ptr++;
  }
  
  /* A megadott sz�m t�rt r�sz�nek �talak�t�sa karakterl�ncc�. */
  *result_ptr++ = '.';
  if(frac_part == 0) {
    *result_ptr++ = '0';
  }
  else {
    max_length = precision ? precision : (sizeof(result) - (result_ptr - result) - 1);
    if(max_length > 7) max_length = 7;
    
    /* A t�rt r�sz ism�tl�d� szorz�sa t�zzel �s az �gy kapott sz�m eg�sz
    r�sz�nek �talak�t�sa karakterr� minden peri�dusban. */
    for(length = 0; length < max_length; length++) {
      frac_part = (frac_part << 3) + (frac_part << 1);
      *result_ptr++ = (frac_part >> 24) + '0';
      frac_part &= 0xFFFFFF;
    }
    
    /* A felesleges null�k t�rl�se a karakterl�nck�nt k�dolt tizedes �rt�k
    v�g�r�l. */
    for(--result_ptr; result_ptr[0] == '0' && result_ptr[-1] != '.'; --result_ptr);
    ++result_ptr;
  }
  
  /* A karakterl�nc lez�r�sa �s az eredm�ny els� karakter�re mutat� pointer
  visszaad�sa. */
  *result_ptr = '\0';
  return result;
}