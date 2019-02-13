
INOMAKE_NORMAL_DEPS=ino/Makefile \
ino/FOLD.cpp \
ino/FOLD.h \
ino/echo.h \
ino/drive.cpp \
ino/drive.h \
ino/wiring.h \
ino/wheel.h \
ino/wheel.cpp \
ino/control.h \
ino/control.cpp \
ino/echo.cpp \
ino/switch.cpp \
ino/testoptions.h\
ino/switch.h 

INOMAKE_SPECIAL_DEPS=ino \
ino/Arduino-Makefile \
/usr/share/arduino/libraries/Adafruit_MotorShield

all: ino inomake test

test: gcctest/gcctest
	cp gcctest/gcctest test

gcctest/gcctest: gcctest/drive.o gcctest/fakewheel.o gcctest/gcctest.o gcctest/cpTime.o
	g++ gcctest/drive.o gcctest/fakewheel.o gcctest/gcctest.o gcctest/cpTime.o -lm -o gcctest/gcctest

gcctest/gcctest.o: gcctest/gcctest.cpp
	g++ -c gcctest/gcctest.cpp -o gcctest/gcctest.o

gcctest/fakewheel.o: gcctest/fakewheel.cpp
	g++ -c gcctest/fakewheel.cpp -o gcctest/fakewheel.o

gcctest/drive.o: gcctest/drive.cpp gcctest/drive.h gcctest/wiring.h gcctest/testoptions.h gcctest/cpTime.h
	g++ -c gcctest/drive.cpp -o gcctest/drive.o

gcctest/cpTime.o: gcctest/cpTime.cpp gcctest/cpTime.h
	g++ -c gcctest/cpTime.cpp -o gcctest/cpTime.o

gcctest/drive.h: FOLD/drive.h
	cat FOLD/drive.h | sed -r 's;#include "wheel.h";#include "fakewheel.h"\n#include <math.h>;' > gcctest/drive.h

gcctest/wiring.h: FOLD/wiring.h
	cp FOLD/wiring.h gcctest/wiring.h

gcctest/testoptions.h: FOLD/testoptions.h
	cp FOLD/testoptions.h gcctest/testoptions.h

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

ino/echo.h: FOLD/echo.h | ino
	cp FOLD/echo.h ino/echo.h

ino/echo.cpp: FOLD/echo.ino | ino
	cp FOLD/echo.ino ino/echo.cpp

ino/control.h: FOLD/control.h | ino
	cp FOLD/control.h ino/control.h

ino/control.cpp: FOLD/control.ino | ino
	cp FOLD/control.ino ino/control.cpp

ino/switch.h: FOLD/switch.h | ino
	cp FOLD/switch.h ino/switch.h

ino/switch.cpp: FOLD/switch.ino | ino
	cp FOLD/switch.ino ino/switch.cpp

ino/wiring.h: FOLD/wiring.h | ino
	cp FOLD/wiring.h ino/wiring.h

ino/testoptions.h: FOLD/testoptions.h | ino
	cp FOLD/testoptions.h ino/testoptions.h

/usr/share/arduino/libraries/Adafruit_MotorShield: 
	git clone git@github.com:adafruit/Adafruit_Motor_Shield_V2_Library.git /usr/share/arduino/libraries/Adafruit_MotorShield

inomake: $(INOMAKE_NORMAL_DEPS) | $(INOMAKE_SPECIAL_DEPS)
	cd ino && make

upload: inomake
	cd ino && make upload

purge: clean
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

