all:chat.exe chatserver.exe
chat.exe: chat.c 
	g++ chat.c -o chat.exe  `pkg-config --cflags --libs gtk+-3.0 libglade-2.0` -lpthread
chatserver.exe:server.c
	g++ server.c -o chatserver.exe  `pkg-config --cflags --libs gtk+-3.0 libglade-2.0` -lpthread
clean: 
	rm -f *.o outFile
