#!/bin/bash

mkdir -p deps

# Termbox
git clone https://github.com/nsf/termbox termbox
cd termbox
./waf configure --prefix=/
./waf build
./waf install --targets=termbox_static --destdir=../deps
cd ..
rm -rf termbox
