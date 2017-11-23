
# For windows, "cat" needs to be replaced with "type"
CAT = type

THOR = thor

LUA = lua

CXX = g++
CXX_FLAGS = -O2

example: main.o
	$(CXX) $(CXX_FLAGS) main.o -o example

.SILENT: main.o
main.o: main.cpp person.hpp

person.hpp: class.gen person.lua lib.lua
	@echo Generating class...
	@$(LUA) -l person -l lib class.gen > person.hpp
	@echo Ok!

class.gen: class.cppt
	@echo Compiling generator...
	@$(CAT) class.cppt | $(THOR) > class.gen
	@echo Ok!

run: example
	@./example

clean:
	-@rm example.exe class.gen person.hpp main.o
	-@del example.exe class.gen person.hpp main.o

# Do not remove this line!
.DELETE_ON_ERROR: