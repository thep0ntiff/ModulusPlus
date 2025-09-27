# Makefile for ModulusPlus project

CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinc -fPIC

SRC = src/modplus.o src/montgomery.o src/uint256.o
OBJ = examples/main.o
STATICLIB = libmodplus.a
SHAREDLIB = libmodplus.so
HEADERS = inc/modplus.h inc/uint256.h inc/montgomery.h

ifeq ($(OS),Windows_NT)
    EXE := .exe
    RM := del /Q
    MKDIR := mkdir
    CP := copy
    PREFIX ?= C:/Program Files/ModulusPlus
    INCLUDEDIR = $(PREFIX)/include
    LIBDIR = $(PREFIX)/lib
    BINDIR = $(PREFIX)/bin
else
    EXE :=
    RM := rm -f
    MKDIR := mkdir -p
    CP := cp
    PREFIX ?= /usr
    INCLUDEDIR = $(PREFIX)/include
    LIBDIR = $(PREFIX)/lib
    BINDIR = $(PREFIX)/bin
endif

TARGET = modulus_plus$(EXE)

.PHONY: all clean install uninstall

all: $(TARGET) $(STATICLIB) $(SHAREDLIB)

$(TARGET): $(OBJ) $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

$(STATICLIB): $(SRC)
	ar rcs $@ $^

$(SHAREDLIB): $(SRC)
	$(CC) -shared -o $@ $^

clean:
ifeq ($(OS),Windows_NT)
	-$(RM) $(TARGET) $(STATICLIB) $(SHAREDLIB) $(SRC)
	-if exist src del /S /Q src\*.o
	-if exist examples del /S /Q examples\*.o
else
	$(RM) $(TARGET) $(STATICLIB) $(SHAREDLIB) $(SRC) $(OBJ)
endif

install:
ifeq ($(OS),Windows_NT)
	$(MKDIR) "$(BINDIR)" "$(LIBDIR)" "$(INCLUDEDIR)"
	$(CP) $(STATICLIB) "$(LIBDIR)"
	$(CP) "inc\modplus.h" "$(INCLUDEDIR)"
	$(CP) "inc\uint256.h" "$(INCLUDEDIR)"
	$(CP) "inc\montgomery.h" "$(INCLUDEDIR)"
	
else
	install -d $(DESTDIR)$(BINDIR) $(DESTDIR)$(LIBDIR) $(DESTDIR)$(INCLUDEDIR)
	install -m 755 $(TARGET) $(DESTDIR)$(BINDIR)
	install -m 644 $(STATICLIB) $(DESTDIR)$(LIBDIR)
	install -m 644 $(SHAREDLIB) $(DESTDIR)$(LIBDIR)
	install -m 644 $(HEADERS) $(DESTDIR)$(INCLUDEDIR)
endif

uninstall:
ifeq ($(OS),Windows_NT)
	rmdir /S /Q "$(PREFIX)"
	
else
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET) $(DESTDIR)$(LIBDIR)/$(STATICLIB) $(DESTDIR)$(LIBDIR)/$(SHAREDLIB)
	cd $(DESTDIR)$(INCLUDEDIR) && rm -f $(notdir $(HEADERS))
endif