CC=g++
CXXFLAGS=-I. -Wall -pedantic -O2 -std=c++11
LDFLAGS=-lboost_system -lpthread
LDFLAGS2=-lmysqlclient
LDFLAGS3=-lboost_thread
LDFLAGS4=-ldht22

all: app

app: log.o sender.o configs.o tcpsocket.o app.o main.o
	$(CC) log.o configs.o sender.o tcpsocket.o app.o main.o -o mzclient $(CXXFLAGS) $(LDFLAGS) $(LDFLAGS2) $(LDFLAGS3) $(LDFLAGS4)

log.o: log.cpp
	$(CC) log.cpp -c $(CXXFLAGS)

configs.o: configs.cpp
	$(CC) configs.cpp -c $(CXXFLAGS)

sender.o: sender.cpp
	$(CC) sender.cpp -c $(CXXFLAGS) $(LDFLAGS4)

tcpsocket.o: tcpsocket.cpp
	$(CC) tcpsocket.cpp -c $(CXXFLAGS) $(LDFLAGS)

app.o: app.cpp
	$(CC) app.cpp -c $(CXXFLAGS)

main.o: main.cpp
	$(CC) main.cpp -c $(CXXFLAGS)

clean:
	-rm *.o
	-rm mzclient

install:
	-mkdir /usr/share/meteo
	cp mzclient /usr/share/meteo/
	cp meteo.cfg /etc/

remove:
	rm -rf /usr/share/meteo
	rm /etc/meteo.cfg
