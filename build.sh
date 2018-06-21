#!/bin/bash

g++ -o randomdots examples/randomdots/src/randomdots.cpp pixel/src/* -Ipixel/include -std=c++17 -lGLEW -lGL -lSDL2 -g

