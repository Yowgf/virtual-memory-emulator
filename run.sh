#!/bin/bash

alg="$1"

if [ "$alg" = "" ]; then
    echo 'Usage: <program> <replacement-algorithm>'
    exit 1
fi

./build/main.out "$1" test/fixtures/simulador.log 2 1024
