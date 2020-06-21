CC = g++
CFLAGS = -Wall -Wextra -Wshadow -pedantic -O2
OBJ = main.o token.o tokenstream.o calculator.o function.o

Analyzer: $(OBJ)
	@$(CC) $(OBJ) -o expr_analyzer $(CFLAGS)
	@echo "\tCC $<"

main.o: main.cpp calculator.h
	@$(CC) -c main.cpp
	@echo "\tCC $<"

calculator.o: calculator.cpp token.h tokenstream.h defs.h function.h
	@$(CC) -c calculator.cpp
	@echo "\tCC $<"

token.o: token.cpp token.h defs.h function.h
	@$(CC) -c token.cpp
	@echo "\tCC $<"

tokenstream.o: tokenstream.cpp token.h defs.h function.h
	@$(CC) -c tokenstream.cpp
	@echo "\tCC $<"

function.o: function.cpp function.h
	@$(CC) -c function.cpp
	@echo "\tCC $<"

clean:
	rm $(OBJ) expr_analyzer
	@if [ -f '.history' ]; then rm .history; fi
