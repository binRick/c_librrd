#!/bin/bash
set -eou pipefail
reset
#[[ -d b ]] && rm -rf b
#[[ -d b ]] || 
    meson  --reconfigure --wipe b
(cd b && ninja)
cd b
#clear
meson test
#./test1
