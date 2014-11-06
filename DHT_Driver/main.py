from DHT import *

dht = AdafruitDHT()
dht.load_lib()
print(dht.get_temp_and_hum(DEV_DHT_22, 4))
