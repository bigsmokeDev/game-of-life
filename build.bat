#!/bin/sh

gcc -o gol.exe gol.c -Lwin64 -lraylib -lgdi32 -lwinmm
