#!/bin/bash
set -eou pipefail
reset

BD="$(pwd)/.build"

if [[ -d "$BD" ]]; then
    meson --reconfigure --wipe $BD
else
    meson $BD
fi
cd $BD
ninja

clear

meson test -v

./test1
