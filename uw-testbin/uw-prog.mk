
# Common to all of the new vm test programs.
# Note that this actually gets used in a subdirectory of this one.

# ROOT=../../root
BINDIR=/uw-testbin

# This is an attempt to find os161-1.11
# We assume that the directory this file lives in is under OS161DIR.
OS161DIR = ../..
include $(OS161DIR)/defs.mk
include $(OS161DIR)/mk/prog.mk


EXTRAS = readelf.out nm.out objdump.out $(PROG).S nm.out

all: $(PROG)

extras: $(EXTRAS)

readelf.out:	$(PROG).c $(PROG)
	cs350-readelf -a $(PROG) > readelf.out

objdump.out:	$(PROG).c $(PROG)
	cs350-objdump -s $(PROG) > objdump.out

$(PROG).S:	$(PROG).c $(PROG)
	cs350-objdump -d $(PROG) > $(PROG).S

nm.out:	$(PROG).c $(PROG)
	cs350-nm -n $(PROG) > nm.out

vclean: clean
	-rm $(EXTRAS) *.o

localinstall: doinstall
doinstall:
	[ -d $(BINDIR) ] || mkdir $(BINDIR)
	cp $(PROG) $(BINDIR)

