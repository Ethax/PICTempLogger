#include <iostream>
#include <string>
#include <app/inc/serialcomm/SerialPort.h>
#include <app/inc/core/DataTypes.h>

using namespace std;

/**
* @brief Az alkalmaz�s bel�p�si pontja, ami az alkalmaz�s
* futtat�sakor el�sz�r h�v�dik meg.
*
* @return Ha nulla, akkor az alkalmaz�s hib�tlanul lefutott.
*/
int main(int argc, char* argv[]) {
	SerialPort serialPort("/dev/ttyUSB0");
	PICTime actualTime;
	float threshold = 0.0f;

	/* A haszn�lati s�g� ki�rat�sa a konzol k�perny�re, ha a megadott
	parancssori argumentumok sz�ma nem megfelel�. */
	if(argc < 2) {
		cout << "Usage:" << endl;
		cout << "  templogger --synctime" << endl;
		cout << "  templogger --threshold <value>" << endl;
		cout << "  templogget --getlog" << endl;
		exit(0);
	}

	/* A megadott parancssori argumentumok feldolgoz�sa �s az �tadott
	�rt�keknek megfelel� m�veletek v�grehajt�sa. */
	for(int i = 1; i < argc; i++) {
		try {
			/* A soros port megnyit�sa. */
			serialPort.openPort();
			
			/* A riaszt�s k�sz�b�rt�k�t megv�ltoztat� �zenet kik�ld�se
			a soros porton keresz�l, ha a parancssori argumentum �rt�ke
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
			/* A mikrovez�rl� �ltal sz�molt id�t a PC idej�vel
			�sszehangol� �zenet kik�ld�se a soros porton keresz�l, ha
			a parancssori argumentum �rt�ke "--synctime". */
			else if(string(argv[i]) == "--synctime") {
				serialPort.writeByte('T');
				serialPort.writeData(actualTime.serialize(), sizeof(PICTime));
				serialPort.writeByte('\n');
			}
			/* A let�rol napl�bejegyz�seket lek�r� �zenet kik�ld�se a
			soros porton keresz�l, ha a parancssori argumentum �rt�ke
			"--getlog". */
			else if(string(argv[i]) == "--getlog") {
				serialPort.writeByte('L');
				serialPort.writeByte('\n');
			}
			/* Hiba megjelen�t�se �s a program fut�s�nak megszak�t�sa, ha
			a parancssori argumentum �rt�ke hib�s. */
			else {
				cout << "Not enough or invalid arguments." << endl;
				exit(0);
			}

			/* A nyugt�z� �zenet meg�rkez�s�nek kiv�r�sa legfeljebb 10
			m�sodpercig. */
			std::string receiveBuffer;
			LogEntry entry;
			while(true) {
				receiveBuffer = serialPort.readLine(10000);
				
				/* A nyugta ki�rat�sa a konzol k�perny�re �s az alkalmaz�s
				fut�s�nak befejez�se, ha a fogadott adatb�jtok �rt�ke
				megegyezik a nyugta �zenet�vel. */
				if(receiveBuffer.find("ACK") != string::npos) {
					cout << receiveBuffer << endl;
					break;
				}
				/* A fogadott adatb�jtok napl�bejegyz�seket t�rol� objektumm�
				alak�t�sa �s ki�rat�sa a konzol k�perny�re. */
				else {
					std::memcpy(&entry, receiveBuffer.c_str(), sizeof(LogEntry));
					cout << entry << endl;
				}
			}
		}
		/* A standart kiv�telek elfog�sa �s a hiba�zenet ki�rat�sa a
		konzol k�perny�re. */
		catch(exception& e) {
			cout << "An exception is thrown: " << e.what() << endl;
			exit(0);
		}
		/* A soros portot kezel� objektumt�l sz�rmaz� kiv�telek elfog�sa
		�s a hiba�zenet ki�rat�sa a konzol k�perny�re. */
		catch(SerialException& e) {
			cout << e.getErrorMessage() << endl;
		}
		/* Az ismeretlen eredet� kiv�telek elfog�sa �s a hiba�zenet
		ki�rat�sa a konzol k�perny�re. */
		catch(...) {
			cout << endl << "Application terminated with an unexpected error." << endl;
		}
	}

	/* A megnyitott soros port lez�r�sa �s az alkalmaz�s fut�s�nak
	befejez�se. */
	if(serialPort.isOpen())
		serialPort.closePort();
	return 0;
}