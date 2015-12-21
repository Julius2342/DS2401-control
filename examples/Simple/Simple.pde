#include <OneWire.h>
#include <DS2401.h>

// Data wire is plugged into port 30 on the Arduino
#define ONE_WIRE_BUS 30

// List of all known DS2401 chips
DS2401::OneWireDeviceAddress known_devices[DS2401_MAX_DEVICES] = {
   {0x01, 0x6B, 0x25, 0xC9, 0x17, 0x00, 0x00, 0xB6},
   {0x01, 0xED, 0x98, 0xCB, 0x17, 0x00, 0x00, 0x4A},
   {0x01, 0xAC, 0xD1, 0xC8, 0x17, 0x00, 0x00, 0x9A},
   {0x01, 0x45, 0x51, 0xCB, 0x17, 0x00, 0x00, 0x66},
   {0x01, 0xF4, 0x8B, 0xC9, 0x17, 0x00, 0x00, 0xB2},
   0
  };

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

DS2401 ds2401(oneWire, known_devices);

void setup(void)
{
	// start serial port
	Serial.begin(9600);
}

void loop(void)
{
	ds2401.scan();

	for (int i= 0; i<5;i++)
	{
		bool status = !ds2401.get_status(i);

		Serial.print("Device ");
		Serial.print(i);
		Serial.print(" has status ");
		Serial.println(status ? "OFF" : "ON" );
	} 

	delay(1000);
}


