#include <app/inc/serialcomm/SerialPort.h>

SerialPort::SerialPort(const std::string& deviceName) :
    deviceFile(deviceName),
    isPortOpen(false),
    fileDescriptor(-1),
    initialPortSettings(),
    inputBuffer() {}

SerialPort::~SerialPort() {
  if(isPortOpen)
    closePort();
  return;
}

/*
 * Megnyitja és beállítja a soros porti kommunikációt.
 */
void SerialPort::openPort(
  const BaudRate baudRate,
  const CharacterSize charSize,
  const Parity parityType,
  const StopBits stopBits,
  const FlowControl flowControl)
{
  /* Kivétel dobása, ha a soros port már nyitva van. */
  if(isPortOpen)
    throw SerialException(SerialException::ALREADY_OPEN, "Serial port already open.");

  /* A soros port megnyitása és kivétel dobása, ha a megnyitás nem sikerült. */
  fileDescriptor = open(deviceFile.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
  if(fileDescriptor < 0)
    throw SerialException(SerialException::OPEN_FAILED, strerror(errno));

  /* A soros port korábbi beállításainak letárolása és kivétel dobása, ha a
  beállítások letárolása nem sikerült. */
  if(tcgetattr(fileDescriptor, &initialPortSettings) < 0)
    throw SerialException(SerialException::OPEN_FAILED, strerror(errno));

  /* A soros port új beállításait tartalmazó struktúra létrehozása és nullára
  inicializálása. */
  termios newPortSettings;
  memset(&newPortSettings, 0, sizeof(newPortSettings));

  /* A vevő engdedélyezése (CREAD) és a hardvervezérlő vonalak mellőzése (CLOCAL). */
  newPortSettings.c_cflag |= CREAD | CLOCAL;

  /* A vevő beállítása nem-kanonikus és a paritáshibával rendelkező bájtokat mellőző
  bemenetnek. (Nem-kanonikus üzemmódban a vevő nem küld jelzéseket vagy visszhangokat az
  üzemeltető program felé.) */
  newPortSettings.c_lflag = 0;
  newPortSettings.c_iflag = IGNPAR;

  /* Az adó beállítása nyers kimenetnek. */
  newPortSettings.c_oflag = 0;

  /* A VMIN és a VTIME paraméterek nullázása. (Karakterorientált (nyers) üzemmódban
  a VMIN a karakterek számának alsó határát, a VTIME pedig az időkorlátot jelentik.
  A VTIME értékét deciszekundumokban kell megadni.) */
  newPortSettings.c_cc[VMIN] = 0;
  newPortSettings.c_cc[VTIME] = 0;

  /* A soros port fogadó pufferének törlése és kivétel dobása, ha a törlés nem
  sikerült. */
  if(tcflush(fileDescriptor, TCIFLUSH) < 0)
    throw SerialException(SerialException::OPEN_FAILED, strerror(errno));

  /* A soros port új beállításainak érvénybe léptetése és kivétel dobása, ha a
  művelet nem sikerült. */
  if(tcsetattr(fileDescriptor, TCSANOW, &newPortSettings) < 0)
    throw SerialException(SerialException::OPEN_FAILED, strerror(errno));

  /* A soros port megnyitásának befejezése. */
  isPortOpen = true;

  /* A soros port további beállításainak életbe léptetése a paramétereknek
  megfelelően. */
  setBaudRate(baudRate);
  setCharSize(charSize);
  setParity(parityType);
  setNumOfStopBits(stopBits);
  setFlowControl(flowControl);
}

/* Leellenőrzi, hogy a soros kommunikáció nyitott-e vagy sem. */
bool SerialPort::isOpen() const {
  return isPortOpen;
}

/*
 * Lezárja a korábban menyitott soros porti kommunikációt és visszaállítja a
 * megnyitáskor lementett beállításokat.
 */
void SerialPort::closePort() {
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
  if(!isPortOpen)
    throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  /* A soros port korábbi beállításainak visszaállítása, és a fájlleíró
  lezárása. */
  tcsetattr(fileDescriptor, TCSANOW, &initialPortSettings);
  close(fileDescriptor);

  /* A soros port lezárásának befejezése. */
  isPortOpen = false;
}

/*
 * Módosítja a korábban megnyitott soros porti kommunikáció adatátviteli
 * sebességét.
 */
void SerialPort::setBaudRate(const BaudRate baudRate) {
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
  if(!isPortOpen)
    throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  /* A soros port aktuális beállításainak lekérdezése és kivétel dobása, ha a
  lekérdezés meghiúsult. */
  termios actualPortSettings;
  if(tcgetattr(fileDescriptor, &actualPortSettings) < 0)
    throw SerialException(SerialException::RUNTIME_ERROR, strerror(errno));

  /* Az olvasás és az írás adatátviteli sebességeinek beállítása és kivétel dobása,
  ha a beállítás nem sikerült. */
  if((cfsetispeed(&actualPortSettings, baudRate) < 0) ||
    (cfsetospeed(&actualPortSettings, baudRate) < 0))
    throw SerialException(
      SerialException::UNSUPPORTED_SETUP_PARAMETER, "Unsupported baud rate."
    );

  /* A soros port beállításainak módosítása az új értékeknek megfelelően, és kivétel
  dobása, ha a művelet meghiúsult. */
  if(tcsetattr(fileDescriptor, TCSANOW, &actualPortSettings) < 0)
    throw SerialException(
      SerialException::UNSUPPORTED_SETUP_PARAMETER, strerror(errno)
    );
}

/*
 * Visszaadja a korábban megnyitott soros porti kommunikáció adatátviteli
 * sebességet.
 */
SerialPort::BaudRate SerialPort::getBaudRate() const {
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
  if(!isPortOpen)
    throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  /* A soros port aktuális beállításainak lekérdezése és kivétel dobása, ha a
  lekérdezés meghiúsult. */
  termios actualPortSettings;
  if(tcgetattr(fileDescriptor, &actualPortSettings) < 0)
    throw SerialException(SerialException::RUNTIME_ERROR, strerror(errno));

  /* Az aktuális beállításoknak megfelelő adatátviteli sebesség visszaadása. */
  return SerialPort::BaudRate(cfgetispeed(&actualPortSettings));
}

/* Módosítja a korábban megnyitott soros porti kommunikáció karaktereinek
szélességét. */
void SerialPort::setCharSize(const CharacterSize charSize) {
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
  if(!isPortOpen)
    throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  /* A soros port aktuális beállításainak lekérdezése és kivétel dobása, ha a
  lekérdezés meghiúsult. */
  termios actualPortSettings;
  if(tcgetattr(fileDescriptor, &actualPortSettings) < 0)
    throw SerialException(SerialException::RUNTIME_ERROR, strerror(errno));

  /* A karakterszélesség beállítása a megadott értéknek megfelelően. */
  actualPortSettings.c_cflag &= ~CSIZE;
  actualPortSettings.c_cflag |= charSize;

  /* A soros port beállításainak módosítása az új értékeknek megfelelően, és kivétel
  dobása, ha a művelet meghiúsult. */
  if(tcsetattr(fileDescriptor, TCSANOW, &actualPortSettings) < 0)
    throw SerialException(
      SerialException::UNSUPPORTED_SETUP_PARAMETER, strerror(errno)
    );
}

/* Visszaadja a korábban megnyitott soros porti kommunikáció által használt
karakterszélességet. */
SerialPort::CharacterSize SerialPort::getCharSize() const {
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
  if(!isPortOpen)
    throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  /* A soros port aktuális beállításainak lekérdezése és kivétel dobása, ha a
  lekérdezés meghiúsult. */
  termios actualPortSettings;
  if(tcgetattr(fileDescriptor, &actualPortSettings) < 0)
    throw SerialException(SerialException::RUNTIME_ERROR, strerror(errno));

  /* Az aktuális beállításoknak megfelelő karakterszélesség visszaadása. */
  return SerialPort::CharacterSize(actualPortSettings.c_cflag & CSIZE);
}

/*
 * Módosítja a korábban megnyitott soros porti kommunikáció paritásának típusát.
 */
void SerialPort::setParity(const Parity parityType) {
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
    if(!isPortOpen)
      throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  /* A soros port aktuális beállításainak lekérdezése és kivétel dobása, ha a
  lekérdezés meghiúsult. */
  termios actualPortSettings;
  if(tcgetattr(fileDescriptor, &actualPortSettings) < 0)
    throw SerialException(SerialException::RUNTIME_ERROR, strerror(errno));

  /* A paritás típusának beállítása a megadott értéknek megfelelően, és kivétel
  dobása, ha az átadott érték nem megfelelő. */
  switch(parityType) {
  case SerialPort::PARITY_EVEN:
    actualPortSettings.c_cflag |= PARENB;
    actualPortSettings.c_cflag &= ~PARODD;
    actualPortSettings.c_iflag |= INPCK;
    break;
  case SerialPort::PARITY_ODD:
    actualPortSettings.c_cflag |= ( PARENB | PARODD );
    actualPortSettings.c_iflag |= INPCK;
    break;
  case SerialPort::PARITY_NONE:
    actualPortSettings.c_cflag &= ~(PARENB);
    actualPortSettings.c_iflag |= IGNPAR;
    break;
  default:
    throw SerialException(
      SerialException::UNSUPPORTED_SETUP_PARAMETER, "Invalid parity setting."
    );
    break;
  }

  /* A soros port beállításainak módosítása az új értékeknek megfelelően, és kivétel
  dobása, ha a művelet meghiúsult. */
  if(tcsetattr(fileDescriptor, TCSANOW, &actualPortSettings) < 0)
    throw SerialException(
      SerialException::UNSUPPORTED_SETUP_PARAMETER, strerror(errno)
    );
}

/*
 * Visszaadja a korábban megnyitott soros porti kommunikáció paritásának típusát.
 */
SerialPort::Parity SerialPort::getParity() const {
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
  if(!isPortOpen)
    throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  /* A soros port aktuális beállításainak lekérdezése és kivétel dobása, ha a
  lekérdezés meghiúsult. */
  termios actualPortSettings;
  if(tcgetattr(fileDescriptor, &actualPortSettings) < 0)
    throw SerialException(SerialException::RUNTIME_ERROR, strerror(errno));

  /* Az aktuális beállításoknak megfelelő paritás típus visszaadása. */
  if(actualPortSettings.c_cflag & PARENB) {
    if(actualPortSettings.c_cflag & PARODD)
      return SerialPort::PARITY_ODD;
    else
      return SerialPort::PARITY_EVEN;
  }
  return SerialPort::PARITY_NONE;
}

/*
 * Módosítja a korábban megnyitott soros porti kommunikáció stop bitjeinek
 * számát.
 */
void SerialPort::setNumOfStopBits(const StopBits numOfStopBits) {
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
  if(!isPortOpen)
    throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  /* A soros port aktuális beállításainak lekérdezése és kivétel dobása, ha a
  lekérdezés meghiúsult. */
  termios actualPortSettings;
  if(tcgetattr(fileDescriptor, &actualPortSettings) < 0)
    throw SerialException(SerialException::RUNTIME_ERROR, strerror(errno));

  /* Stop bitek számának beállítása a megadott értéknek megfelelően, és kivétel
  dobása, ha az átadott érték nem megfelelő. */
  switch(numOfStopBits) {
  case SerialPort::STOP_BITS_1:
    actualPortSettings.c_cflag &= ~(CSTOPB);
    break;
  case SerialPort::STOP_BITS_2:
    actualPortSettings.c_cflag |= CSTOPB;
    break;
  default:
    throw SerialException(
      SerialException::UNSUPPORTED_SETUP_PARAMETER, "Invalid number of stop bits."
    );
    break;
  }

  /* A soros port beállításainak módosítása az új értékeknek megfelelően, és kivétel
  dobása, ha a művelet meghiúsult. */
  if(tcsetattr(fileDescriptor, TCSANOW, &actualPortSettings) < 0)
    throw SerialException(
      SerialException::UNSUPPORTED_SETUP_PARAMETER, strerror(errno)
    );
}

/*
 * Visszaadja a korábban megnyitott soros porti kommunikáció aktuális stop bitjeinek
 * számát.
 */
SerialPort::StopBits SerialPort::getNumOfStopBits() const {
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
  if(!isPortOpen)
    throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  /* A soros port aktuális beállításainak lekérdezése és kivétel dobása, ha a
  lekérdezés meghiúsult. */
  termios actualPortSettings;
  if(tcgetattr(fileDescriptor, &actualPortSettings) < 0)
    throw SerialException(SerialException::RUNTIME_ERROR, strerror(errno));

  /* Az aktuális beállításoknak egyező stop bitek számának visszaadása. */
  if(actualPortSettings.c_cflag & CSTOPB)
    return SerialPort::STOP_BITS_2;
  return SerialPort::STOP_BITS_1;
}

/*
 * Módosítja a korábban megnyitott soros porti kommunikáció hardvervezérlésének
 * módját.
 */
void SerialPort::setFlowControl(const FlowControl flowControl) {
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
  if(!isPortOpen)
    throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  /* A soros port aktuális beállításainak lekérdezése és kivétel dobása, ha a
  lekérdezés meghiúsult. */
  termios actualPortSettings;
  if(tcgetattr(fileDescriptor, &actualPortSettings) < 0)
    throw SerialException(SerialException::RUNTIME_ERROR, strerror(errno));

  /* A hardvervezérlésének módjának beállítása a megadott értéknek megfelelően,
  és kivétel dobása, ha az átadott érték nem megfelelő. */
  switch(flowControl) {
  case SerialPort::FLOW_CONTROL_HARD:
    actualPortSettings.c_cflag |= CRTSCTS;
    break;
  case SerialPort::FLOW_CONTROL_NONE:
    actualPortSettings.c_cflag &= ~(CRTSCTS);
    break;
  default:
    throw SerialException(
      SerialException::UNSUPPORTED_SETUP_PARAMETER, "Invalid flow control."
    );
    break;
  }

  /* A soros port beállításainak módosítása az új értékeknek megfelelően, és kivétel
  dobása, ha a művelet meghiúsult. */
  if(tcsetattr(fileDescriptor, TCSANOW, &actualPortSettings) < 0)
    throw SerialException(
      SerialException::UNSUPPORTED_SETUP_PARAMETER, strerror(errno)
    );
}

/*
 * Visszaadja a korábban megnyitott soros porti kommunikáció aktuálisan alkalmazott
 * hardvervezérlésének módját.
 */
SerialPort::FlowControl SerialPort::getFlowControl() const {
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
  if(!isPortOpen)
    throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  /* A soros port aktuális beállításainak lekérdezése és kivétel dobása, ha a
  lekérdezés meghiúsult. */
  termios actualPortSettings;
  if(tcgetattr(fileDescriptor, &actualPortSettings) < 0)
    throw SerialException(SerialException::RUNTIME_ERROR, strerror(errno));

  /* Az aktuális beállításoknak egyező hardvervezérlés visszaadása. */
  if(actualPortSettings.c_cflag & CRTSCTS)
    return SerialPort::FLOW_CONTROL_HARD;
  return SerialPort::FLOW_CONTROL_NONE;
}

/* Leellenőrzi, hogy van-e új adat a fogadó pufferben. */
bool SerialPort::isDataAvailable() const {
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
  if(!isPortOpen)
    throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  /* IGAZ vagy HAMIS érték visszaadása attól függően, hogy a fodagó puffer üres-e
  vagy sem. */
  return (inputBuffer.size() > 0 ? true : false);
}

/*
 * Beolvas egy egybájtnyi adatot a soros portról.
 */
unsigned char SerialPort::readByte(const unsigned int msTimeout) {
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
  if(!isPortOpen)
    throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  /* Az aktuális időpillanat lekérdezése. */
  auto startTime = std::chrono::high_resolution_clock::now();

  /* Várakozás a soros portról fogadható bájtok beérkezésére, amennyiben a fogadó
  puffer üres. */
  do {
    /* Időtúllépés ellenőrzése és kivétel dobása, ha az adatokra várakozás túllépte
    a megszabott időkorlátot. */
    if(msTimeout) {
      std::chrono::duration<double, std::milli> elapsedTime =
        std::chrono::high_resolution_clock::now() - startTime;
      if((unsigned int)elapsedTime.count() >= msTimeout)
        throw SerialException(SerialException::READ_TIMEOUT, "Read timeout.");
    }

    /* A soros porton elérhető bájtok számának lekérdezése és kivétel dobása, ha
    a lekérdezés nem sikerült. */
    int numberOfBytesAvailable = 0;
    if(ioctl(fileDescriptor, FIONREAD, &numberOfBytesAvailable ) < 0)
      throw SerialException(
        SerialException::RUNTIME_ERROR, "File descriptor cannot be read."
      );

    /* Az elérhető bájtok beolvasása a soros portról a fogadó pufferbe. */
    for(int i = 0; i < numberOfBytesAvailable; i++) {
      unsigned char nextByte;
      if(read(fileDescriptor, &nextByte, 1) > 0)
        inputBuffer.push(nextByte);
      else
        break;
    }

    /* Egy másodperces várakozás a következő olvasási kísérletig, ha a fogadó
    puffer üres. */
    if(!inputBuffer.size())
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
  } while(!inputBuffer.size());

  /* A fogadó puffer legutolsó bájtjának kiolvasása és visszaadása. */
  unsigned char nextChar = inputBuffer.front();
  inputBuffer.pop();
  return nextChar;
}

/* Beolvas egy meghatározott hosszúságú vagy minden elérhető adatot a
soros portról. */
void SerialPort::readData(
  std::vector<unsigned char>& dataBuffer,
  const unsigned int numOfBytes,
  const unsigned int msTimeout)
{
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
  if(!isPortOpen)
    throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  /* Az beolvasott adatokat tároló puffer ürítése és az adatok beolvasása
  a soros portról. */
  dataBuffer.resize(0);
  if(!numOfBytes) {
    /* Minden elérhető adat beolvasása az időkorláton belül. (Az időkorlátnak
    csak addig van jelentősége, amíg az első bájtok meg nem érkeznek a soros
    portról, onnantól a beolvasás csak addig tart, amíg az adatok folyamatosan
    érkeznek.) */
    do {
      dataBuffer.push_back(readByte(msTimeout ? msTimeout : 10000));
    } while(isDataAvailable());
  }
  else {
    /* Az kiolvasott adatokat tároló puffer előkészítése. */
    dataBuffer.reserve(numOfBytes);

    /* A megadott számú bájt kiolvasása a soros portról. */
    for(unsigned int i = 0; i < numOfBytes; i++) {
      dataBuffer.push_back(readByte(msTimeout));
    }
  }
}

/* Beolvas egy sort a korábban megnyitott soros portról. */
const std::string SerialPort::readLine(
  const unsigned int msTimeout,
  const char lineTerminator)
{
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
  if(!isPortOpen)
    throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  /* Az adatok folyamatos beolvasása a soros portról, a lezárókarakterig. */
  std::string result;
  unsigned char nextByte = 0;
  do {
    nextByte = readByte(msTimeout);
    result += nextByte;
  } while(nextByte != lineTerminator);

  /* A beolvasott sor visszaadása. */
  return result.substr(0, result.size() - 1);
}

/* Kiír egy egybájtos adatot a korábban megnyitott soros portra. */
void SerialPort::writeByte(const unsigned char dataByte) {
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
  if(!isPortOpen)
    throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  /* Az átadott adatbájt kiírása a soros portra. */
  writeData(&dataByte, 1);
}

/* Kiírja az átadott puffer tartalmát a korábban megnyitott soros portra. */
void SerialPort::writeData(const std::vector<unsigned char>& dataBuffer) {
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
  if(!isPortOpen)
    throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  /* A kiírás kihagyása, ha az átadott puffer mérete nulla. */
  if(!dataBuffer.size()) return;

  /* Ideiglenes puffer lefoglalása a dataBuffer tartalmának letárolására.
  Ez lehetőséget ad a teljes puffer tartalmának átadására az unsigned char
  típusú pointert fogadó kiírató metódusnak. */
  unsigned char* temporaryBuffer = new unsigned char[dataBuffer.size()];
  if(temporaryBuffer == 0)
    throw SerialException(
      SerialException::RUNTIME_ERROR,
      std::string(__FUNCTION__) + ": Cannot allocate memory while writing "
      "data to the serial port."
    );

  /* A dataBuffer tartalmának másolása a temporaryBuffer-be, és az átmásolt
  adat kiírása a soros portra. */
  std::copy(dataBuffer.begin(), dataBuffer.end(), temporaryBuffer);
  try {
    writeData(temporaryBuffer, dataBuffer.size());
  }
  catch(...) {
    delete[] temporaryBuffer;
    throw;
  }

  /* Az ideiglenes puffer felszabadítása. */
  delete[] temporaryBuffer;
}

/* Kiírja az átadott sztring tartalmát a korábban megnyitott soros portra. */
void SerialPort::writeData(const std::string& dataString) {
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
  if(!isPortOpen)
    throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  if(dataString.size())
    writeData((const unsigned char*)dataString.c_str(), dataString.size());
}

/* Kiírja a megadott karaktertömb tartalmát a korábban megnyitott soros
portra. */
void SerialPort::writeData(
  const unsigned char* dataArray,
  const unsigned int size)
{
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
  if(!isPortOpen)
    throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  /* Az átadott bájtok kiírása a soros portra. */
  int numOfBytesWritten = -1;
  do {
    numOfBytesWritten = write(fileDescriptor, dataArray, size);
  } while((numOfBytesWritten < 0) && (EAGAIN == errno));

  /* Kivétel dobása, ha a kiírt bájtok száma változatlanul negatív érték. */
  if(numOfBytesWritten < 0)
    throw SerialException(SerialException::RUNTIME_ERROR, strerror(errno));
}

/* Beállítja a meghatározott hardvervezérlő vonalat a meghatározott logikai
szintre. */
void SerialPort::setModemControlLine(const int modemLine, const bool lineState) {
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
  if(!isPortOpen)
    throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  /* A megadott bit magas vagy alacsony logikai szintre állítása, a lineState
  értékétől függően. */
  int ioctlResult = -1;
  if(lineState) {
    int setLineMask = modemLine;
    ioctlResult = ioctl(fileDescriptor, TIOCMBIS, &setLineMask);
  }
  else {
    int resetLineMask = modemLine;
    ioctlResult = ioctl(fileDescriptor, TIOCMBIC, &resetLineMask);
  }

  /* Hiba esetén kivétel dobása. */
  if(ioctlResult == -1)
    throw SerialException(SerialException::RUNTIME_ERROR, strerror(errno));
}

/* Lekéri a meghatározott hardvervezérlő vonal állapotát. */
bool SerialPort::getModemControlLine(const int modemLine) const {
  /* Kivétel dobása, ha a soros port nincs megnyitva. */
  if(!isPortOpen)
    throw SerialException(SerialException::NOT_OPEN, "Serial port not open.");

  /* A soros port állapotának lekérdezése, és kivétel dobása, ha a lekérdezés
  közben hiba történt. */
  int serialPortState = 0;
  if(ioctl(fileDescriptor, TIOCMGET, &serialPortState) == -1)
    throw SerialException(SerialException::RUNTIME_ERROR, strerror(errno));

  /* A kiolvasott állapot maszkolása és az eredmény visszaadása. */
  return (serialPortState & modemLine);
}
