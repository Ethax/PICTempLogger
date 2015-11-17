#include <iostream>
#include <string>
#include <app/inc/serialcomm/SerialPort.h>
#include <app/inc/core/DataTypes.h>

using namespace std;

/**
* @brief Az alkalmazás belépési pontja, ami az alkalmazás
* futtatásakor elõször hívódik meg.
*
* @return Ha nulla, akkor az alkalmazás hibátlanul lefutott.
*/
int main(int argc, char* argv[]) {
	SerialPort serialPort("/dev/ttyUSB0");
	PICTime actualTime;
	float threshold = 0.0f;

	/* A használati súgó kiíratása a konzol képernyõre, ha a megadott
	parancssori argumentumok száma nem megfelelõ. */
	if(argc < 2) {
		cout << "Usage:" << endl;
		cout << "  templogger --synctime" << endl;
		cout << "  templogger --threshold <value>" << endl;
		cout << "  templogget --getlog" << endl;
		exit(0);
	}

	/* A megadott parancssori argumentumok feldolgozása és az átadott
	értékeknek megfelelõ mûveletek végrehajtása. */
	for(int i = 1; i < argc; i++) {
		try {
			/* A soros port megnyitása. */
			serialPort.openPort();
			
			/* A riasztás küszöbértékét megváltoztató üzenet kiküldése
			a soros porton kereszül, ha a parancssori argumentum értéke
			"--threshold". */
			if(string(argv[i]) == "--threshold") {
				threshold = stof(string(argv[++i]));
				if(threshold < 0.0f || threshold > 99.0f) {
					cout << "Invalid threshold. The value must be between 0 and 99." << endl;
					exit(0);
				}
				serialPort.writeByte('R');
				serialPort.writeData(FloatUtils::convertIEEE754ToMicrochip(threshold), 4);
				serialPort.writeByte('\n');
			}
			/* A mikrovezérlõ által számolt idõt a PC idejével
			összehangoló üzenet kiküldése a soros porton kereszül, ha
			a parancssori argumentum értéke "--synctime". */
			else if(string(argv[i]) == "--synctime") {
				serialPort.writeByte('T');
				serialPort.writeData(actualTime.serialize(), sizeof(PICTime));
				serialPort.writeByte('\n');
			}
			/* A letárol naplóbejegyzéseket lekérõ üzenet kiküldése a
			soros porton kereszül, ha a parancssori argumentum értéke
			"--getlog". */
			else if(string(argv[i]) == "--getlog") {
				serialPort.writeByte('L');
				serialPort.writeByte('\n');
			}
			/* Hiba megjelenítése és a program futásának megszakítása, ha
			a parancssori argumentum értéke hibás. */
			else {
				cout << "Not enough or invalid arguments." << endl;
				exit(0);
			}

			/* A nyugtázó üzenet megérkezésének kivárása legfeljebb 10
			másodpercig. */
			std::string receiveBuffer;
			LogEntry entry;
			while(true) {
				receiveBuffer = serialPort.readLine(10000);
				
				/* A nyugta kiíratása a konzol képernyõre és az alkalmazás
				futásának befejezése, ha a fogadott adatbájtok értéke
				megegyezik a nyugta üzenetével. */
				if(receiveBuffer.find("ACK") != string::npos) {
					cout << receiveBuffer << endl;
					break;
				}
				/* A fogadott adatbájtok naplóbejegyzéseket tároló objektummá
				alakítása és kiíratása a konzol képernyõre. */
				else {
					std::memcpy(&entry, receiveBuffer.c_str(), sizeof(LogEntry));
					cout << entry << endl;
				}
			}
		}
		/* A standart kivételek elfogása és a hibaüzenet kiíratása a
		konzol képernyõre. */
		catch(exception& e) {
			cout << "An exception is thrown: " << e.what() << endl;
			exit(0);
		}
		/* A soros portot kezelõ objektumtól származó kivételek elfogása
		és a hibaüzenet kiíratása a konzol képernyõre. */
		catch(SerialException& e) {
			cout << e.getErrorMessage() << endl;
		}
		/* Az ismeretlen eredetû kivételek elfogása és a hibaüzenet
		kiíratása a konzol képernyõre. */
		catch(...) {
			cout << endl << "Application terminated with an unexpected error." << endl;
		}
	}

	/* A megnyitott soros port lezárása és az alkalmazás futásának
	befejezése. */
	if(serialPort.isOpen())
		serialPort.closePort();
	return 0;
}