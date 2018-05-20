OBJS=lib-orientation-lock-status-menu-widget.o
SOURCES=lib-orientation-lock-status-menu-widget.c
LIB=lib-orientationlock-status-menu.so
PKG_FLAGS=$(shell pkg-config hildon-1 libhildondesktop-1 gconf-2.0 dbus-1 --libs --cflags)
CCFLAGS=-shared -fPIC
CC=gcc

all:$(LIB)

$(LIB):$(OBJS)
	$(CC) $(CCFLAGS) $(PKG_FLAGS) $(OBJS) -o $(LIB)

.c.o:
	$(CC) $(CCFLAGS) $(PKG_FLAGS) -c $< -o $@

.PHONE: clean all

clean:
	rm -f $(OBJS) $(LIB)
