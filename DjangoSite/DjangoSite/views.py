from django.shortcuts import render
from django.http import HttpResponse
import pymysql
import datetime
import os
from django.contrib.auth import authenticate, login
from django.shortcuts import redirect
from django.template import Context, loader
from DjangoSite.DHT import *
from django.contrib.auth.models import User


def index(request):
	if request.method == 'GET':
		if request.META["PATH_INFO"] == "/send/":
			dht = AdafruitDHT()
			dht.load_lib()
			res = dht.get_temp_and_hum(DEV_DHT_22, 3)

			date = str(datetime.datetime.now()).split(" ")[0]
			time = str(datetime.datetime.now()).split(" ")[1].split(".")[0]

			conn = pymysql.connect(host="127.0.0.1", port=3306, user="root", passwd="123456", db="weather", charset='utf8')
			
			if conn:
				cur = conn.cursor()
				cur.execute("".join(("INSERT INTO weather(temp,hum,time,date) VALUES ('", str(res["temp"]), "', '", str(res["hum"]), "', '", time, "', '", date, "')")))
				conn.commit()

	t = loader.get_template('index.html')

	conn = pymysql.connect(host="127.0.0.1", port=3306, user="root", passwd="123456", db="weather", charset='utf8')
	if conn:
		cur = conn.cursor()
		cur.execute("SELECT * FROM my")

	weather = []
	weather2 = []
	temp = {"date": "", "temp":"", "hum":""}

	for row in cur:
		w = {}
		w["time"] =  "".join((row[3].split(":")[0], ":", row[3].split(":")[1]))
		w["temp"] = float(row[1])
		w["hum"] = float(row[2])
		weather.append( w )

		if not row[4] == temp["date"]:
			temp["date"] = row[4]
			temp["temp"] = float(row[1])
			temp["hum"] = float(row[2])

			if not temp["date"] == "":
				weather2.append(temp)
		else:
			if float(row[1]) > temp["temp"]:
				temp["temp"] = float(row[1])
				temp["hum"] = float(row[2])

	conn.close()

	dht = AdafruitDHT()
	dht.load_lib()
	now = dht.get_temp_and_hum(DEV_DHT_22, 3)

	c = Context({
		'now_weather': now,
		'weather': weather,
		'weather2': weather2
	})
	return HttpResponse(t.render(c))