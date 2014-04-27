
CFLAGS= -Wall -O1 -pg

all: t1 t2
	echo "Good" | ./t1
	./t2

t1: t1.o
	gcc $(CFLAGS) -o t1 t1.o  
t2: t2.o
	gcc $(CFLAGS) -o t2 t2.o  

clean:
	rm -f t1 t2 t1.o t2.o
