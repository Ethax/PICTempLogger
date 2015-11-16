#include <alarm/Alarm.h>
#include <alarm/Melody.h>
#include <core/Application.h>

/*
 * A riaszt�s k�sz�b�rt�ke, amit ha meghalad a h�m�rs�klet bekapcsol a riaszt�s.
 */
float threshold = 90.0f;

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
  Alarm_beep();
}

/*
 * Be�ll�tja a riaszt�s k�sz�b�rt�k�t, �s egy�ttal enged�lyezi a riaszt�st.
 */
void Alarm_setThreshold(float _threshold) {
  threshold = _threshold;
  isThresholdSet = true;
}

/*
 * Visszaadja a riaszt�s k�sz�b�rt�k�t.
 */
float Alarm_getThreshold() {
  return threshold;
}

/*
 * T�rli a riaszt�s k�sz�b�rt�k�t, �s egy�ttal letiltja a riaszt�st.
 */
void Alarm_clearThreshold() {
  threshold = 0.0f;
  isThresholdSet = false;
}

/*
 * Ellen�rzi a riaszt�s felt�teleit �s v�grehajtja a riaszt�s esem�nykezel�j�t,
 * ha a felt�telek alapj�n meg kell kezdeni a riaszt�st.
 */
void Alarm_checkConditions(float _temperature) {
  /* A riaszt�shoz sz�ks�ges felt�telek vizsg�lat�nak megszak�t�sa, ha a
  riaszt�s inakt�v. */
  if(!isThresholdSet) return;
  
  /* A riaszt�s esem�nykezel�j�nek v�grehajt�sa, ha a h�m�rs�klet meghaladta a
  k�sz�b�t �s kor�bban nem t�rt�nt riaszt�s, illetve a folyamatos riaszt�st
  megg�tol� jelz�bit t�rl�se, ha a h�m�rs�klet a k�sz�b al� esett. */
  if(_temperature > threshold && !isAlerted) {
    isAlerted = true;
    Alarm_thresholdExceededEvent();
  }
  else if(_temperature <= threshold && isAlerted) {
    isAlerted = false;
  }
}

/*
 * Lej�tssza a riaszt� hangjelz�st.
 */
void Alarm_playAlarmSound() {
  playTheImperialMarch();
}

/*
 * Lead egy egy m�sodpercig tart� 880Hz-es hangjelz�st.
 */
void Alarm_beep() {
  Sound_Play(880, 1000);
}