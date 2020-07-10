PREFIX ?= /usr
ICONPATH ?= $(PREFIX)/share/icons/hicolor
DESKTOPPATH ?= $(shell pkg-config libhildondesktop-1 --variable=hildonstatusmenudesktopentrydir)

ICONS_48 = \
	orientation-lock-icon.auto.png \
	orientation-lock-icon.landscape.png

ICONS_18 = orientation-lock.landscape.png

DESKTOPFILE = status-area-orientationlock-applet.desktop

all:

install:
	mkdir -p $(DESTDIR)$(DESKTOPPATH)
	cp -f $(DESKTOPFILE) $(DESTDIR)$(DESKTOPPATH)
	mkdir -p $(DESTDIR)$(ICONPATH)/48x48/hildon
	mkdir -p $(DESTDIR)$(ICONPATH)/18x18/hildon
	cp -f $(ICONS_48) $(DESTDIR)$(ICONPATH)/48x48/hildon
	cp -f $(ICONS_18) $(DESTDIR)$(ICONPATH)/18x18/hildon
