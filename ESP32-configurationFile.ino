#include <esp_system.h>
#include <SPIFFS.h>

// Example of a custom configuration file using SPIFFS
char *filename = "/config.cnf";

bool readFile() {
  if (SPIFFS.exists(filename))
  {
    File configFile = SPIFFS.open(filename, FILE_READ);
    if (!configFile)
    {
      Serial.println("Failed to open file");
      return false;
    }
    Serial.println("File read");
    // Read each line and parse key-value pairs
    while (configFile.available())
    {
      String line = configFile.readStringUntil('\n');
      int separatorIndex = line.indexOf(':');
      if (separatorIndex != -1)
      {
        String key = line.substring(0, separatorIndex);
        String value = line.substring(separatorIndex + 1);
        value.trim(); // required as values will have a whitespace (newline) character at the end
        Serial.print(key);
        Serial.print(" -> ");
        Serial.println(value);
      }
    }
    configFile.close();
    return true;
  }
  return false;
}

bool writeFile() {
  File configFile = SPIFFS.open(filename, FILE_WRITE);
  if (!configFile)
  {
    Serial.println("Failed to open file for writing");
    return false;
  }
  Serial.println("File write");
  // Example config, write each key-value pair to the file
  configFile.print("key1");
  configFile.print(":");
  configFile.println("value1");
  configFile.print("key2");
  configFile.print(":");
  configFile.println("value2");
  configFile.close();
  return true;
}

void setup()
{
  // Make sure we have serial comm's
  Serial.begin(115200);
  // while the serial stream is not open, do nothing:
  while (!Serial)
  {
    delay(2000); // Wait for 2 seconds
  };
  delay(4000); // Wait for extra 4 seconds
  Serial.println("Serial ready");

  SPIFFS.begin(true); // Format on fail to mount
  // List all files in filesystem
  Serial.println("Listing files in FS..");  
  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  while (file)
  {
    Serial.print("  ");
    Serial.println(file.name());
    file = root.openNextFile();
  }
  // Try to open configuration file
  if (!readFile()) {
    // Create file if it does not exist
    writeFile();
  }
  Serial.println("Power cycle unit to read the configuration.");
  Serial.println("Press boot to delete the configuration file.");
}

void loop()
{
  // Check if the BOOT button is pressed (0 is the pin connected on many ESP32 boards)
  if (!digitalRead(0))
  { 
    // Delete configuration
    Serial.println("Deleting configuration file...");
    if (SPIFFS.exists(filename))
    {
      SPIFFS.remove(filename);
    }
    // Restart the ESP32 board
    Serial.println("Restarting...");
    esp_restart();
  }
}

