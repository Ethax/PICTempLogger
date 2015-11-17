#line 1 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
#line 1 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/include/built_in.h"
#line 1 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/include/stdint.h"




typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;



typedef signed char int_fast8_t;
typedef signed int int_fast16_t;
typedef signed long int int_fast32_t;


typedef unsigned char uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned long int uint_fast32_t;


typedef signed int intptr_t;
typedef unsigned int uintptr_t;


typedef signed long int intmax_t;
typedef unsigned long int uintmax_t;
#line 1 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/include/stdbool.h"
#line 10 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/include/stdbool.h"
typedef unsigned char _Bool;
#line 1 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/include/stdarg.h"





typedef void * va_list[1];
#line 18 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
typedef void (*EventHandler)(void);
#line 28 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
typedef struct event_queue_t {
#line 32 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
 uint8_t end;
#line 37 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
 uint8_t begin;
#line 42 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
 EventHandler eventHandlers[ 20 ];
} EventQueue;
#line 49 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
void Application_initialize();
#line 57 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
void Application_dispatchEvent(EventHandler handler);
#line 63 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
void Application_handleEvents();
#line 69 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
void Application_run();
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
#line 15 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
typedef struct pic_time_t {
#line 19 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
 uint8_t second;
#line 24 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
 uint8_t minute;
#line 29 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
 uint8_t hour;
#line 34 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
 uint8_t day;
#line 39 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
 uint8_t month;
#line 44 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
 uint8_t year;
} PICTime;
#line 52 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
void Timer_initialize();
#line 61 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
void Timer_handleInterrupt();
#line 68 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
PICTime* Timer_getSystemTime();
#line 76 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
void Timer_setSystemTime(PICTime* time_ptr);
#line 85 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
char* Timer_timeToString(PICTime* time_ptr);
#line 91 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
extern void Timer_elapsedSecondEvent();
#line 97 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
extern void Timer_elapsedMinuteEvent();
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/display.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
#line 10 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/display.h"
void Display_initialize();
#line 22 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/display.h"
void Display_writeLine(uint8_t line, char* format, ...);
#line 29 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/display.h"
void Display_clearLine(uint8_t line);
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/tempsensor/sensor.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
#line 13 "c:/projects/pictemplogger/temploggercontroller/lib/inc/tempsensor/sensor.h"
void Sensor_initialize(const float _vref);
#line 29 "c:/projects/pictemplogger/temploggercontroller/lib/inc/tempsensor/sensor.h"
float Sensor_getTemperature();
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
#line 10 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
void Alarm_initialize();
#line 18 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
void Alarm_setThreshold(float _threshold);
#line 25 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
float Alarm_getThreshold();
#line 30 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
void Alarm_clearThreshold();
#line 43 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
void Alarm_checkConditions(float _temperature);
#line 48 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
void Alarm_playAlarmSound();
#line 53 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
void Alarm_beep();
#line 59 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
extern void Alarm_thresholdExceededEvent();
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
#line 22 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
typedef struct storable_data_t {
#line 26 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
 PICTime systemTime;
#line 31 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
 float threshold;
#line 36 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
 uint8_t logBegin;
#line 41 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
 uint8_t logEnd;
} StorableData;
#line 52 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
typedef struct log_t {
#line 56 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
 PICTime timeStamp;
#line 61 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
 float value;
} LogEntry;
#line 71 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
void Storage_initialize();
#line 78 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
void Storage_resetLogCounter();
#line 86 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
StorableData* Storage_getStoredSettings();
#line 95 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
void Storage_storeSettings(PICTime* _systemTime, float _threshold);
#line 103 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
void Storage_writeLog(PICTime* timeStamp, float value);
#line 116 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
LogEntry* Storage_readEarliestLog();
#line 123 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
extern void Storage_settingsLoadedEvent();
#line 130 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
extern void Storage_firstBootEvent();
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
#line 10 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
enum BaudRate {
 BAUD_1200, BAUD_2400, BAUD_4800, BAUD_9600, BAUD_19200, BAUD_38400,
 BAUD_57600, BAUD_115200
};
#line 22 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
void Serial_initialize(enum BaudRate baudrate);
#line 31 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
void Serial_handleInterrupt();
#line 41 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
void* Serial_getReceivedData();
#line 48 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
void Serial_sendLogEntry(LogEntry* entry);
#line 53 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
void Serial_sendAcknowledgement();
#line 59 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
extern void Serial_receivedTimeSettingEvent();
#line 65 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
extern void Serial_receivedThresholdSettingEvent();
#line 71 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
extern void Serial_receivedLogRequestEvent();
#line 12 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
volatile EventQueue eventQueue = { 0, 0, { 0 }};
#line 18 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Application_initialize() {
#line 21 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 TRISA = TRISB = TRISC = TRISD = TRISE = 0xFF;
 ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = 0x00;
 SLRCON = LATA = LATB = LATC = LATD = LATE = 0x00;


 ADCON0 = ADCON1 = ADCON2 = 0x00;
 C1ON_bit = C2ON_bit =  0 ;


 Display_initialize();
 Alarm_initialize();
 Timer_initialize();
 Sensor_initialize(3.3f);
 Storage_initialize();
 Serial_initialize(BAUD_9600);
}
#line 42 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Application_dispatchEvent(EventHandler handler) {
#line 45 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 eventQueue.eventHandlers[eventQueue.end] = handler;
 eventQueue.end = (eventQueue.end + 1) %  20 ;
