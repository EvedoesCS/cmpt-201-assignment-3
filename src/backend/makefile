#/*****************************************
# * Author: Eve Leonard 3148599
# * Lab instructor: Dhara Wagh 
# * Lecture instructor: Abdullah Mohiuddin
#*****************************************/

CC=gcc
CFLAGS= -Wall -g -std=c99
LDLIBS = -lm

test_import: testing/test_import.o import.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm *.o
