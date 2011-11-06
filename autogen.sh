#!/bin/bash
libtoolize --copy --force --automake
aclocal
autoconf
automake --add-missing -c
