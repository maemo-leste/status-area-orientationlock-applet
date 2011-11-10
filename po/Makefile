

GETTEXT_PACKAGE = status-area-orientationlock-applet
PACKAGE = status-area-orientationlock-applet

SHELL = /bin/sh

prefix = /usr
DATADIRNAME = share
itlocaledir = $(prefix)/$(DATADIRNAME)/locale

INSTALL = /scratchbox/tools/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644

GMSGFMT = /usr/bin/msgfmt
MSGFMT = /usr/bin/msgfmt
XGETTEXT = /usr/bin/xgettext
MSGMERGE = /usr/bin/msgmerge 

PO_LINGUAS= de_DE en_GB en_US pl_PL fi_FI fr_FR

USE_LINGUAS= de_DE en_GB en_US pl_PL fi_FI fr_FR

POFILES=$(shell LINGUAS="$(PO_LINGUAS)"; for lang in $$LINGUAS; do printf "$$lang.po "; done)

DISTFILES = Makefile POTFILES.in $(POFILES)
EXTRA_DISTFILES = ChangeLog POTFILES.skip Makevars LINGUAS

POTFILES = \
	../src/gui.py \
# This comment gets stripped out

CATALOGS=$(shell LINGUAS="$(USE_LINGUAS)"; for lang in $$LINGUAS; do printf "$$lang.gmo "; done)

.SUFFIXES:
.SUFFIXES: .po .gmo .mo 

.po.mo:
	$(MSGFMT) -o $@ $<

.po.gmo:
	file=`echo $* | sed 's,.*/,,'`.gmo \
	  && rm -f $$file && $(GMSGFMT) -o $$file $<

all: compile

compile: $(CATALOGS)

$(GETTEXT_PACKAGE).pot: $(POTFILES)
	$(XGETTEXT) --package-name=$(PACKAGE) -o $(GETTEXT_PACKAGE).pot $(POTFILES) 

install: all
	linguas="$(USE_LINGUAS)"; \
	for lang in $$linguas; do \
	  dir=$(DESTDIR)$(itlocaledir)/$$lang/LC_MESSAGES; \
	  mkdir -p $$dir; \
	  if test -r $$lang.gmo; then \
	    $(INSTALL_DATA) $$lang.gmo $$dir/$(GETTEXT_PACKAGE).mo; \
	    echo "installing $$lang.gmo as $$dir/$(GETTEXT_PACKAGE).mo"; \
	  fi; \
	done

clean: 	
	rm -f *.mo *.gmo

update-po: 
	$(MAKE) $(GETTEXT_PACKAGE).pot
	linguas="$(USE_LINGUAS)"; \
	for lang in $$linguas; do \
	  echo "$$lang:"; \
	  if test -r $$lang.po; then \
	    $(MSGMERGE) -U $$lang.po $(GETTEXT_PACKAGE).pot; \
	  else \
	    cp $(GETTEXT_PACKAGE).pot $$lang.po; \
	  fi; \
	done

