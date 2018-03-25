#!/bin/sh


gcc -std=c11 -Wall -Werror $1 -o build/$(echo $1 | sed 's/\..*$//')
