#include <display/NumberToString.h>

/*
 * Átalakítja a megadott egész számot karakterlánccá a megadott számrendszerben
 * kifejezve.
 */
char* intToString(int32_t value, uint8_t base) {
  static const char DIGIT_MAP[] = "0123456789ABCDEF";
  static char result[17];
  uint8_t max_length = 14;
  
  /* Az elõjel elválasztása az átalakítani kívánt számtól. */
  bool isNegative = value < 0 ? true : false;
  if(isNegative) value = -value;
  
  /* Az átalakítás megszakítása és nulla eredmény visszaadása, ha a megadott
  számrendszer kívül esik a megendegett intervallumon, vagy a szám értéke
  nulla. */
  if(base < 2 || base > 16 || !value) return "0";
  
  /* A megadott szám átalakítása karakterlánccá. */
  result[max_length + isNegative + 1] = '\0';
  for(; value && max_length ; --max_length, value /= base)
    result[max_length + isNegative] = DIGIT_MAP[value % base];
  
  /* Az elválaszott elõjel hozzáadása a karakterlánchoz, majd az eredmény elsõ
  karakterére mutató pointer visszaadása. */
  if(isNegative) result[max_length + 1] = '-';
  return &result[max_length + 1];
}

/*
 * Átalakítja a megadott lebegõpontos számot karakterlánccá a megadott
 * pontosságnak megfelelõen.
 */
char* floatToString(float value, uint8_t precision) {
  static char result[15];
  char* result_ptr;
  int32_t mantissa, int_part = 0, frac_part = 0;
  int8_t exponent;
  uint8_t length, max_length;
  char* str_ptr;
  
  /* A megadott lebegõpontos szám kitevõjének és mantisszájának kinyerése a
  változó bitjeibõl. */
  union { int32_t raw_value; float float_value; } _value;
  _value.float_value = value;
  exponent = (uint8_t)(_value.raw_value >> 24) - 127;
  mantissa = (_value.raw_value & 0xFFFFFF) | 0x800000;
  
  /* Az átalakítás megszakítása, amennyiben a megadott szám kitevõje túl kicsi,
  vagy túl nagy, esetleg maga a megadott szám nullával egyenlõ. */
  if(exponent >= 31 || exponent < -23 || !_value.raw_value) return "0.0";

  /* A megadott szám egész és tört részeinek meghatározása a kitevõ alapján. */
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
  
  /* A negatív elõjel hozzáírása a karakterlánchoz, ha a megadott szám kisebb,
  mint nulla. */
  result_ptr = result;
  if(_value.raw_value & 0x800000) *result_ptr++ = '-';

  /* A megadott szám egész részének átalakítása karakterlánccá. */
  if(int_part == 0) {
    *result_ptr++ = '0';
  }
  else {
    str_ptr = intToString(int_part, 10);
    while(*str_ptr)
      *result_ptr++ = *str_ptr++;
  }
  
  /* A megadott szám tört részének átalakítása karakterlánccá. */
  *result_ptr++ = '.';
  if(frac_part == 0) {
    *result_ptr++ = '0';
  }
  else {
    max_length = precision ? precision : (sizeof(result) - (result_ptr - result) - 1);
    if(max_length > 7) max_length = 7;
    
    /* A tört rész ismétlõdõ szorzása tízzel és az így kapott szám egész
    részének átalakítása karakterré minden periódusban. */
    for(length = 0; length < max_length; length++) {
      frac_part = (frac_part << 3) + (frac_part << 1);
      *result_ptr++ = (frac_part >> 24) + '0';
      frac_part &= 0xFFFFFF;
    }
    
    /* A felesleges nullák törlése a karakterláncként kódolt tizedes érték
    végérõl. */
    for(--result_ptr; result_ptr[0] == '0' && result_ptr[-1] != '.'; --result_ptr);
    ++result_ptr;
  }
  
  /* A karakterlánc lezárása és az eredmény elsõ karakterére mutató pointer
  visszaadása. */
  *result_ptr = '\0';
  return result;
}