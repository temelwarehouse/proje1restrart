default: server
	./server

server: server.cpp
	g++ -std=c++17 -o server server.cpp  
redis-server:
	gnome-terminal -- bash -c "redis-7.0.11/src/redis-server; exec bash"
	gnome-terminal -- bash -c "redis-7.0.11/src/redis-cli; exec bash"
