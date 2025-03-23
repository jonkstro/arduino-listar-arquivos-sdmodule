/*

Pinos para o NodeMCU-V3:
 ** CS -> 4     // D2
 ** MOSI -> 13  // D7
 ** MISO -> 12  // D6
 ** SCK -> 14   // D5

Pinos para arduino:
 ** CS - pin 4
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13

Pinos para o ESP32:
 ** CS 5
 ** MOSI 23
 ** MISO 19
 ** SCK 18

*/


#include "SD.h"

// Defina os pinos do SD card no NodeMCU-V3
#define SD_CS 4  // D2

File root;

void setup() {
  Serial.begin(115200);
  Serial.println("Cartão sendo inicializado...");

  if (!SD.begin(SD_CS)) {
    Serial.println("Falha, verifique se o cartão está presente.");
    return;
  }

  Serial.println("Cartão inicializado.");

  root = SD.open("/");

  printDirectory(root, 0);

  Serial.println("done!");
}

void loop() {
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry = dir.openNextFile();
    if (!entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) { Serial.print('\t'); }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.print(entry.size(), DEC);
      time_t cr = entry.getCreationTime();
      time_t lw = entry.getLastWrite();
      struct tm* tmstruct = localtime(&cr);
      Serial.printf("\tCREATION: %d-%02d-%02d %02d:%02d:%02d", (tmstruct->tm_year) + 1900, (tmstruct->tm_mon) + 1, tmstruct->tm_mday, tmstruct->tm_hour, tmstruct->tm_min, tmstruct->tm_sec);
      tmstruct = localtime(&lw);
      Serial.printf("\tLAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n", (tmstruct->tm_year) + 1900, (tmstruct->tm_mon) + 1, tmstruct->tm_mday, tmstruct->tm_hour, tmstruct->tm_min, tmstruct->tm_sec);
    }
    entry.close();
  }
}
