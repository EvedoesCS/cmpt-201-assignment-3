CC = gcc
CFLAGS = -Wall -g -std=c99
HEADER = DB.h DB_impl.h

#dashboard: dashboard.o DB.o
#	$(CC) $(CFLAGS) dashboard.o DB.o -o dashboard

dashboard: dashboard.o
	$(CC) $(CFLAGS) dashboard.o -o dashboard


%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

valgrindDashBoard:
	valgrind --leak-check=full ./dashboard

clean:
	rm -f *.o dashboard

tar:
	tar -zcvf cmpt201_as_3_HL.tar.gz *.c *.h Makefile