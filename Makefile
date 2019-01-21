

all: ino inomake test

test: gcctest/gcctest
	cp gcctest/gcctest test

gcctest/gcctest: gcctest/drive.o gcctest/fakewheel.o gcctest/gcctest.o gcctest/cpTime.o
	g++ gcctest/drive.o gcctest/fakewheel.o gcctest/gcctest.o gcctest/cpTime.o -lm -o gcctest/gcctest

gcctest/gcctest.o: gcctest/gcctest.cpp
	g++ -c gcctest/gcctest.cpp -o gcctest/gcctest.o

gcctest/fakewheel.o: gcctest/fakewheel.cpp
	g++ -c gcctest/fakewheel.cpp -o gcctest/fakewheel.o

gcctest/drive.o: gcctest/drive.cpp gcctest/drive.h gcctest/wiring.h gcctest/cpTime.h
	g++ -c gcctest/drive.cpp -o gcctest/drive.o

gcctest/cpTime.o: gcctest/cpTime.cpp gcctest/cpTime.h
	g++ -c gcctest/cpTime.cpp -o gcctest/cpTime.o

gcctest/drive.h: FOLD/drive.h
	cat FOLD/drive.h | sed -r 's;#include "wheel.h";#include "fakewheel.h"\n#include <math.h>;' > gcctest/drive.h

gcctest/wiring.h: FOLD/wiring.h
	cp FOLD/wiring.h gcctest/wiring.h

gcctest/drive.cpp: FOLD/drive.ino
	cp FOLD/drive.ino gcctest/drive.cpp

ino:
	mkdir -p ino

ino/Makefile: INO-Makefile | ino
	cp INO-Makefile ino/Makefile

ino/Arduino-Makefile: | ino
	cd ino && git clone git@github.com:sudar/Arduino-Makefile.git

ino/FOLD.cpp: FOLD/FOLD.ino | ino
	cp FOLD/FOLD.ino ino/FOLD.cpp

ino/FOLD.h: FOLD/FOLD.h | ino
	cp FOLD/FOLD.h ino/FOLD.h

ino/drive.h: FOLD/drive.h | ino
	cp FOLD/drive.h ino/drive.h

ino/drive.cpp: FOLD/drive.ino | ino
	cp FOLD/drive.ino ino/drive.cpp

ino/wheel.h: FOLD/wheel.h | ino
	cp FOLD/wheel.h ino/wheel.h

ino/wheel.cpp: FOLD/wheel.ino | ino
	cp FOLD/wheel.ino ino/wheel.cpp

ino/wiring.h: FOLD/wiring.h | ino
	cp FOLD/wiring.h ino/wiring.h

/usr/share/arduino/libraries/Adafruit_MotorShield: 
	git clone git@github.com:adafruit/Adafruit_Motor_Shield_V2_Library.git /usr/share/arduino/libraries/Adafruit_MotorShield

inomake: ino/Makefile ino/FOLD.cpp ino/FOLD.h ino/drive.cpp ino/drive.h ino/wiring.h ino/wheel.h ino/wheel.cpp | ino ino/Arduino-Makefile /usr/share/arduino/libraries/Adafruit_MotorShield
	cd ino && make

upload: inomake
	cd ino && make upload

purge:
	rm -rf ino

clean:
	rm -rf gcctest/drive.*
	rm -rf gcctest/wiring.*
	rm -rf gcctest/*.o
	rm -rf gcctest/gcctest
	cp -rf ino/Arduino-Makefile .
	rm -rf ino
	mkdir -p ino
	mv Arduino-Makefile ino

