#!/usr/bin/env -S make -f

include ../Makefile.conf

# CFLAGS := $(subst -O3,-Og,$(CFLAGS))
BIN := $(filter-out poly chebyshev intp tdm cubic,$(BIN))
RUN += runge-plot che-plot cub-plot
OUT += runge-plot.pdf che-plot.pdf cub-plot.pdf

include ../Makefile.rule

$(OBJ): defs.h ../che/defs.h

poly.o: ../che/poly.c
poly-test.o: ../che/poly-test.c
chebyshev.o: ../che/chebyshev.c
chebyshev-test.o: ../che/chebyshev-test.c

poly-test: poly.o
chebyshev-test: chebyshev.o poly.o
intp-test: intp.o poly.o
tdm-test: tdm.o
cubic-test: cubic.o tdm.o

runge: intp.o poly.o
che: chebyshev.o poly.o
cub: cubic.o tdm.o

runge-plot.run: runge.out
che-plot.run: che.out
cub-plot.run: cub.out
