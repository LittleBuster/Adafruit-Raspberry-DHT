// Copyright (c) 2014 Adafruit Industries
// Author: Tony DiCola
// Author: Denisov Sergey

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

#include "Raspberry_Pi/pi_dht_read.h"

char* get_temp_and_hum( int device_id, int pin ) {
	char hum[100];
	char res[200];

	float humidity = 0, temperature = 0;
	int result = pi_dht_read(device_id, pin, &temperature, &humidity);
	
	sprintf(res, "%f", temperature);
	sprintf(hum, "%f", humidity); 
	strcat(res, "%");
	strcat(res, hum);
	
	return res;
}

extern char* get_temp_and_hum( int device_id, int pin );
