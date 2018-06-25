#!/bin/bash
# 25-06-2018
# alex
# install.sh

INSTALL_DIR="/usr/local/lib/"
HEADER_DIR="/usr/local/include/"
LIB_NAME="libgplot.so"
ACT_DIR=$PWD
if [ $UID -ne 0 ] ; then  
    echo "Are you root?" >&2 ; exit 1
fi

cd src
gcc -march=native -O3 -pipe -W -Wall -Wextra -ansi -pedantic -D_GNU_SOURCE -fPIC -c gplot.c -o gplot.o
ld -o "$LIB_NAME" gplot.o -shared
rm gplot.o
mv "$LIB_NAME" "$INSTALL_DIR"
cp gplot.h "$HEADER_DIR"
cd $INSTALL_DIR
chown root:staff "$LIB_NAME"
chmod 644 "$LIB_NAME"
cd $HEADER_DIR
chown root:staff gplot.h
chmod 644 gplot.h
cd $ACT_DIR
