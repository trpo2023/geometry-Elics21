.PHONY: all clean run
# Цель будет выполняться, даже если в корне репозитория создан файл с именем clean или all или run


all : bin/geometry


bin/geometry : obj/geometry/geometry.o obj/libgeometry/check.o
	gcc -Wall -Werror $^ -o $@
# $^ (список зависимостей) = obj/geometry/geometry.o obj/libgeometry/check.o ; $@ (имя цели) = geometry

obj/geometry/geometry.o : src/geometry/geometry.c
	gcc -Wall -Werror -Isrc/ -c $< -o  $@
# $< (первая зависимость) = src/geometry/geometry.c obj/libgeometry/check.o ; $@ (имя цели) = obj/geometry/geometry.o

obj/libgeometry/check.o : src/libgeometry/check.c
	gcc -Wall -Werror -Isrc/ -c $< -o  $@

clean :
	rm bin/geometry
	rm obj/geometry/*.o
	rm obj/libgeometry/*.o 

run :
	./bin/geometry



