all: CatchemEggV8 clean

CatchemEggV8: main.o init.o game.o game2.o classement.o
	gcc -W -Wall -std=c89 -pedantic -O3 `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` main.o init.o game.o game2.o classement.o `pkg-config --libs-only-l MLV` -o CatchemEggV8

main.o: main.c init.h
	gcc -W -Wall -std=c89 -pedantic -O3 `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` -c main.c `pkg-config --libs-only-l MLV` -o main.o

game.o: game.c game.h
	gcc -W -Wall -std=c89 -pedantic -O3 `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` -c game.c `pkg-config --libs-only-l MLV` -o game.o

init.o: init.c init.h game.h classement.h
	gcc -W -Wall -std=c89 -pedantic -O3 `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` -c init.c `pkg-config --libs-only-l MLV` -o init.o

game2.o: game2.c game.h
	gcc -W -Wall -std=c89 -pedantic -O3 `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` -c game2.c `pkg-config --libs-only-l MLV` -o game2.o

classement.o: classement.c classement.h
	gcc -W -Wall -std=c89 -pedantic -O3 `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` -c classement.c `pkg-config --libs-only-l MLV` -o classement.o

clean:
	rm -f *.o *~

