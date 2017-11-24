# Thor

Thor is a generic template compiler.

## Using Thor

To use Thor, simply feed it the template via STDIN.
It will spit out the compiled template to STDOUT.

Example:

    cat somefile.template | thor

## Requirements

To build `thor`, you only need a working C++14 compiler.
No extra dependencies!

To compile using the Makefile, you also need `make`.

`thor` itself does not depend on [lua](http://www.lua.org), but the
compiled generators that it produces do. Any version is fine, but `5.3`
is recommended.
	
## Compiling Thor

### The easy way

Open the `SETTINGS` file to define your platform and installation path.

Then, run `make`.

### The "other" way

`thor`'s source is just a single `.cpp` file.
You can just feed `src/main.cpp` to your C++14 compiler of choice.

Example:

    g++ src/main.cpp -O2 -o build/thor

## Running the examples

You can simply pipe the examples through thor, then through lua.
The generated code should be ready to compile:

Example:

    cd examples/require
    cat main.cppt | thor | lua -l library | g++ -c -o exec -xc++ -

