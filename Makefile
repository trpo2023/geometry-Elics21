


all : obj/geometry/geometry.o obj/libgeometry/check.o
	gcc -Wall -Werror obj/geometry/geometry.o obj/libgeometry/check.o -o geometry

obj/geometry/geometry.o : src/geometry/geometry.c
	gcc -Wall -Werror -Isrc/ -c src/geometry/geometry.c -o  obj/geometry/geometry.o

obj/libgeometry/check.o : src/libgeometry/check.c
	gcc -Wall -Werror -Isrc/ -c src/libgeometry/check.c -o  obj/libgeometry/check.o

clean :
	rm geometry obj/libgeometry/check.o obj/geometry/geometry.o 

run :
	./geometry
