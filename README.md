# Configuration file example using SPIFFS

Simple example of writing, reading and deleting a configuration file from a filesystem in ESP32.


## Initial configuration

When first launching, the SPIFFS filesystem will be created.

If a configuration file is not detected, it is created. Otherwise content will be read and printed to serial.

Pressing the boot button will trigger a file deletion and reboot of the unit.


## References

* https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/storage/spiffs.html
* https://www.programmingelectronics.com/spiffs-esp32/