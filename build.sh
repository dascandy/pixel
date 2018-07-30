#!/bin/bash

PIXEL_ARGS="-Lpixel/lib -lpixel -Ipixel/include -std=c++17 -lGLEW -lGL -lSDL2"

mkdir pixel/lib pixel/obj examples/bin -p
g++ -c -o pixel/obj/Window.o pixel/src/Window.cpp -Ipixel/include -std=c++17 -g
g++ -c -o pixel/obj/Canvas.o pixel/src/Canvas.cpp -Ipixel/include -std=c++17 -g
ar rcs pixel/lib/libpixel.a pixel/obj/Window.o pixel/obj/Canvas.o
g++ -o examples/bin/image_swap examples/image_swap/src/image_swap.cpp $PIXEL_ARGS -g
g++ -o examples/bin/randomdots examples/randomdots/src/randomdots.cpp $PIXEL_ARGS -g


