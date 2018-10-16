// ----------------------------------------------------------------------------
// NewhavenDisplay.h
//
// Provides an interface to the Newhaven serial liquid crystal display
// modules.
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef NEWHAVEN_DISPLAY_H
#define NEWHAVEN_DISPLAY_H
#include <Arduino.h>
#include <Stream.h>
#include <HardwareSerial.h>
#include <Streaming.h>
#include <BetterMap.h>


class NewhavenDisplay {
public:
  NewhavenDisplay(HardwareSerial &serial);
  NewhavenDisplay(HardwareSerial &serial,
    size_t row_count,
    size_t col_count);
  void setSerial(HardwareSerial &serial);
  void setup();
  template<typename T>
  void print(const T value)
  {
    serial_ptr_->print(value);
  }
  template<typename T>
  void printPadLeft(const T value,
    size_t length_total)
  {
    String string = String(value);
    stringPadLeft(string,length_total);
    serial_ptr_->print(string);
  }
  template<typename T>
  void printPadRight(const T value,
    size_t length_total)
  {
    String string = String(value);
    stringPadRight(string,length_total);
    serial_ptr_->print(string);
  }
  template<typename T>
  void setPaddingChar(const T value)
  {
    String string = String(value);
    if (string.length() > 0)
    {
      padding_char_ = string.charAt(0);
    }
    else
    {
      padding_char_ = ' ';
    }
  }
  void resetDefaultPaddingChar();
  char getPaddingChar();
  void displayOn();
  void displayOff();
  void setCursor(size_t row,
    size_t col);
  void setCursor(size_t pos);
  void homeCursor();
  void underlineCursorOn();
  void underlineCursorOff();
  void moveCursorLeft();
  void moveCursorRight();
  void blinkingCursorOn();
  void blinkingCursorOff();
  void backspace();
  void clearScreen();
  void setContrast(size_t percent);
  void setContrastDefault();
  void setBrightness(size_t percent);
  void setBrightnessDefault();
  void moveDisplayLeft();
  void moveDisplayRight();
  void displayFirmwareVersion();
  void displayRs232Rate();
  int getRowCount();
  int getColCount();

private:
  HardwareSerial *serial_ptr_;
  const size_t row_count_;
  const size_t col_count_;
  char padding_char_;
  const static int ROW_COUNT_DEFAULT = 4;
  const static int COL_COUNT_DEFAULT = 20;
  const static int BAUD = 9600;
  const static int PERCENT_MIN = 0;
  const static int PERCENT_MAX = 100;
  const static int BRIGHTNESS_MIN = 1;
  const static int BRIGHTNESS_MAX = 8;
  const static int BRIGHTNESS_PERCENT_DEFAULT = 15;
  const static int CONTRAST_MIN = 1;
  const static int CONTRAST_MAX = 50;
  const static int CONTRAST_PERCENT_DEFAULT = 80;
  void sendCmd(uint8_t cmd);
  void stringPadLeft(String &,
    size_t length_total);
  void stringPadRight(String &,
    size_t length_total);
};


#endif
