#!/bin/sh

PNMHIDE=../build/src/pnmhide

$PNMHIDE -e "./src/pnmhide  -d stego.pnmres: WHATEVER JUST A LONG TEXTr -d stego.pnmr -d stego.pnmr -d stego.pnmr -d stego.pnmr -d stego.pnmr -d stego.pnmr -d stego.pnm./src/pnmhide  -d stego.pnmres: WHATEVER JUST A LONG TEXTr -d stego.pnmr -d stego.pnmr -d stego.pnmr -d stego.pnmr -d stego.pnmr -d stego.pnmr -d stego.pnm" -d ../test/cover.pnm > stego.pnm && \
    pnmtojpeg stego.pnm > stego.jpg && \
    pnmhistmap ../test/cover.pnm | pnmtojpeg > cover-hist.jpg && \
    pnmhistmap stego.pnm | pnmtojpeg > stego-hist.jpg

exit
