#флаг для запуска компиляции файла .c
CC = gcc

#флаг для доступа к файлу/папке геометрии
APP_NAME = geometry
#Название флага, с помощью которого мы получим доступ к папке с файлами статистической библиотеки
LIB_NAME = libgeometry

#Флаг для запуска вывода предупреждения компилятора
CFLAGS = -Wall -Werror

#Добавление папки src для включения пути и изменение зависимых источников из файла заголовка(-MMD)
CPPFLAGS = -I src -MD -MMD

#флаг для доступа к папке bin в следующем коде Makefile
BIN_DIR = bin
#флаг для доступа к папке obj в следующем коде Makefile
OBJ_DIR = obj
#флаг для доступа к папке src в следующем коде Makefile
SRC_DIR = src

#доступ к файлу исполняемого кода (bin/geometry)
APP_PATH = $(BIN_DIR)/$(APP_NAME)
#доступ к исполняемым файлам дополнительных файлов (статистических библиотек) (obj/src/libgeometry/libgeometry.o)
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).o

#расширение файлов кода
SRC_EXT = c

#найдите файлы с расширением .c в папке src/geometry
APP_SOURCES = $(shell find $(SRC_DIR)/$(APP_NAME) -name '*.$(SRC_EXT)')
#Переход к объектным файлам (.o) исполняемого файла
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)


#найдите файлы с расширением .c в папке src/libgeometry
LIB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_NAME) -name '*.$(SRC_EXT)')
#Переход к объектным файлам (.o) исполняемого файла
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

#путь к библиотекам .h, которые мы подключаем
DEPS = $(APP_OBJECTS:.o=.h) $(LIB_OBJECTS:.o=.h)

all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ 

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean

clean:
	$(RM) $(APP_PATH) $(OBJ_DIR)/*/*/*.[od]

.PHONY: run

run:
	./bin/geometry

hello: main.o libgeometry.o
        $(CC) $(CFLAGS) -o $@ $^

main.o: main.c
        $(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

libhello.a: hello.o
        ar rcs $@ $^

hello.o: hello.c
        $(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

-include main.d hello.d