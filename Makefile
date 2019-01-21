

all: ino inomake

ino:
	mkdir ino

ino/Makefile: INO-Makefile | ino
	cp INO-Makefile ino/Makefile

ino/Arduino-Makefile: | ino
	cd ino && git clone git@github.com:sudar/Arduino-Makefile.git

ino/FOLD.cpp: FOLD.ino | ino
	cp FOLD.ino ino/FOLD.cpp

ino/FOLD.h: FOLD.h | ino
	cp FOLD.h ino/FOLD.h

ino/drive.h: drive.h | ino
	cp drive.h ino/drive.h

ino/drive.cpp: drive.ino | ino
	cp drive.ino ino/drive.cpp

ino/wiring.h: wiring.h | ino
	cp wiring.h ino/wiring.h

/usr/share/arduino/libraries/Adafruit_MotorShield: 
	git clone git@github.com:adafruit/Adafruit_Motor_Shield_V2_Library.git /usr/share/arduino/libraries/Adafruit_MotorShield

inomake: ino/Makefile ino/FOLD.cpp ino/FOLD.h ino/drive.cpp ino/drive.h ino/wiring.h | ino ino/Arduino-Makefile /usr/share/arduino/libraries/Adafruit_MotorShield
	cd ino && make

upload: inomake
	cd ino && make upload

purge:
	rm -rf ino

clean:
	cp -rf ino/Arduino-Makefile .
	rm -rf ino
	mkdir -p ino
	mv Arduino-Makefile ino

