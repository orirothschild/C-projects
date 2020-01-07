CC = gcc -ansi -pedantic-errors -Wall -Wextra -g

.PHONY : clean
clean:
	rm -f *.out

.PHONY: tcp
tcp:
	$(CC) tcp_server.c -o tcp_server.out
	$(CC) tcp_client.c -o tcp_client.out

.PHONY: udp
udp:
	$(CC) udp_server.c -o udp_server.out
	$(CC) udp_client.c -o udp_client.out
	
.PHONY: broadcast
broadcast:
	$(CC) broadcast_server.c -o broadcast_server.out
	$(CC) broadcast_client.c -o broadcast_client.out

test_tcp_server :
	./tcp_server.out

test_tcp_clien :
	./tcp_client.out

test_udp_server :
	./udp_server.out

test_udp_client :
	./udp_client.out

test_broadcast_server :
	./broadcast_server.out

test_broadcast_client :
	./broadcast_client.out