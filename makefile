all : puzzle.c boardADT.h boardADT.c
	dcc -o puzzle puzzle.c boardADT.c

# all : puzzle
cc : puzzle.c boardADT.h boardADT.c
	cc -o puzzle puzzle.c boardADT.c