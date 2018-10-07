CC=gcc
FLAGS=-Wall
EXE=tema3
EXEv=tema3.g

build: $(EXE)

buildv: $(EXEv)

$(EXE): main.o functii.o trie.o
	$(CC) $(FLAGS) $^ -o $(EXE)
$(EXEv): main.c functii.c trie.c 
	$(CC) $(FLAGS) -g $^ -o $(EXEv)
main.o: main.c
	$(CC) $(FLAGS) -c $< -o $@
functii.o: functii.c
	$(CC) $(FLAGS) -c $< -o $@
trie.o: trie.c
	$(CC) $(FLAGS) -c $< -o $@

main.c: functii.h trie.h

functii.c: functii.h trie.h

trie.c : functii.h trie.h

.PHONY: clean

clean:
	rm -f *.o $(EXE) $(EXEv)