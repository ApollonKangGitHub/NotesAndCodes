.PHONY:all
all:server client
server:server.c
	gcc -o server server.c -lpthread
client:client.c
	gcc -o client client.c -lpthread

.PHONY:clean
clean:
	rm -rf server
	rm -rf client 
