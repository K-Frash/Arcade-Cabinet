#!/usr/bin/env bash

cd $(dirname $BASH_SOURCE)
cd ..
./sorcery -deck1 ./tests/inspect_test.deck -init ./tests/inspect_test.init -testing 
