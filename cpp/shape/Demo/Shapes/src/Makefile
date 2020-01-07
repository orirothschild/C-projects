CC = gcc -ansi -pedantic-errors -Wall -Wextra -g

.PHONY : clean
clean:
	rm -f *.out
	rm -f /tmp/fifo1
	rm -f /tmp/fifo2

.PHONY: fork
fork:
	$(CC) pipe_fork.c -o pipe_fork.out

.PHONY: namedpipe
namedpipe:
	$(CC) namedpipe_ping.c -o namedpipe_ping.out
	$(CC) namedpipe_pong.c -o namedpipe_pong.out

.PHONY: msgq
msgq:
	$(CC) msgq_p1.c -o msgq_p1.out
	$(CC) msgq_p2.c -o msgq_p2.out
	$(CC) msgq_p3.c -o msgq_p3.out
	$(CC) msgq_p4.c -o msgq_p4.out
	
.PHONY: sharedmem
sharedmem:
	$(CC) sharedm_p1.c -o sharedm_p1.out
	$(CC) sharedm_p2.c -o sharedm_p2.out
	$(CC) sharedm_p3.c -o sharedm_p3.out
	$(CC) sharedm_p4.c -o sharedm_p4.out


test_pipe_fork :
	./pipe_fork.out

test_named_pipe_ping :
	./namedpipe_ping.out

test_named_pipe_pong :
	./namedpipe_pong.out

test_msgq :
	./msgq_p1.out
	./msgq_p2.out
	./msgq_p3.out
	./msgq_p4.out

test_sharedmem :
	./sharedm_p1.out
	./sharedm_p2.out
	./sharedm_p3.out
	./sharedm_p4.out