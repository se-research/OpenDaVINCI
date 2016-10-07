all: clean unpack patch compile install

clean:
	rm -fr peak-linux-driver-7.15.2

unpack:
	tar xvzf peak-linux-driver-7.15.2.tar.gz

patch:
	cd peak-linux-driver-7.15.2 && patch -p1 < ../peak-linux-driver-7.15.2-pcan.starttime.patch && cd ..

compile:
	cd peak-linux-driver-7.15.2 && make NET=NO_NETDEV_SUPPORT && cd ..

install:
	cd peak-linux-driver-7.15.2 && sudo make install && cd ..

