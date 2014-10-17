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


def main():
	dht = AdafruitDHT()
	dht.load_lib()

	print("-----------------------------------------------")
	print("Write to database? Press Enter;\nPress q for exit.")
	print('Type "s" to show')
	print("-----------------------------------------------")
	while True:
		x = input("Get data?")
		if x == "q" or x == "quit" or x == "exit":
			break

		if x == "s" or x == "show":
			conn = pymysql.connect(host="127.0.0.1", port=3306, user="root", passwd="123456", db="my", charset='utf8')
			cur = conn.cursor()
			cur.execute("SELECT * FROM my")
			for row in cur:
				print("id:", row[0], "temperature:", row[1], "humidity:", row[2], "time:", row[3], "date:", row[4])
		else: 

			res = dht.get_temp_and_hum(DEV_DHT_22, 3)
	
			date = str(datetime.datetime.now()).split(" ")[0]
			time = str(datetime.datetime.now()).split(" ")[1].split(".")[0]

			conn = pymysql.connect(host="127.0.0.1", port=3306, user="root", passwd="123456", db="my", charset='utf8')
			cur = conn.cursor()
			cur.execute("".join(("INSERT INTO my(temp,hum,time,date) VALUES ('", str(res["temp"]), "', '", str(res["hum"]), "', '", time, "', '", date, "')")))
			conn.commit()

			print("Temperature is:", res["temp"], "Humidity is:", res["hum"], "added to database.")

if __name__ == "__main__":
	main()
