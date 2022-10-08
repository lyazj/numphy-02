#!/usr/bin/env -S make -f

include ../Makefile.conf

# CFLAGS := $(subst -O3,-Og,$(CFLAGS))
BIN := $(filter-out poly chebyshev,$(BIN))
RUN += che-log2-plot
OUT += che-log2-plot.pdf che-log2-plot-err.pdf

include ../Makefile.rule

poly-test: poly.o
poly.o poly-test.o: defs.h
chebyshev-test: chebyshev.o poly.o
chebyshev.o chebyshev-test.o: defs.h
che-log2: chebyshev.o poly.o
che-log2.o: defs.h
