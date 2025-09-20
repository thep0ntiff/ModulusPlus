# Makefile for ModulusPlus project

CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinc -fPIC

SRC = src/modplus.o src/montgomery.o src/uint256.o
OBJ = examples/main.o
TARGET = modulus_plus
STATICLIB = libmodplus.a
SHAREDLIB = libmodplus.so
HEADERS = inc/modplus.h inc/uint256.h inc/montgomery.h


PREFIX ?= /usr
INCLUDEDIR = $(PREFIX)/include
LIBDIR = $(PREFIX)/lib
BINDIR = $(PREFIX)/bin

.PHONY: all clean install uninstall

all: $(TARGET) $(STATICLIB) $(SHAREDLIB)

$(TARGET): $(OBJ) $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

$(STATICLIB): $(SRC)
	ar rcs $@ $^

$(SHAREDLIB): $(SRC)
	$(CC) -shared -o $@ $^

examples/main.o: examples/main.c
	$(CC) $(CFLAGS) -c $< -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

install: all
	install -Dm755 $(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)
	install -Dm644 $(STATICLIB) $(DESTDIR)$(LIBDIR)/$(STATICLIB)
	install -Dm755 $(SHAREDLIB) $(DESTDIR)$(LIBDIR)/$(SHAREDLIB)
	for header in $(HEADERS); do \
		install -Dm644 $$header $(DESTDIR)$(INCLUDEDIR)/$$(basename $$header); \
	done

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET)
	rm -f $(DESTDIR)$(LIBDIR)/$(STATICLIB)
	rm -f $(DESTDIR)$(LIBDIR)/$(SHAREDLIB)
	for header in $(HEADERS); do \
		rm -f $(DESTDIR)$(INCLUDEDIR)/$$(basename $$header); \
	done
clean:
	rm -f $(OBJ) $(SRC) $(TARGET) $(STATICLIB) $(SHAREDLIB)
