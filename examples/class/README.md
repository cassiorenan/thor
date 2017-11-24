# Class template

Not to be mistaken for an actual C++ template :)

This example demonstrates a template to generate basic classes.
A "Person" class is generated according to metadata defined in `person.lua`.
Then, it is used to store and display some data by `main.cpp`.

Check the makefile to understand the basic flow.

## Building the example

The `thor` binary must be accessible to the shell.

`lua` must also be available.

Assuming these prerequisites are met, simply run `make`.