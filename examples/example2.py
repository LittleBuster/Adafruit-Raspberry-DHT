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
import datetime
from DHT import *
from threading import Thread


class Worker(Thread):
	def set_dht(self, _dht):
		self.dht = _dht

	def run(self):
		while True:
			res = self.dht.get_temp_and_hum(DEV_DHT_22, 3)
			date = datetime.datetime.now()
			print("".join(("[", str(date).split(".")[0], "]")), "Temperature is:", res["temp"], "Humidity is:", res["hum"])
			time.sleep(1)

def main():
	dht = AdafruitDHT()
	dht.load_lib()
	
	worker = Worker()
	worker.set_dht( dht )
	worker.start()

if __name__ == "__main__":
	main()
