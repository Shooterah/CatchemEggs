
CatchemEggV3: main.o init.o game.o
	gcc -W -Wall -std=c89 -pedantic -O3 `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` main.o init.o game.o `pkg-config --libs-only-l MLV` -o CatchemEggV3

main.o: main.c init.h
	gcc -W -Wall -std=c89 -pedantic -O3 `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` -c main.c `pkg-config --libs-only-l MLV` -o main.o

game.o: game.c game.h
	gcc -W -Wall -std=c89 -pedantic -O3 `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` -c game.c `pkg-config --libs-only-l MLV` -o game.o

init.o: init.c init.h game.h
	gcc -W -Wall -std=c89 -pedantic -O3 `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` -c init.c `pkg-config --libs-only-l MLV` -o init.o

clean :
	rm -f CatchemEggV3 *.o

