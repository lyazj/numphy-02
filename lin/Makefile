#!/usr/bin/env -S make -f

include ../Makefile.conf

# CFLAGS := $(subst -O3,-Og,$(CFLAGS))
BIN := $(filter-out gem cholesky,$(BIN))
PLT := $(shell ls *-plot 2>/dev/null)
RUN += $(PLT)
OUT += $(PLT:%=%.pdf)

include ../Makefile.rule

cholesky.o gem.o: defs.h