#line 51 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 if(eventQueue.end == eventQueue.begin)
 eventQueue.begin = (eventQueue.begin + 1) %  20 ;
}
#line 59 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Application_handleEvents() {

 if(eventQueue.begin == eventQueue.end) return;
#line 66 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 if(eventQueue.eventHandlers[eventQueue.begin]) {
 eventQueue.eventHandlers[eventQueue.begin]();
 eventQueue.eventHandlers[eventQueue.begin] = 0;
 }


 eventQueue.begin = (eventQueue.begin + 1) %  20 ;
}
#line 79 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Application_run() {
#line 82 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 IPEN_bit =  0 ;
 PEIE_bit = GIE_bit =  1 ;


 while( 1 ) Application_handleEvents();
}
#line 92 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Storage_firstBootEvent() {
 PICTime default_time;


 Display_writeLine(1, "Loading defaults");
 Display_clearLine(2);
 Delay_ms(1000);


 default_time.second = 0;
 default_time.minute = 0;
 default_time.hour = 0;
 default_time.day = 1;
 default_time.month = 1;
 default_time.year = 70;
 Timer_setSystemTime(&default_time);


 Alarm_setThreshold(90.0f);


 Storage_resetLogCounter();
}
#line 119 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Storage_settingsLoadedEvent() {

 StorableData* settings_ptr = Storage_getStoredSettings();
 Timer_setSystemTime(&settings_ptr->systemTime);
 Alarm_setThreshold(settings_ptr->threshold);
}
#line 129 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Timer_elapsedSecondEvent() {

 float actual_temp = Sensor_getTemperature();
#line 136 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 char* date_str = Timer_timeToString(Timer_getSystemTime());
 char* time_str = strstr(date_str, " ");
 *time_str++ = '\0';
#line 142 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 Display_writeLine(1, "%a   [T]", date_str);
 Display_writeLine(2, "%a %2f%cC", time_str, actual_temp, 223);
#line 147 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 Alarm_checkConditions(actual_temp);
}
#line 153 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Timer_elapsedMinuteEvent() {

 Storage_writeLog(Timer_getSystemTime(), Sensor_getTemperature());
 Delay_ms(5);
 Storage_storeSettings(Timer_getSystemTime(), Alarm_getThreshold());
}
#line 163 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Alarm_thresholdExceededEvent() {

 Display_writeLine(1, "     ALARM!");
 Display_clearLine(2);
 Alarm_playAlarmSound();
}
#line 173 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Serial_receivedTimeSettingEvent() {

 Timer_setSystemTime((PICTime*)Serial_getReceivedData());
 Serial_sendAcknowledgement();
}
#line 182 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Serial_receivedThresholdSettingEvent() {
#line 185 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 Alarm_setThreshold(*(float*)Serial_getReceivedData());
 Serial_sendAcknowledgement();


 Display_writeLine(1, "New threshold:");
 Display_writeLine(2, "%2f%cC", Alarm_getThreshold(), 223);
 Delay_ms(1000);
}
#line 197 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Serial_receivedLogRequestEvent() {

 LogEntry* entry;
 while((entry = Storage_readEarliestLog()))
 Serial_sendLogEntry(entry);


 Serial_sendAcknowledgement();
}
