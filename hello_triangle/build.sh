#!/bin/bash

echo "On building hello triangle..."

g++ -Wall -pedantic -g main.cxx Shader.cpp glad.c -ldl -lglfw -o application