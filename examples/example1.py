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

from DHT import *


def main():
	dht = AdafruitDHT()
	dht.load_lib()

	print("-----------------------------------------------")
	print("Press Enter for print temperature and humidity;\nPress q for exit.")
	print("-----------------------------------------------")
	while True:
		x = input("Get data?")
		if x == "q" or x == "quit" or x == "exit":
			break

		res = dht.get_temp_and_hum(DEV_DHT_22, 3)
		print("Temperature is:", res["temp"], "Humidity is:", res["hum"])

if __name__ == "__main__":
	main()
