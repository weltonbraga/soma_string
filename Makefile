CC = %compilador%\gcc
IDIR = inc
CFLAGS = -I$(IDIR)
ODIR = obj
SDIR = src
TARGET = testa_soma_string_stdin

DEPS = $(IDIR)\string_soma.hpp


OBJ =  obj\string_soma.o  obj\\testa_string_soma.o 


obj\%.o: src\%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): obj
	gcc -o $@ $^ $(CFLAGS)
