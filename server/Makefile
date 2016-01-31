CC=g++
CXXFLAGS=-I. -Wall -pedantic -O2 -std=c++14
LDFLAGS=-lboost_system -lpthread

all: app

app: log.o database.o configs.o server.o tcpsocket.o app.o main.o
	$(CC) log.o database.o configs.o server.o tcpsocket.o app.o main.o -o weathersrv $(CXXFLAGS) $(LDFLAGS)

log.o: log.cpp
	$(CC) log.cpp -c $(CXXFLAGS)

database.o: database.cpp
	$(CC) database.cpp -c $(CXXFLAGS)

configs.o: configs.cpp
	$(CC) configs.cpp -c $(CXXFLAGS)

server.o: server.cpp
	$(CC) server.cpp -c $(CXXFLAGS)

tcpsocket.o: tcpsocket.cpp
	$(CC) tcpsocket.cpp -c $(CXXFLAGS) $(LDFLAGS)

app.o: app.cpp
	$(CC) app.cpp -c $(CXXFLAGS)

main.o: main.cpp
	$(CC) main.cpp -c $(CXXFLAGS)

clean:
	-rm *.o
	-rm weathersrv
