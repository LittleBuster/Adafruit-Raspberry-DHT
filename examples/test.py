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
import unittest


class MainTest(unittest.TestCase):
	def setUp(self):
		self.dht = AdafruitDHT()

	def test_load(self):
		f = False
		try:
			self.dht.load_lib()
			f = True
		except:
			f = False

		self.assertTrue(f)

	def test_values(self):
		self.dht.load_lib()
		res = self.dht.get_temp_and_hum(DEV_DHT_22, 3)
		
		self.assertNotEqual(res["temp"], "0.000000")
		self.assertNotEqual(res["hum"], "0.000000")
		
if __name__ == "__main__":
	unittest.main()
