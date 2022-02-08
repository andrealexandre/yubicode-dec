EXE=yubicode-dec

default: run

clean:
	rm -f $(EXE)

$(EXE):
	gcc -o $(EXE) main.c

compile: clean $(EXE)

run: clean $(EXE)
	./$(EXE)