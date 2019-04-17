# Makefile for activity 1
# 

CFLAGS_1 = -Wno-format -g -ggdb -std=c99

all:
	@echo command choices:
	@echo make phase1
	@echo or...
	@echo make phase2
	@echo or...
	@echo make clean

# phase 1 debugging
phase1:
	@-rm -f Phase*
	gcc $(CFLAGS_1) good-life.c -o good-life
	@-touch Phase1


CFLAGS_2 = -g -ggdb -std=c99

# phase 2 debugging
phase2:
	@-rm -f Phase*
	gcc $(CFLAGS_2) good-life.c -o good-life
	@-touch Phase2

clean:
	-rm -f good-life
	@-rm -f Phase*

