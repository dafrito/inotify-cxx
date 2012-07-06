#! /bin/bash

automake --add-missing
autoreconf
automake --add-missing

echo "run ./configure && make"

