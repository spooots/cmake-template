#!/bin/bash
cmake -D COVERAGE=1 . ../foobla 
make all
ctest -D ExperimentalMemCheck .
