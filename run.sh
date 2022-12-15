#!/bin/sh
pip3.10 install -r requirements.txt

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    g++ -O3 -Wall -shared -std=c++17 -fPIC $(python3 -m pybind11 --includes) src/controller.cpp -o src/controller$(python3-config --extension-suffix)
elif [[ "$OSTYPE" == "darwin"* ]]; then
    g++ -std=c++17 -shared -undefined dynamic_lookup -I./pybind11/include/ `python3.10 -m pybind11 --includes` src/controller.cpp -o src/controller.so `python3-config --ldflags`
fi
    
python3.10 ./src/run.py
