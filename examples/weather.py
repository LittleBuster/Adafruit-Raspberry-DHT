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

import datetime
import pymysql
from DHT import *
from threading import Thread
import time


class Worker(Thread):
	def set_dht(self, _dht):
		self.dht = _dht

	def run(self):
		while True:
			res = self.dht.get_temp_and_hum(DEV_DHT_22, 3)
			date = str(datetime.datetime.now()).split(".")[0]
			conn = pymysql.connect(host="127.0.0.1", port=3306, user="myuser", passwd="myuser", db="my", charset='utf8')
			cur = conn.cursor()
			cur.execute("INSERT INTO weather (temperature, humidity, date) VALUES ('"+ str(res["temp"])+"','"+ str(res["hum"]) +"', '"+ date +"')")
			conn.commit()

			print("[" + date + "] Insterted: " + str(res))
			time.sleep(5)


def main():
	dht = AdafruitDHT()
	dht.load_lib()
	
	print("Startted!")

	worker = Worker()
	worker.set_dht( dht )
	worker.start()

if __name__ == "__main__":
	main()
