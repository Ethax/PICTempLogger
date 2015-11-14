#ifndef INC_MELODY_H_
#define INC_MELODY_H_

/**
 * @brief A zenei hangok frekvenciáinak definíciói.
 */
#define Tone_C0  16.35
#define Tone_Db0 17.32
#define Tone_D0  18.35
#define Tone_Eb0 19.45
#define Tone_E0  20.60
#define Tone_F0  21.83
#define Tone_Gb0 23.12
#define Tone_G0  24.50
#define Tone_Ab0 25.96
#define Tone_A0  27.50
#define Tone_Bb0 29.14
#define Tone_B0  30.87
#define Tone_C1  32.70
#define Tone_Db1 34.65
#define Tone_D1  36.71
#define Tone_Eb1 38.89
#define Tone_E1  41.20
#define Tone_F1  43.65
#define Tone_Gb1 46.25
#define Tone_G1  49.00
#define Tone_Ab1 51.91
#define Tone_A1  55.00
#define Tone_Bb1 58.27
#define Tone_B1  61.74
#define Tone_C2  65.41
#define Tone_Db2 69.30
#define Tone_D2  73.42
#define Tone_Eb2 77.78
#define Tone_E2  82.41
#define Tone_F2  87.31
#define Tone_Gb2 92.50
#define Tone_G2  98.00
#define Tone_Ab2 103.83
#define Tone_A2  110.00
#define Tone_Bb2 116.54
#define Tone_B2  123.47
#define Tone_C3  130.81
#define Tone_Db3 138.59
#define Tone_D3  146.83
#define Tone_Eb3 155.56
#define Tone_E3  164.81
#define Tone_F3  174.61
#define Tone_Gb3 185.00
#define Tone_G3  196.00
#define Tone_Ab3 207.65
#define Tone_A3  220.00
#define Tone_Bb3 233.08
#define Tone_B3  246.94
#define Tone_C4  261.63
#define Tone_Db4 277.18
#define Tone_D4  293.66
#define Tone_Eb4 311.13
#define Tone_E4  329.63
#define Tone_F4  349.23
#define Tone_Gb4 369.99
#define Tone_G4  392.00
#define Tone_Ab4 415.30
#define Tone_A4  440.00
#define Tone_Bb4 466.16
#define Tone_B4  493.88
#define Tone_C5  523.25
#define Tone_Db5 554.37
#define Tone_D5  587.33
#define Tone_Eb5 622.25
#define Tone_E5  659.26
#define Tone_F5  698.46
#define Tone_Gb5 739.99
#define Tone_G5  783.99
#define Tone_Ab5 830.61
#define Tone_A5  880.00
#define Tone_Bb5 932.33
#define Tone_B5  987.77
#define Tone_C6  1046.50
#define Tone_Db6 1108.73
#define Tone_D6  1174.66
#define Tone_Eb6 1244.51
#define Tone_E6  1318.51
#define Tone_F6  1396.91
#define Tone_Gb6 1479.98
#define Tone_G6  1567.98
#define Tone_Ab6 1661.22
#define Tone_A6  1760.00
#define Tone_Bb6 1864.66
#define Tone_B6  1975.53
#define Tone_C7  2093.00
#define Tone_Db7 2217.46
#define Tone_D7  2349.32
#define Tone_Eb7 2489.02
#define Tone_E7  2637.02
#define Tone_F7  2793.83
#define Tone_Gb7 2959.96
#define Tone_G7  3135.96
#define Tone_Ab7 3322.44
#define Tone_A7  3520.01
#define Tone_Bb7 3729.31
#define Tone_B7  3951.07
#define Tone_C8  4186.01
#define Tone_Db8 4434.92
#define Tone_D8  4698.64
#define Tone_Eb8 4978.03

/**
 * @brief A tempó definíciója, ami az ütemek idõbeli hosszát befolyásolja.
 */
#define BPM 160

/**
 * @brief A hangjegyek hosszainak definíciói milliszekundumokban a tempó
 * függvényében.
 */
#define Half      2 * Quarter
#define Quarter   60000 / BPM
#define Eighth    Quarter / 2
#define Sixteenth Quarter / 4
#define Whole     4 * Quarter

/**
 * @brief Lejátsza a Birodalmi Indulót a Csillagok Háborúja címû filmbõl.
 *
 * A hangok lejátszását követõ legalább 1 milliszekundumos késleltetések a
 * hangjegyek egymástól való elválasztását biztosítják, és megakadályozzák a
 * hangok egymásba folyását.
 */
