#
# Makefile for src/testbin (sources for programs installed in /testbin)
#

include ../defs.mk

all depend tags clean install vclean:
	(cd common && $(MAKE) $@)
	(cd argtest && $(MAKE) $@)
	(cd segments && $(MAKE) $@)
	(cd syscall && $(MAKE) $@)
	(cd vm-crash1 && $(MAKE) $@)
	(cd vm-crash2 && $(MAKE) $@)
	(cd vm-crash3 && $(MAKE) $@)
	(cd vm-data1 && $(MAKE) $@)
	(cd vm-data2 && $(MAKE) $@)
	(cd vm-data3 && $(MAKE) $@)
	(cd vm-stack1 && $(MAKE) $@)
	(cd vm-stack2 && $(MAKE) $@)
	(cd vm-mix1 && $(MAKE) $@)
	(cd vm-mix1-exec && $(MAKE) $@)
	(cd vm-mix1-fork && $(MAKE) $@)
	(cd vm-mix2 && $(MAKE) $@)
