#!/bin/bash

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    pip install -r requirements.txt
    . ~/.profile
    g++ -O3 -Wall -shared -std=c++17 -fPIC $(python3 -m pybind11 --includes) src/include/bindings.cpp src/include/battle.cpp src/include/hero.cpp src/include/stack.cpp src/include/controller.cpp -o src/bindings$(python3-config --extension-suffix)
    python3 ./run.py
elif [[ "$OSTYPE" == "darwin"* ]]; then
    pip3.10 install -r requirements.txt
    g++ -std=c++17 -shared -undefined dynamic_lookup -I./pybind11/include/ `python3.10 -m pybind11 --includes` src/include/bindings.cpp src/include/battle.cpp src/include/hero.cpp src/include/stack.cpp src/include/controller.cpp -o src/bindings.so `python3-config --ldflags`
    python3.10 ./run.py
fi
    

