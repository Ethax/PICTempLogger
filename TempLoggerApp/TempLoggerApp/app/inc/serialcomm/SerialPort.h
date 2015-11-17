#ifndef INC_SERIAL_SERIALPORT_H_
#define INC_SERIAL_SERIALPORT_H_

#include <app/inc/common.h>

/**
 * @class SerialException
 * @brief A soros port működése közben létrejövő hibákat jelző típus.
 */
class SerialException {
public:
  /**
   * A soros port lehetséges hibáinak felsorolása.
   */
  enum ErrorType {
    NOT_OPEN,
    OPEN_FAILED,
    ALREADY_OPEN,
    UNSUPPORTED_SETUP_PARAMETER,
    RUNTIME_ERROR,
    READ_TIMEOUT
  };

private:
  /**
   * Az létrejött hiba típusa.
   */
  ErrorType errorType;

  /**
   * A létrejött hiba leírása.
   */
  std::string errorMessage;

public:
  SerialException(ErrorType errtype, const std::string& errmsg) :
    errorType(errtype), errorMessage(errmsg) {}
  SerialException(ErrorType errtype, const char* errmsg) :
      errorType(errtype), errorMessage(errmsg) {}
  virtual ~SerialException() {}

  /**
   * @brief Visszaadja a létrejött hiba leírására mutató referenciát.
   */
  std::string getErrorMessage() { return errorMessage; }

  /**
   * @brief Visszaadja a létrejött hiba típusát.
   */
  ErrorType getErrorType() { return errorType; };
};

/**
 * @class SerialPort
 * @brief Soros porti kommunikációt megvalósító osztály.
 */
class SerialPort {//: public boost::noncopyable {
private:
  /**
   * Az eszközfájl elérési útvonala. (Általában: "/dev/ttySx", ahol az "x"
   * a soros port számát jelenti.)
   */
  std::string deviceFile;

  /**
   * Jelzőbit, amelyik jelzi, hogy a soros port nyitva van-e, vagy sem.
   */
  bool isPortOpen;

  /**
   * A soros port fájlleírója.
   */
  int fileDescriptor;

  /**
   * A soros port kezdeti beállításai, amikkel a megnyitást követően rendelkezett.
   * Ezek a beállítások a lezárást megelőzően visszaíródnak.
   */
  termios initialPortSettings;

  /**
   * A soros port fogadó puffere, a beérkező bájtok tárolására. (A megfelelő TTY
   * fogadó pufferének csúlcsordulásvédelmét szolgálja.)
   *
   * FIXME: szükség lehet egy korlátra, arra az esetre, ha valamilyen hiba folytán
   * a soros port nem fejezné be az adatok küldését.
   */
  std::queue<unsigned char> inputBuffer;

public:

  /**
   * Az alkalmazható adatátviteli sebességek felsorolása.
   */
  enum BaudRate {
    BAUD_50      = B50,
    BAUD_75      = B75,
    BAUD_110     = B110,
    BAUD_134     = B134,
    BAUD_150     = B150,
    BAUD_200     = B200,
    BAUD_300     = B300,
    BAUD_600     = B600,
    BAUD_1200    = B1200,
    BAUD_1800    = B1800,
    BAUD_2400    = B2400,
    BAUD_4800    = B4800,
    BAUD_9600    = B9600,
    BAUD_19200   = B19200,
    BAUD_38400   = B38400,
    BAUD_57600   = B57600,
    BAUD_115200  = B115200,
    BAUD_230400  = B230400,
    BAUD_DEFAULT = BAUD_9600
  };

  /**
   * Az alkalmazható karakterszélességek felsorolása.
   */
  enum CharacterSize {
    CHAR_SIZE_5  = CS5,
    CHAR_SIZE_6  = CS6,
    CHAR_SIZE_7  = CS7,
    CHAR_SIZE_8  = CS8,
    CHAR_SIZE_DEFAULT = CHAR_SIZE_8
  };

  /**
   * Az alkalmazható paritások felsorolása.
   */
  enum Parity {
    PARITY_EVEN,
    PARITY_ODD,
    PARITY_NONE,
    PARITY_DEFAULT = PARITY_NONE
  };

  /**
   * Az alkalmazható stop bitek felsorolása.
   */
  enum StopBits {
    STOP_BITS_1,
    STOP_BITS_2,
    STOP_BITS_DEFAULT = STOP_BITS_1
  };

  /**
   * Az alkalmazható hardvervezérlések felsorolása.
   */
  enum FlowControl {
    FLOW_CONTROL_HARD,
    FLOW_CONTROL_SOFT,
    FLOW_CONTROL_NONE,
    FLOW_CONTROL_DEFAULT = FLOW_CONTROL_NONE
  };

