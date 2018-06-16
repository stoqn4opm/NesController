/*
   EEPROM Read

   Reads the value of each byte of the EEPROM and prints it
   to the computer.
   This example code is in the public domain.
*/

#include <EEPROM.h>

// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;

void setup()
{
  // initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}

void loop() {
  read();
  pinMode(9, INPUT);

  if (digitalRead(9) == HIGH) {
    Serial.println("Erasing...");
    for ( int i = 0 ; i < EEPROM.length() ; i++ )
      EEPROM.write(i, 0);

    Serial.println("Erased");
  }
}

void read()
{
  // read a byte from the current address of the EEPROM
  value = EEPROM.read(address);

  Serial.print(address);
  Serial.print("\t");
  Serial.print(EEPROM.read(address));
  Serial.println();

  address = address + 1;
  if (address == EEPROM.length())
    address = 0;

  delay(50);
}
