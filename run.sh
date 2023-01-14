#!/bin/bash

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    pip install -r requirements.txt
    . ~/.profile
    g++ -O3 -Wall -shared -std=c++17 -fPIC $(python3 -m pybind11 --includes) src/controller.cpp -o src/controller$(python3-config --extension-suffix)
    python3 ./src/run.py
elif [[ "$OSTYPE" == "darwin"* ]]; then
    pip3.10 install -r requirements.txt
    g++ -std=c++17 -shared -undefined dynamic_lookup -I./pybind11/include/ `python3.10 -m pybind11 --includes` src/controller.cpp -o src/controller.so `python3-config --ldflags`
    g++ -std=c++17 -shared -undefined dynamic_lookup -I./pybind11/include/ `python3.10 -m pybind11 --includes` src/unit.cpp -o src/unit.so `python3-config --ldflags`
    g++ -std=c++17 -shared -undefined dynamic_lookup -I./pybind11/include/ `python3.10 -m pybind11 --includes` src/stack.cpp src/unit.cpp -o src/stack.so `python3-config --ldflags`
    g++ -std=c++17 -shared -undefined dynamic_lookup -I./pybind11/include/ `python3.10 -m pybind11 --includes` src/hero.cpp src/stack.cpp src/unit.cpp src/ability.cpp -o src/hero.so `python3-config --ldflags`
    g++ -std=c++17 -shared -undefined dynamic_lookup -I./pybind11/include/ `python3.10 -m pybind11 --includes` src/battlefield.cpp src/hero.cpp src/stack.cpp src/unit.cpp src/ability.cpp -o src/battlefield.so `python3-config --ldflags`
    python3.10 ./src/run.py
fi
    
