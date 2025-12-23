<<<<<<< HEAD
CC=g++
CFLAGS=-std=c++17 -pedantic -g -Wall -Wextra -Wno-unused-variable
EXECUTABLE=solution
SRC=main.cpp trie.cpp
OBJ=$(SRC:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

trie.cpp: trie.hpp

main.o: trie.hpp

clean:
=======
CC=g++
CFLAGS=-std=c++17 -pedantic -g -Wall -Wextra -Wno-unused-variable
EXECUTABLE=solution
SRC=main.cpp trie.cpp
OBJ=$(SRC:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

trie.cpp: trie.hpp

main.o: trie.hpp

clean:
>>>>>>> 017b9db (8 9 fiished)
	rm -f *.o $(EXECUTABLE)