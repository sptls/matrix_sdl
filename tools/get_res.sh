#!/bin/bash
DLLS=`ldd.exe matrix.exe | grep -o -E '(\/{1}[a-zA-Z0-9_+-]{1,}){1,}\.(dll|DLL)' | grep -o -E '\/mingw.*'`

cp $DLLS bin/