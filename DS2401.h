#ifndef _DS2401_H_
#define _DS2401_H_ 

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#define DS2401LIBVERSION "0.0.1"

#include <OneWire.h>

#define DS2401_MAX_DEVICES 128

class DS2401
{
public:
	typedef uint8_t OneWireDeviceAddress[8];

	DS2401(OneWire & one_wire, OneWireDeviceAddress * known_devices );

	void scan();

	void test_address(OneWireDeviceAddress & addr);

	bool compare_address(OneWireDeviceAddress & a, OneWireDeviceAddress & b);

	void reset_status();

	bool get_status(int i);
	
	void print_address_to_serial(OneWireDeviceAddress & addr);

private:
	OneWire & one_wire_;
	OneWireDeviceAddress * known_devices_;
	bool status_array_[DS2401_MAX_DEVICES];
};



#endif
