CXX=g++

EXENAME=testa_soma_string_stdin

MYLIB=string_soma

IDIR=inc

CFLAGS=-I$(IDIR) --coverage -g -Wall -ftest-coverage -fprofile-arcs -std=gnu++11

ODIR=obj

OBJS=$(ODIR)/$(EXENAME).o $(ODIR)/$(MYLIB).o 

DEPS=$(IDIR)/$(MYLIB).hpp

SDIR=src

TFLAGS= -I$(IDIR) -lgtest -lgtest_main -pthread -g -Wall -ftest-coverage -fprofile-arcs -std=gnu++11

TDIR=test

TEXENAME=testa_string_soma

TSRC=$(TEXENAME).cpp

TOBJS=$(ODIR)/$(MYLIB).o $(ODIR)/$(TEXENAME).o

DEBUG=0

CFLAGS += -DDEBUG=${DEBUG}

all : test main

main : $(EXENAME)

$(ODIR)/%.o : $(SDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)
	
$(EXENAME) : $(OBJS) $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)
	@echo " ###  check código ### "
	cppcheck --enable=warning $(SDIR)

test : $(TEXENAME)

$(ODIR)/$(TEXENAME).o : $(TDIR)/$(TEXENAME).cpp $(DEPS)
	$(CXX) -c -o $@ $< $(TFLAGS)

$(TEXENAME) : $(TOBJS) $(DEPS)
	$(CXX) -o $@ $^ $(TFLAGS)
	@echo " ### check testes ### "
	cppcheck --enable=warning $(TDIR)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~





	



	