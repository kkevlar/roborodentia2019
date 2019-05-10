

INOMAKE_NORMAL_DEPS=ino/Makefile \
ino/FOLD.cpp \
ino/FOLD.h \
ino/echo.h \
ino/drive.cpp \
ino/drive.h \
ino/main.cpp \
ino/main.h \
ino/test.cpp \
ino/test.h \
ino/wiring.h \
ino/wheel.h \
ino/wheel.cpp \
ino/lcd.h \
ino/lcd.cpp \
ino/shoot.h \
ino/shoot.cpp \
ino/control.h \
ino/control.cpp \
ino/aim.h \
ino/aim.cpp \
ino/collect.h \
ino/collect.cpp \
ino/echo.cpp \
ino/switch.cpp \
ino/testoptions.h\
ino/switch.h


INOMAKE_SPECIAL_DEPS=ino \
ino/Arduino-Makefile

GCCFLAGS=-Wall -Werror -g -O0

GCCTESTDEPS=gcctest/wiring.h\
gcctest/testoptions.h\
gcctest/control.h\
gcctest/collect.h\
gcctest/pretendarduino.h\
gcctest/aim.h\
gcctest/shoot.h

all: ino inomake test

test: gcctest/gcctest
	cp gcctest/gcctest test

gcctest/gcctest: gcctest/aim.o gcctest/pretendarduino.o gcctest/testaim.o
	gcc $(GCCFLAGS) $^ -lm -o $@

gcctest/aim.o: gcctest/aim.c $(GCCTESTDEPS)
	gcc $(GCCFLAGS) -c $< -o $@

gcctest/testaim.o: gcctest/testaim.c $(GCCTESTDEPS)
	gcc $(GCCFLAGS) -c $< -o $@

gcctest/pretendarduino.o: gcctest/pretendarduino.c $(GCCTESTDEPS)
	gcc $(GCCFLAGS) -c $< -o $@

gcctest/testoptions.h: 
	touch $@

gcctest/control.h: 
	touch $@

gcctest/collect.h: 
	touch $@

gcctest/shoot.h: 
	touch $@

gcctest/aim.c: FOLD/aim.ino
	cat $< | head -n 86 | sed -r 's;#include "aim.h";#include "pretendarduino.h";' | sed 's;om(";fake(";' > $@

gcctest/wiring.h: FOLD/wiring.h
	cat $< | sed -r 's;#ifndef WIRING_H;#include "pretendarduino.h"\n#ifndef WIRING_H;' > $@

gcctest/aim.h: FOLD/aim.h
	cp $< $@

ino:
	mkdir -p ino

ino/Makefile: INO-Makefile | ino
	cp INO-Makefile ino/Makefile

ino/Arduino-Makefile: | ino
	cd ino && git clone https://github.com/sudar/Arduino-Makefile.git

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

ino/lcd.h: FOLD/lcd.h | ino
	cp FOLD/lcd.h ino/lcd.h

ino/lcd.cpp: FOLD/lcd.ino | ino
	cp FOLD/lcd.ino ino/lcd.cpp

ino/shoot.h: FOLD/shoot.h | ino
	cp FOLD/shoot.h ino/shoot.h

ino/shoot.cpp: FOLD/shoot.ino | ino
	cp FOLD/shoot.ino ino/shoot.cpp

ino/test.h: FOLD/test.h | ino
	cp FOLD/test.h ino/test.h

ino/test.cpp: FOLD/test.ino | ino
	cp FOLD/test.ino ino/test.cpp

ino/main.h: FOLD/main.h | ino
	cp FOLD/main.h ino/main.h

ino/main.cpp: FOLD/main.ino | ino
	cp FOLD/main.ino ino/main.cpp

ino/echo.h: FOLD/echo.h | ino
	cp FOLD/echo.h ino/echo.h

ino/echo.cpp: FOLD/echo.ino | ino
	cp FOLD/echo.ino ino/echo.cpp

ino/control.h: FOLD/control.h | ino
	cp FOLD/control.h ino/control.h

ino/control.cpp: FOLD/control.ino | ino
	cp FOLD/control.ino ino/control.cpp

ino/aim.h: FOLD/aim.h | ino
	cp FOLD/aim.h ino/aim.h

ino/aim.cpp: FOLD/aim.ino | ino
	cp FOLD/aim.ino ino/aim.cpp

ino/collect.h: FOLD/collect.h | ino
	cp FOLD/collect.h ino/collect.h

ino/collect.cpp: FOLD/collect.ino | ino
	cp FOLD/collect.ino ino/collect.cpp

ino/switch.h: FOLD/switch.h | ino
	cp FOLD/switch.h ino/switch.h

ino/switch.cpp: FOLD/switch.ino | ino
	cp FOLD/switch.ino ino/switch.cpp

ino/wiring.h: FOLD/wiring.h | ino
	cp FOLD/wiring.h ino/wiring.h

ino/testoptions.h: FOLD/testoptions.h | ino
	cp FOLD/testoptions.h ino/testoptions.h

ino/utility: | ino
	mkdir ino/utility

inomake: $(INOMAKE_NORMAL_DEPS) | $(INOMAKE_SPECIAL_DEPS)
	cd ino && make

upload: inomake
	cd ino && make upload

purge: clean
	rm -rf ino
	rm -rf libs

clean:
	rm -rf gcctest/drive.*
	rm -rf gcctest/wiring.*
	rm -rf gcctest/*.o
	rm -rf gcctest/gcctest
	cp -rf ino/Arduino-Makefile .
	rm -rf ino
	mkdir -p ino
	mv Arduino-Makefile ino

