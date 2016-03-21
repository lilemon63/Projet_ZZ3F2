#!/bin/bash

gnuplot -e "p1='pareto_$1.dat';p2='pareto_$2.dat" plotCmpPareto
