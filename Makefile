all: folders server client

server : bin/monitor

client: bin/tracer


folders:
	@mkdir -p src obj bin tmp

bin/monitor: obj/monitor.o
	gcc -g obj/monitor.o -o bin/monitor

obj/monitor.o: monitor.c
	gcc -Wall -g -c monitor.c -o obj/monitor.o

bin/tracer: obj/tracer.o
	gcc -g obj/tracer.o -o bin/tracer

-o obj/tracer.o: tracer.c
	gcc -Wall -g -c tracer.c -o obj/tracer.o

clean:
	rm -f obj/* tmp/*bin/{tracer,monitor}
