#Thor

Thor is a generic template compiler.

## Using Thor

To use Thor, simply feed it the template via STDIN.
It will spit out the compiled template to STDOUT.

Example:

    cat somefile.template | thor

## Compiling Thor

Thor is written in a single `.cpp` file, inside `src` folder.
It requires C++14. To compile thor, just feed the cpp file to
your C++14 compiler of choice.

Example:

    g++ src/main.cpp -O2 -o build/thor

## Caveats

Thor is meant to be as generic as possible. But, for now, it spits
out the compiled template as a [lua](http://www.lua.org) script.