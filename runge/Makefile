#!/usr/bin/env -S make -f

include ../Makefile.conf

# CFLAGS := $(subst -O3,-Og,$(CFLAGS))
BIN := $(filter-out poly chebyshev intp,$(BIN))
RUN += runge-plot che-plot
OUT += runge-plot.pdf che-plot.pdf

include ../Makefile.rule

$(OBJ): defs.h ../che/defs.h
poly.o: ../che/poly.c
poly-test.o: ../che/poly-test.c
chebyshev.o: ../che/chebyshev.c
chebyshev-test.o: ../che/chebyshev-test.c
poly-test: poly.o
chebyshev-test: chebyshev.o poly.o
intp-test: intp.o poly.o
runge: intp.o poly.o
che: chebyshev.o poly.o
runge-plot.run: runge.out
che-plot.run: che.out