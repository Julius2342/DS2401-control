// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#include "DS2401.h"

#if ARDUINO >= 100
	#include "Arduino.h"	 
#else
extern "C" {
	#include "WConstants.h"
}
#endif

DS2401::DS2401(OneWire & one_wire, OneWireDeviceAddress * known_devices ) :
		one_wire_(one_wire),
		known_devices_(known_devices)
{
	reset_status();
}

void
DS2401::scan()
{
	OneWireDeviceAddress addr;
	one_wire_.reset();
	reset_status();

	while ( one_wire_.search(addr) )
	{
		if ( OneWire::crc8( addr, 7) != addr[7])
		{
			Serial.print("CRC is not valid!\n");
			return;
		}

		// the first ROM byte indicates which chip
		switch (addr[0])
		{
			case 0x01:
				//Serial.print("DS2401 ");
				//print_address_to_serial(addr);
				test_address(addr);
				break;
			default:
				Serial.print("DS2401:: Unknown device, family: ");
				Serial.println(addr[0], HEX);
		}
	}
}

void
DS2401::test_address(OneWireDeviceAddress & addr)
{		
	int address_index = -1;
	
	for (int i=0;i<DS2401_MAX_DEVICES;i++)
	{
		if (known_devices_[i][0]==0)
			break;
		
		if (compare_address(addr,known_devices_[i]))
		{
			address_index = i;
			break;
		}
	}

	if (address_index==-1)
	{
		Serial.print("unmatched: ");
		print_address_to_serial(addr);
		Serial.println("");
	}
	else
	{
		status_array_[address_index] = true;
	}
}

bool
DS2401::compare_address(OneWireDeviceAddress & a, OneWireDeviceAddress & b)
{
	for (int i = 0;i<8;i++)
		if(a[i]!=b[i])
			return false;
	return true;
}

void
DS2401::reset_status()
{
	for(int i=0;i<DS2401_MAX_DEVICES;i++)
		status_array_[i]=false;
}

bool
DS2401::get_status(int i)
{
	return status_array_[i];
}

void
DS2401::print_address_to_serial(OneWireDeviceAddress & addr)
{
	for (int i = 0;i<8;i++)
	{
		Serial.print(addr[i], HEX);
		Serial.print(" ");
	}
}
