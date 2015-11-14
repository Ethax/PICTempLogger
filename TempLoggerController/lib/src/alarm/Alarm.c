#include <alarm/Alarm.h>
#include <alarm/Melody.h>
#include <core/Application.h>

/*
 * A riasztás küszöbértéke, amit ha meghalad a hõmérséklet bekapcsol a riasztás.
 */
float Threshold = 0.0f;

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
  Sound_Play(880, 1000);
}

/*
 * Beállítja a riasztás küszöbértékét, és egyúttal engedélyezi a riasztást.
 */
void Alarm_setThreshold(float _threshold) {
  Threshold = _threshold;
  isThresholdSet = true;
}

/*
 * Törli a riasztás küszöbértékét, és egyúttal letiltja a riasztást.
 */
void Alarm_clearThreshold() {
  Threshold = 0.0f;
  isThresholdSet = false;
}

/*
 * Ellenõrzi a riasztás feltételeit és IGAZ értékkel tér vissza, ha a feltételek
 * alapján meg kell kezdeni a riasztást.
 */
bool Alarm_checkConditions(float _temperature) {
  /* A riasztáshoz szükséges feltételek vizsgálatának megszakítása, ha a
  riasztás inaktív. */
  if(!isThresholdSet) return false;
  
  /* A riasztás állapotának módosítása a hõmérséklet jelenlegi értéke és a
  riasztás korábbi állapota alapján és IGAZ érték visszaadása, ha a riasztás
  feltételei teljesültek. */
  if(_temperature > Threshold && !isAlerted) {
    isAlerted = true;
    return true;
  }
  else if(_temperature <= Threshold && isAlerted) {
    isAlerted = false;
  }
  
  /* HAMIS érték visszaadása minden olyan esetben, ha a riasztás feltételei nem
  teljesültek. */
  return false;
}

/* Lejátssza a riasztó hangjelzést. */
void Alarm_playAlarmSound() {
  playTheImperialMarch();
}