  /**
  * @brief Az osztály másoló konstruktorának tiltása.
  */
  SerialPort(const SerialPort&) = delete;

  /**
  * @brief Az osztály értékadó operátorának tiltása.
  */
  SerialPort& operator=(const SerialPort&) = delete;

public:
  SerialPort(const std::string& deviceName);
  virtual ~SerialPort();

  /**
   * @brief Megnyitja és beállítja a soros porti kommunikációt.
   *
   * @param baudRate Az alkalmazni kívánt adatátviteli sebesség.
   * @param parityType Az alkalmazni kívánt paritás típusa.
   * @param stopBits Az alkalmazni kívánt stopbitek száma.
   * @param flowControl Az alkalmazni kívánt hardvervezérlés fajtája.
   */
  void openPort(
    const BaudRate baudRate = BAUD_DEFAULT,
    const CharacterSize charSize = CHAR_SIZE_DEFAULT,
    const Parity parityType = PARITY_DEFAULT,
    const StopBits stopBits = STOP_BITS_DEFAULT,
    const FlowControl flowControl = FLOW_CONTROL_DEFAULT
  );

  /**
   * @brief Leellenőrzi, hogy a soros kommunikáció nyitott-e vagy sem.
   *
   * @return Ha a soros port nyitott, akkor IGAZ, ellenkező esetben HAMIS.
   */
  bool isOpen() const;

  /**
   * @brief Lezárja a korábban menyitott soros porti kommunikációt. (A lezárást
   * követően a megnyitáskor lementett beállítások visszaállnak.)
   */
  void closePort();

  /**
   * @brief A beállított értéknek megfelelően módosítja a korábban megnyitott
   * soros porti kommunikáció adatátviteli sebességét.
   *
   * @param baudRate A beállítani kívánt adatátviteli sebesség.
   */
  void setBaudRate(const BaudRate baudRate);

  /**
   * @brief Visszaadja a korábban megnyitott soros porti kommunikáció aktuális
   * adatátviteli sebességet.
   *
   * @return Az érvényben levő adatátviteli sebesség.
   */
  BaudRate getBaudRate() const;

  /**
   * @brief A beállított értéknek megfelelően módosítja a korábban megnyitott
   * soros porti kommunikáció karaktereinek szélességét.
   *
   * @param charSize A beállítani kívánt karakterszélesség.
   */
  void setCharSize(const CharacterSize charSize);

  /**
   * @brief Visszaadja a korábban megnyitott soros porti kommunikáció által használt
   * karakterszélességet.
   */
  CharacterSize getCharSize() const;

  /**
   * @brief A beállított értéknek megfelelően módosítja a korábban megnyitott
   * soros porti kommunikáció paritásának típusát.
   *
   * @param parityType A beállítani kívánt paritás típusa.
   */
  void setParity(const Parity parityType);

  /**
   * @brief Visszaadja a korábban megnyitott soros porti kommunikáció aktuálisan
   * alkalmazott paritásának típusát.
   *
   * @return Az érvényben levő paritás típusa.
   */
  Parity getParity() const;

  /**
   * @brief A beállított értéknek megfelelően módosítja a korábban megnyitott
   * soros porti kommunikáció stop bitjeinek számát.
   *
   * @param numOfStopBits Az alkalmazni kívánt stop bitek száma.
   */
  void setNumOfStopBits(const StopBits numOfStopBits);

  /**
   * @brief Visszaadja a korábban megnyitott soros porti kommunikáció aktuális
   * stop bitjeinek számát.
   *
   * @return Az érvényben levő stop bitek száma.
   */
  StopBits getNumOfStopBits() const;

  /**
   * @brief A beállított értéknek megfelelően módosítja a korábban megnyitott
   * soros porti kommunikáció hardvervezérlésének módját.
   *
   * @param flowControl Az alkalmazni kívánt hardvervezérlés fajtája.
   */
  void setFlowControl(const FlowControl flowControl);

  /**
   * @brief Visszaadja a korábban megnyitott soros porti kommunikáció aktuálisan
   * alkalmazott hardvervezérlésének módját.
   *
   * @return Az érvényben levő hardvervezérlés fajtája.
   */
  FlowControl getFlowControl() const;

  /**
   * @brief Leellenőrzi, hogy van-e új adat a fogadó pufferben.
   *
   * @return IGAZ, ha új adat érhető el a soros porton, egyébként HAMIS.
   */
  bool isDataAvailable() const;

  /**
   * @brief Beolvas egy egybájtnyi adatot a soros portról. Amennyiben a soros
   * porton nincs elérhető adat, a meadott időkorláton belül újra és újra
   * megkísérli az olvasási műveletet. Ha az időkorlát értéke nulla, akkor
   * mindaddid lefogja az aktuális szálat, amíg új adat nem érkezik.
   *
   * @param msTimeout Az olvasási kísérletek időkorlátja.
   * @return A kiolvasott egybájtnyi adat.
   */
  unsigned char readByte(const unsigned int msTimeout = 0);

