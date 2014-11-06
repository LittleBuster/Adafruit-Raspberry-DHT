#!/usr/bin/python
# -*- coding: utf-8 -*-

# Copyright (c) 2014 Denisov Foundation
# Author: Denisov Sergey
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

import time
import ctypes


DEV_DHT_22 = 22


class AdafruitDHT():
	"""
	Python binding class for Adafruit C-library.
	It may use for Python3 and Python2 languages.
	"""
	def load_lib(self):
		"""
		Load C-language library from /usr/lib
		"""
		self.lib = ctypes.cdll.LoadLibrary("/usr/lib/libdht_driver.so")

	def get_temp_and_hum(self, device_id, pin):
		"""
		Get and check temperature and humidity values.
		Function never return 0.
		"""
		while True:
			out = {}
			res = ctypes.c_char_p( self.lib.pi_dht_read(device_id, pin))
			res_s = res.value.decode("utf-8")
			del res
						
			out["temp"] = res_s.split("%")[0]
			out["hum"] = res_s.split("%")[1]
			
			if not out["temp"] == "0.000000" and not out["hum"] == "0.000000":
				out["temp"] = round( float(out["temp"]), 1 )
				out["hum"] = round( float(out["hum"]), 1 )
				return out
			time.sleep(0.1)

