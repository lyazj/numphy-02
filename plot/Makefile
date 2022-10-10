#!/usr/bin/env -S make -f

include ../Makefile.conf

# CFLAGS := $(subst -O3,-Og,$(CFLAGS))
BIN := $(filter-out tdm cubic,$(BIN))
RUN += plot-plot
OUT += plot-plot.pdf

include ../Makefile.rule

$(OBJ): defs.h ../runge/defs.h ../che/defs.h

tdm.o: ../runge/tdm.c
cubic.o: ../runge/cubic.c

plot: cubic.o tdm.o
