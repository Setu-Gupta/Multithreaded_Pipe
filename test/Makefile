CXX = g++
CXX_FLAGS = -pedantic -Wall -Wextra -Werror -std=c++20

OPT_FLAGS = -Ofast -march=native -flto
DBG_FLAGS = -g3 -Og -ggdb

INCLPATH = ./../pipe

.PHONY: release
release: CXX_FLAGS += $(OPT_FLAGS)
release: test

.PHONY: debug
debug: CXX_FLAGS += $(DBG_FLAGS)
debug: test

test: main.cc
	$(CXX) -I$(INCLPATH) $(CXX_FLAGS) main.cc -o $@

.PHONY: clean
clean:
	rm test
