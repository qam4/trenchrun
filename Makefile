all:
	make -f trenchrun.mk
	make -f testsrunner.mk

run:
	make -f trenchrun.mk run

dbg:
	make -f trenchrun.mk dbg

test:
	make -f testsrunner.mk run