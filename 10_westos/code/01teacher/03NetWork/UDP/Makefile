.PHONY:all
all:client server
server:server.c
	gcc -o $@ $^
client:client.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -rf client server