void playTheImperialMarch() {
  Sound_Play(Tone_A5, Quarter); Delay_ms(1 + Quarter);
  Sound_Play(Tone_A5, Quarter); Delay_ms(1 + Quarter);
  Sound_Play(Tone_A5, Quarter); Delay_ms(1 + Quarter);
  Sound_Play(Tone_F5, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
  Sound_Play(Tone_C6, Sixteenth); Delay_ms(1 + Sixteenth);

  Sound_Play(Tone_A5, Quarter); Delay_ms(1 + Quarter);
  Sound_Play(Tone_F5, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
  Sound_Play(Tone_C6, Sixteenth); Delay_ms(1 + Sixteenth);
  Sound_Play(Tone_A5, Half); Delay_ms(1 + Half);

  Sound_Play(Tone_E6, Quarter); Delay_ms(1 + Quarter);
  Sound_Play(Tone_E6, Quarter); Delay_ms(1 + Quarter);
  Sound_Play(Tone_E6, Quarter); Delay_ms(1 + Quarter);
  Sound_Play(Tone_F6, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
  Sound_Play(Tone_C6, Sixteenth); Delay_ms(1 + Sixteenth);

  Sound_Play(Tone_Ab5, Quarter); Delay_ms(1 + Quarter);
  Sound_Play(Tone_F5, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
  Sound_Play(Tone_C6, Sixteenth); Delay_ms(1 + Sixteenth);
  Sound_Play(Tone_A5, Half); Delay_ms(1 + Half);

  Sound_Play(Tone_A6, Quarter); Delay_ms(1 + Quarter);
  Sound_Play(Tone_A5, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
  Sound_Play(Tone_A5, Sixteenth); Delay_ms(1 + Sixteenth);
  Sound_Play(Tone_A6, Quarter); Delay_ms(1 + Quarter);
  Sound_Play(Tone_Ab6, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
  Sound_Play(Tone_G6, Sixteenth); Delay_ms(1 + Sixteenth);

  Sound_Play(Tone_Gb6, Sixteenth); Delay_ms(1 + Sixteenth);
  Sound_Play(Tone_E6, Sixteenth); Delay_ms(1 + Sixteenth);
  Sound_Play(Tone_F6, Eighth); Delay_ms(1 + Eighth);
  Delay_ms(1 + Eighth);
  Sound_Play(Tone_Bb5, Eighth); Delay_ms(1 + Eighth);
  Sound_Play(Tone_Eb6, Quarter); Delay_ms(1 + Quarter);
  Sound_Play(Tone_D6, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
  Sound_Play(Tone_Db6, Sixteenth); Delay_ms(1 + Sixteenth);

  Sound_Play(Tone_C6, Sixteenth); Delay_ms(1 + Sixteenth);
  Sound_Play(Tone_B5, Sixteenth); Delay_ms(1 + Sixteenth);
  Sound_Play(Tone_C6, Eighth); Delay_ms(1 + Eighth);
  Delay_ms(1 + Eighth);
  Sound_Play(Tone_F5, Eighth); Delay_ms(1 + Eighth);
  Sound_Play(Tone_Ab5, Quarter); Delay_ms(1 + Quarter);
  Sound_Play(Tone_F5, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
  Sound_Play(Tone_A5, Sixteenth); Delay_ms(1 + Sixteenth);

  Sound_Play(Tone_C6, Quarter); Delay_ms(1 + Quarter);
  Sound_Play(Tone_A5, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
  Sound_Play(Tone_C6, Sixteenth); Delay_ms(1 + Sixteenth);
  Sound_Play(Tone_E6, Half); Delay_ms(1 + Half);

  Sound_Play(Tone_A6, Quarter); Delay_ms(1 + Quarter);
  Sound_Play(Tone_A5, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
  Sound_Play(Tone_A5, Sixteenth); Delay_ms(1 + Sixteenth);
  Sound_Play(Tone_A6, Quarter); Delay_ms(1 + Quarter);
  Sound_Play(Tone_Ab6, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
  Sound_Play(Tone_G6, Sixteenth); Delay_ms(1 + Sixteenth);

  Sound_Play(Tone_Gb6, Sixteenth); Delay_ms(1 + Sixteenth);
  Sound_Play(Tone_E6, Sixteenth); Delay_ms(1 + Sixteenth);
  Sound_Play(Tone_F6, Eighth); Delay_ms(1 + Eighth);
  Delay_ms(1 + Eighth);
  Sound_Play(Tone_Bb5, Eighth); Delay_ms(1 + Eighth);
  Sound_Play(Tone_Eb6, Quarter); Delay_ms(1 + Quarter);
  Sound_Play(Tone_D6, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
  Sound_Play(Tone_Db6, Sixteenth); Delay_ms(1 + Sixteenth);

  Sound_Play(Tone_C6, Sixteenth); Delay_ms(1 + Sixteenth);
  Sound_Play(Tone_B5, Sixteenth); Delay_ms(1 + Sixteenth);
  Sound_Play(Tone_C6, Eighth); Delay_ms(1 + Eighth);
  Delay_ms(1 + Eighth);
  Sound_Play(Tone_F5, Eighth); Delay_ms(1 + Eighth);
  Sound_Play(Tone_Ab5, Quarter); Delay_ms(1 + Quarter);
  Sound_Play(Tone_F5, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
  Sound_Play(Tone_C6, Sixteenth); Delay_ms(1 + Sixteenth);

  Sound_Play(Tone_A5, Quarter); Delay_ms(1 + Quarter);
  Sound_Play(Tone_F5, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
  Sound_Play(Tone_C6, Sixteenth); Delay_ms(1 + Sixteenth);
  Sound_Play(Tone_A5, Half); Delay_ms(1 + Half);
}

#endif /* INC_MELODY_H_ */