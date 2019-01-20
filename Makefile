

all: ino inomake

ino:
	mkdir ino

ino/Makefile: INO-Makefile | ino
	cp INO-Makefile ino/Makefile

ino/Arduino-Makefile: | ino
	cd ino && git clone git@github.com:sudar/Arduino-Makefile.git

ino/FOLD.ino: FOLD.ino | ino
	cp FOLD.ino ino/FOLD.ino

ino/FOLD.h: FOLD.h | ino
	cp FOLD.h ino/FOLD.h

inomake: ino/Makefile ino/FOLD.ino ino/FOLD.h  | ino ino/Arduino-Makefile 
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

