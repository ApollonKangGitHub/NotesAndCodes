.PHONY:all
all:server client
server:server.c
	gcc -o $@ $^ -D_FUN3_ -lpthread
client:client.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -rf client server
