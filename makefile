#/*****************************************
# * Author: Eve Leonard 3148599
# * Lab instructor: Dhara Wagh 
# * Lecture instructor: Abdullah Mohiuddin
#*****************************************/

CC=gcc
CFLAGS= -Wall -g -std=c99

dashboard: dashboard.o DB.o DB_impl.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm *.o

tar:
	tar -zcvf cmpt201_eehmm_milestone1.tar.gz DB.h DB.c DB_impl.h DB_impl.c dashboard.c makefile README.md CMPT201_A3_DashboardPlanning.pdf
