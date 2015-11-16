#include <alarm/Alarm.h>
#include <alarm/Melody.h>
#include <core/Application.h>

/*
 * A riasztás küszöbértéke, amit ha meghalad a hõmérséklet bekapcsol a riasztás.
 */
float threshold = 90.0f;

/*
 * A riasztás állapotát jelölõ jelzõbit, ami a folyamatos riasztás meggátolását
 * szolgálja.
 */
bool isAlerted = false;

/*
 * A riasztás engedélyezettségének jelzõbitje.
 */
bool isThresholdSet = false;


/*
 * Inicializálja a riasztó modult az RC2-es kivezetésre és lead egy egy
 * másodpercig tartó 880Hz-es hangjelzést az inicializáció végeztével.
 */
void Alarm_initialize() {
  Sound_Init(&PORTC, 2);
  Alarm_beep();
}

/*
 * Beállítja a riasztás küszöbértékét, és egyúttal engedélyezi a riasztást.
 */
void Alarm_setThreshold(float _threshold) {
  threshold = _threshold;
  isThresholdSet = true;
}

/*
 * Visszaadja a riasztás küszöbértékét.
 */
float Alarm_getThreshold() {
  return threshold;
}

/*
 * Törli a riasztás küszöbértékét, és egyúttal letiltja a riasztást.
 */
void Alarm_clearThreshold() {
  threshold = 0.0f;
  isThresholdSet = false;
}

/*
 * Ellenõrzi a riasztás feltételeit és végrehajtja a riasztás eseménykezelõjét,
 * ha a feltételek alapján meg kell kezdeni a riasztást.
 */
void Alarm_checkConditions(float _temperature) {
  /* A riasztáshoz szükséges feltételek vizsgálatának megszakítása, ha a
  riasztás inaktív. */
  if(!isThresholdSet) return;
  
  /* A riasztás eseménykezelõjének végrehajtása, ha a hõmérséklet meghaladta a
  küszöböt és korábban nem történt riasztás, illetve a folyamatos riasztást
  meggátoló jelzõbit törlése, ha a hõmérséklet a küszöb alá esett. */
  if(_temperature > threshold && !isAlerted) {
    isAlerted = true;
    Alarm_thresholdExceededEvent();
  }
  else if(_temperature <= threshold && isAlerted) {
    isAlerted = false;
  }
}

/*
 * Lejátssza a riasztó hangjelzést.
 */
void Alarm_playAlarmSound() {
  playTheImperialMarch();
}

/*
 * Lead egy egy másodpercig tartó 880Hz-es hangjelzést.
 */
void Alarm_beep() {
  Sound_Play(880, 1000);
}