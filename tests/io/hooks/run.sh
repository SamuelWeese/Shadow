#!/bin/bash
gcc -fPIC -shared -o hook.so hook.c -ldl