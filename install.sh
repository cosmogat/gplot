#!/bin/bash
# 25-06-2018
# alex
# install.sh

INSTALL_DIR="/usr/local/lib/"
if [ $UID -ne 0 ] ; then  
    echo "Are you root?" >&2 ; exit 1
fi

cd src
gcc -fPIC -c gplot.c -o gplot.o
ld -o libgplot.so gplot.o -shared
rm gplot.o
mv libgplot.so "$INSTALL_DIR"
cd ..
