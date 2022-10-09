#!/usr/bin/env -S make -f

include ../Makefile.conf

# CFLAGS := $(subst -O3,-Og,$(CFLAGS))
BIN := $(filter-out poly chebyshev,$(BIN))

include ../Makefile.rule

$(OBJ): defs.h ../che/defs.h
poly.o: ../che/poly.c
chebyshev.o: ../che/chebyshev.c
