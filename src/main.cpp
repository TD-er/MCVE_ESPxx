#include <Arduino.h>


// Needed due to preprocessor issues.
#ifdef PLUGIN_SET_GENERIC_ESP32
  #ifndef ESP32
    #define ESP32
  #endif
#endif



// ESP32C3/S3 embedded USB using JTAG interface
# include <HWCDC.h>
# include <deque>

# if ARDUINO_USB_CDC_ON_BOOT // Serial used for USB CDC
  HWCDC *_hwcdc_serial = &Serial;
# else // if ARDUINO_USB_CDC_ON_BOOT
  HWCDC *_hwcdc_serial = &USBSerial;
# endif // if ARDUINO_USB_CDC_ON_BOOT

// ESP32-C3 using HW Serial CDC on Boot enabled


std::deque<char>_buffer;


size_t streamWrite_ESPEasy(Stream& stream, size_t nrBytesToWrite)
{
  size_t bytesWritten     = 0;
  const size_t bufferSize = _buffer.size();

  if (bufferSize == 0) {
    return bytesWritten;
  }

  if (nrBytesToWrite > 0) {
    // FIXME TD-er: Work-around for bug in HWCDC when writing exactly the amount of free bytes in the buffer.
//    --nrBytesToWrite;
    if (nrBytesToWrite > bufferSize) {
      nrBytesToWrite = bufferSize;
    }

    while (nrBytesToWrite > 0 && !_buffer.empty()) {
      uint8_t tmpBuffer[64]{};

      size_t tmpBufferUsed = 0;

      auto it = _buffer.begin();

      bool done = false;

      for (; tmpBufferUsed < sizeof(tmpBuffer) && 
             !done &&
             it != _buffer.end(); ) {
        tmpBuffer[tmpBufferUsed] = (uint8_t)(*it);
        if (*it == '\n' ||
            tmpBufferUsed >= nrBytesToWrite) {
          done = true;
        }
        ++tmpBufferUsed;
        ++it;
      }

      const size_t written = (tmpBufferUsed == 0) ? 0 : stream.write(tmpBuffer, tmpBufferUsed);

      if (written < tmpBufferUsed) {
        done = true;
      }
      for (size_t i = 0; i < written; ++i) {
        _buffer.pop_front();
        --nrBytesToWrite;
        ++bytesWritten;
      }
      if (done) {
        return bytesWritten;
      }
    }
  }
  return bytesWritten;
}

size_t ESPEasy_flush() {
  size_t sent{};

  int snip = _hwcdc_serial->availableForWrite();

  if  (snip > 0) {
//    --snip;
    sent += streamWrite_ESPEasy(*_hwcdc_serial, snip);
  }
  return sent;
}


bool testCase1(const String &data) {
  size_t receivedLen = data.length();
  size_t sendLen = 0;

  while (sendLen < receivedLen) {
    if (!_hwcdc_serial->write(data[sendLen++])) break;   // <<< if it fails sending a single byte, it will fail the whole test case
  }
  _hwcdc_serial->println("===");
  if (sendLen != receivedLen) {
    Serial0.printf("\r\n ===> T1::Error -- didn't send all data [%d of %d]\r\n", sendLen, receivedLen);
    return false;
  } else {
    return true;
  }
}

bool testCase2(const String &data) {
  size_t receivedLen = data.length();

  size_t sent = _hwcdc_serial->write(data.c_str(), receivedLen);
  _hwcdc_serial->println("===");
  if (sent != receivedLen) {
    Serial0.printf("\r\n ===> T2::Error -- didn't send all data [%d of %d]\r\n\r\n", sent, receivedLen);
    return false;
  }  else {
    return true;
  }
}

bool testCase3(const String& data) {
  size_t receivedLen = data.length();

  for (size_t i = 0; i < receivedLen; ++i) {
    _buffer.push_back(data[i]);
  }
  for (size_t i = 0; i < 3; ++i) {
    _buffer.push_back('=');
  }
   _buffer.push_back('\n');

//  size_t sent = ESPEasy_flush();
  return true;
}

void setup() {
  Serial0.begin(115200);

//  _hwcdc_serial->setTxBufferSize(64);
  _hwcdc_serial->setTxTimeoutMs(1);

  _hwcdc_serial->begin();
  Serial0.println("\r\nStarting... open Serial Monitor with CDC port.");
  while(!Serial) delay(100);
  _hwcdc_serial->println("\r\nCDC Started.");

  bool result = true;
  String testString = "0";
  for (int x = 0; x < 100; x++) {  // runs the test cases 100 times
    testString = "0";
    for (int i = 0; i < 302; i++) {  // sends from 1 to 301 bytes per test
//      result &= testCase1(testString);
//      result &= testCase2(testString);
      result &= testCase3(testString);
//      delay(1);
      ESPEasy_flush();
      if (!result) {
        Serial0.printf("Failed with %d bytes\r\n", i);
        break;
      }
      char c = testString.charAt(testString.length() - 1);
      c = c == '9' ? '0' : c + 1;
//      if(i > 22) c = '7'; inserts an error to test the python script
      testString += c;
    }
    while (!_buffer.empty()) {
      ESPEasy_flush();
    }

    if (!result) break;
    Serial0.print(x+1);
    Serial0.print(" ");
    if (((x+1) % 10) == 0) Serial0.println();
  }
  if (result) {
    _hwcdc_serial->println("OK");
    Serial0.println("\r\nSetup is done : SUCCESS!\r\n");
  }  else {
    _hwcdc_serial->println("ERROR!!!");
    Serial0.println("\r\n\t\t====> Setup is done : FAILED!\r\n");
  }
}

void loop() {}