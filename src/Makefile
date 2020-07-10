LIBDIR ?= $(shell pkg-config libhildondesktop-1 --variable=hildondesktoplibdir)

OBJS=lib-orientation-lock-status-menu-widget.o
SOURCES=lib-orientation-lock-status-menu-widget.c
LIB=lib-orientationlock-status-menu.so
PKG_FLAGS=$(shell pkg-config hildon-1 libhildondesktop-1 gconf-2.0 dbus-1 --libs --cflags)
CCFLAGS=-shared -fPIC
CC=gcc

all: $(LIB)

$(LIB): $(OBJS)
	$(CC) $(CCFLAGS) $(PKG_FLAGS) $(OBJS) -o $(LIB)

.c.o:
	$(CC) $(CCFLAGS) $(PKG_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIB)

install: all
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(LIB) $(DESTDIR)$(LIBDIR)
	chmod 755 $(DESTDIR)$(LIBDIR)/$(LIB)

.PHONY: clean all install