  /**
   * @brief Beolvas egy meghatározott hosszúságú adatot a soros portról. Ha az
   * időkorlát értéke nulla, akkor mindaddig lefogja az aktuális szálat, amíg
   * a meghatározott számú adatbájt fogadása meg nem történik. Amennyiben a
   * fogadni kívánt adat hossza nulla, akkor addig folytatja az olvasást, amíg
   * adatok érkeznek a soros portról.
   *
   * @param dataBuffer Az adatokat fogadó puffer.
   * @param numOfBytes A fogadni kívánt adat hossza.
   * @param Az olvasási kísérletek időkorlátja.
   */
  void readData(
    std::vector<unsigned char>& dataBuffer,
    const unsigned int numOfBytes = 0,
    const unsigned int msTimeout  = 0
  );

  /**
   * @brief Beolvas egy sort a korábban megnyitott soros portról.
   *
   * @param msTimeout Az olvasási kísérletek időkorlátja.
   * @param lineTerminator A sor végét jelölő karakter.
   */
  const std::string readLine(
    const unsigned int msTimeout = 0,
    const char lineTerminator = '\n'
  );

  /**
   * @brief Kiír egy egybájtos adatot a korábban megnyitott soros portra.
   *
   * @param dataByte A kiírni kívánt adatbájt.
   */
  void writeByte(const unsigned char dataByte);

  /**
   * @brief Kiírja az átadott puffer tartalmát a korábban megnyitott soros
   * portra.
   *
   * @param dataBuffer A kiíratásra szánt adatokat tartalmazó puffer.
   */
  void writeData(const std::vector<unsigned char>& dataBuffer);

  /**
   * @brief Kiírja az átadott sztring tartalmát a korábban megnyitott soros
   * portra.
   *
   * @param dataString A kiíratásra szánt sztring.
   */
  void writeData(const std::string& dataString);

  /**
   * @brief Kiírja a megadott karaktertömb tartalmát a korábban megnyitott soros
   * portra.
   *
   * @param dataArray A kiíratásra szánt karaktertömb.
   * @param size A tömb mérete bájtokban.
   */
  void writeData(const unsigned char* dataArray, const unsigned int size);

  /**
   * @brief Beállítja a DTR vonalat a megadott logikai szinre.
   *
   * @param dtrState A beállítani kívánt logikai szint.
   */
  void setDTR(const bool dtrState) { setModemControlLine(TIOCM_DTR, dtrState); }

  /**
   * @brief Lekérdezi a DTR vonal aktuális állapotát.
   *
   * @return A DTR vonal aktuális logikai szintje.
   */
  bool getDTR() const { return getModemControlLine(TIOCM_DTR); }

  /**
   * @brief Beállítja az RTS vonalat a megadott logikai szinre.
   *
   * @param rtsState A beállítani kívánt logikai szint.
   */
  void setRTS(const bool rtsState) { setModemControlLine(TIOCM_RTS, rtsState); }

  /**
   * @brief Lekérdezi az RTS vonal aktuális állapotát.
   *
   * @return Az RTS vonal aktuális logikai szintje.
   */
  bool getRTS() const { return getModemControlLine(TIOCM_RTS); }

  /**
   * @brief Lekérdezi a CTS vonal aktuális állapotát.
   *
   * @return A CTS vonal aktuális logikai szintje.
   */
  bool getCTS() const { return getModemControlLine(TIOCM_CTS); }

  /**
   * @brief Lekérdezi a DSR vonal aktuális állapotát.
   *
   * @return A DSR vonal aktuális logikai szintje.
   */
  bool getDSR() const { return getModemControlLine(TIOCM_DSR); }

private:
  /**
   * @brief Beállítja a meghatározott hardvervezérlő vonalat a meghatározott
   * logikai szintre.
   *
   * @param modemLine A következő konstansok egyike: TIOCM_DTR, TIOCM_RTS,
   * TIOCM_CTS vagy TIOCM_DSR.
   * @param lineState A beállítani kívánt állapot.
   */
  void setModemControlLine(const int modemLine, const bool lineState);

  /**
   * @brief Lekéri a meghatározott hardvervezérlő vonal állapotát.
   *
   * @param modemLine A következő konstansok egyike: TIOCM_DTR, TIOCM_RTS,
   * TIOCM_CTS vagy TIOCM_DSR.
   * @return IGAZ. ha a kiválasztott vonal magas logikai szinten van,
   * egyébként HAMIS.
   */
  bool getModemControlLine(const int modemLine) const;
};

#endif /* INC_SERIAL_SERIALPORT_H_ */
