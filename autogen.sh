#!/bin/sh

set -ex

rm -rf autom4te.cache

aclocal --force
autoheader
autoconf -f -W all
automake -f -a -c -W all

rm -rf autom4te.cache

