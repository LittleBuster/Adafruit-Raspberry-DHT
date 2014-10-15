all:
	gcc -pthread -fno-strict-aliasing -march=armv6 -mfloat-abi=hard -mfpu=vfp -O2 -pipe -fstack-protector --param=ssp-buffer-size=4 -DNDEBUG -march=armv6 -mfloat-abi=hard -mfpu=vfp -O2 -pipe -fstack-protector --param=ssp-buffer-size=4 -fPIC -c source/_Raspberry_Pi_Driver.c -o build/temp.linux-armv6l/source/_Raspberry_Pi_Driver.o -std=gnu99

	gcc -pthread -fno-strict-aliasing -march=armv6 -mfloat-abi=hard -mfpu=vfp -O2 -pipe -fstack-protector --param=ssp-buffer-size=4 -DNDEBUG -march=armv6 -mfloat-abi=hard -mfpu=vfp -O2 -pipe -fstack-protector --param=ssp-buffer-size=4 -fPIC -c source/common_dht_read.c -o build/temp.linux-armv6l/source/common_dht_read.o -std=gnu99

	gcc -pthread -fno-strict-aliasing -march=armv6 -mfloat-abi=hard -mfpu=vfp -O2 -pipe -fstack-protector --param=ssp-buffer-size=4 -DNDEBUG -march=armv6 -mfloat-abi=hard -mfpu=vfp -O2 -pipe -fstack-protector --param=ssp-buffer-size=4 -fPIC -c source/Raspberry_Pi/pi_dht_read.c -o build/temp.linux-armv6l/source/Raspberry_Pi/pi_dht_read.o -std=gnu99

	gcc -pthread -fno-strict-aliasing -march=armv6 -mfloat-abi=hard -mfpu=vfp -O2 -pipe -fstack-protector --param=ssp-buffer-size=4 -DNDEBUG -march=armv6 -mfloat-abi=hard -mfpu=vfp -O2 -pipe -fstack-protector --param=ssp-buffer-size=4 -fPIC -c source/Raspberry_Pi/pi_mmio.c -o build/temp.linux-armv6l/source/Raspberry_Pi/pi_mmio.o -std=gnu99

	gcc -pthread -shared -Wl,-O1,--sort-common,--as-needed,-z,relro build/temp.linux-armv6l/source/_Raspberry_Pi_Driver.o build/temp.linux-armv6l/source/common_dht_read.o build/temp.linux-armv6l/source/Raspberry_Pi/pi_dht_read.o build/temp.linux-armv6l/source/Raspberry_Pi/pi_mmio.o -L/usr/lib -lrt -o build/release/Raspberry_Pi_Driver.so

install:
	cp build/release/Raspberry_Pi_Driver.so /usr/lib/Raspberry_Pi_Driver.so

uninstall:
	rm /usr/lib/Raspberry_Pi_Driver.so

clean:
	rm -rf build/temp.linux-armv6l/source/*.*
	rm -rf build/temp.linux-armv6l/source/Raspberry_Pi/*.*
