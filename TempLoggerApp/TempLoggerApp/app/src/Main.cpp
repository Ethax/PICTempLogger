#include <iostream>
#include <string>
#include <app/inc/serialcomm/SerialPort.h>
#include <app/inc/core/DataTypes.h>

using namespace std;

union {
	float   IEEE_Float;
	unsigned char   uBytes[4];
}  uF;

void convert_ieee_to_microchip(float fval) {
	uF.IEEE_Float = fval;
	unsigned char tempchar_sbit = uF.uBytes[3] & 0x80;   // get IEEE sign bit -- resides in bit 31
	uF.uBytes[3] *= 2;                     // one shift left (drags in a zero on the right)
	if(uF.uBytes[2] & 0x80)                  // if bit 23 is set,
	{
		uF.uBytes[3] |= 0x01;                 // set bit 24 (else it will remain cleared)
		uF.uBytes[2] &= 0x7F;                // clear bit 23
	};
	if(tempchar_sbit)                        // if IEEE sign bit was set,
		uF.uBytes[2] |= 0x80;                  // set bit 23 (else, leave it cleared) 
}

float convert_microchip_to_ieee() {

	unsigned char tempchar_sbit = uF.uBytes[2] & 0x80;   // get Microchip sign bit -- resides in bit 23
	uF.uBytes[2] &= 0x7F;                // clear bit 23
	if(uF.uBytes[3] & 0x01)                  // if bit 24 is set,
		uF.uBytes[2] |= 0x80;                  // set bit 23 (else, leave it cleared)
	uF.uBytes[3] /= 2;                     // one shift right (drags in a zero on the left)
	if(tempchar_sbit)                        // if Microchip sign bit was set,
		uF.uBytes[3] |= 0x80;                  // set bit 31 (else, leave it cleared) 

	return uF.IEEE_Float;
}

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
	unsigned char transmitBuffer[20] = { 0 };

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
	értékek letárolása. */
	for(int i = 1; i < argc; i++) {
		try {
			serialPort.openPort();
			if(string(argv[i]) == "--threshold") {
				threshold = stof(string(argv[++i]));
				if(threshold < 0.0f || threshold > 99.0f) {
					cout << "Invalid threshold. The value must be between 0 and 99." << endl;
					exit(0);
				}

				convert_ieee_to_microchip(threshold);

				serialPort.writeByte('R');
				serialPort.writeData(uF.uBytes, sizeof(float));
				serialPort.writeByte('\n');
			}
			else if(string(argv[i]) == "--synctime") {
				serialPort.writeByte('T');
				serialPort.writeData(actualTime.serialize(), sizeof(PICTime));
				serialPort.writeByte('\n');
			}
			else if(string(argv[i]) == "--getlog") {
				serialPort.writeByte('L');
				serialPort.writeByte('\n');
			}
			else {
				cout << "Not enough or invalid arguments." << endl;
				exit(0);
			}

			std::string receiveBuffer;
			LogEntry entry;

			while(true) {
				receiveBuffer = serialPort.readLine(10000);
				if(receiveBuffer.find("ACK") != string::npos) {
					cout << receiveBuffer << endl;
					break;
				}
				else {
					std::memcpy(&entry, receiveBuffer.c_str(), sizeof(LogEntry));
					uF.IEEE_Float = entry.value;

					cout << entry << convert_microchip_to_ieee() << endl;
				}
			}
		}
		catch(exception& e) {
			cout << "An exception is thrown: " << e.what() << endl;
			exit(0);
		}
		catch(SerialException& e) {
			cout << e.getErrorMessage() << endl;
		}
		catch(...) {
			cout << endl << "Application terminated with an unexpected error." << endl;
		}
	}

	/* Az alkalmazás futásának befejezése. */
	if(serialPort.isOpen())
		serialPort.closePort();
	return 0;
}