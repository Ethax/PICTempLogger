#include <alarm/Alarm.h>
#include <alarm/Melody.h>
#include <core/Application.h>

/*
 * A riaszt�s k�sz�b�rt�ke, amit ha meghalad a h�m�rs�klet bekapcsol a riaszt�s.
 */
float Threshold = 0.0f;

/*
 * A riaszt�s �llapot�t jel�l� jelz�bit, ami a folyamatos riaszt�s megg�tol�s�t
 * szolg�lja.
 */
bool isAlerted = false;

/*
 * A riaszt�s enged�lyezetts�g�nek jelz�bitje.
 */
bool isThresholdSet = false;


/*
 * Inicializ�lja a riaszt� modult az RC2-es kivezet�sre �s lead egy egy
 * m�sodpercig tart� 880Hz-es hangjelz�st az inicializ�ci� v�gezt�vel.
 */
void Alarm_initialize() {
  Sound_Init(&PORTC, 2);
  Sound_Play(880, 1000);
}

/*
 * Be�ll�tja a riaszt�s k�sz�b�rt�k�t, �s egy�ttal enged�lyezi a riaszt�st.
 */
void Alarm_setThreshold(float _threshold) {
  Threshold = _threshold;
  isThresholdSet = true;
}

/*
 * T�rli a riaszt�s k�sz�b�rt�k�t, �s egy�ttal letiltja a riaszt�st.
 */
void Alarm_clearThreshold() {
  Threshold = 0.0f;
  isThresholdSet = false;
}

/*
 * Ellen�rzi a riaszt�s felt�teleit �s IGAZ �rt�kkel t�r vissza, ha a felt�telek
 * alapj�n meg kell kezdeni a riaszt�st.
 */
bool Alarm_checkConditions(float _temperature) {
  /* A riaszt�shoz sz�ks�ges felt�telek vizsg�lat�nak megszak�t�sa, ha a
  riaszt�s inakt�v. */
  if(!isThresholdSet) return false;
  
  /* A riaszt�s �llapot�nak m�dos�t�sa a h�m�rs�klet jelenlegi �rt�ke �s a
  riaszt�s kor�bbi �llapota alapj�n �s IGAZ �rt�k visszaad�sa, ha a riaszt�s
  felt�telei teljes�ltek. */
  if(_temperature > Threshold && !isAlerted) {
    isAlerted = true;
    return true;
  }
  else if(_temperature <= Threshold && isAlerted) {
    isAlerted = false;
  }
  
  /* HAMIS �rt�k visszaad�sa minden olyan esetben, ha a riaszt�s felt�telei nem
  teljes�ltek. */
  return false;
}

/* Lej�tssza a riaszt� hangjelz�st. */
void Alarm_playAlarmSound() {
  playTheImperialMarch();
}