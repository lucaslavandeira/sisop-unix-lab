#!/bin/sh

OUT_DIR=bin/

gcc -std=c11 -Wall -Werror -g $1 -o ${OUT_DIR}/$(echo $1 | sed 's/\..*$//')
