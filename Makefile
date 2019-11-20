CC=g++
CXXFLAGS=-g -std=c++17 -pedantic
ODIR=.
BUILD=build

_OBJ=$(BUILD)/AutomataFinitoDeterminista.o $(BUILD)/AutomataFinitoNodeterminista.o  $(BUILD)/NFA2DFA.o
OBJ=$(patsubst %,%,$(_OBJ))

all:NFA2DFA

$(BUILD)/AutomataFinitoDeterminista.o: $(ODIR)/AutomataFinitoDeterminista.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS)

$(BUILD)/AutomataFinitoNodeterminista.o: $(ODIR)/AutomataFinitoNodeterminista.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS)

$(BUILD)/NFA2DFA.o: $(ODIR)/NFA2DFA.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS)

NFA2DFA: $(OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS) -lm

.PHONY:clean

clean:
	rm -rf build/* NFA2DFA

