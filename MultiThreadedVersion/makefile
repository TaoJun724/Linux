.PHONY:all
all:client server

cc=g++

client:client.cc tcp_client.cc tcp_socket.hpp 
	$(cc) -o $@ -std=c++11 $^

server:server.cc tcp_server.cc tcp_socket.hpp 
	$(cc) -o $@ -std=c++11 $^

.PHONY:clean
clean:
	rm -f client server
