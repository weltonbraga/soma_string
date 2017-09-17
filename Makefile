CXX=g++

EXENAME=testa_soma_string_stdin

MYLIB=string_soma

IDIR=inc

CFLAGS=-I$(IDIR) --coverage -g -Wall -ftest-coverage -fprofile-arcs -std=gnu++11

ODIR=obj

OBJS=$(ODIR)/$(EXENAME).o $(ODIR)/$(MYLIB).o 

DEPS=$(IDIR)/$(MYLIB).hpp

SDIR=src

TFLAGS= -lgtest -lgtest_main -pthread -I$(IDIR) -g -Wall -ftest-coverage -fprofile-arcs -std=gnu++11

TDIR=test

TEXENAME=testa_string_soma

TSRC=$(TEXENAME).cpp

TOBJS=$(ODIR)/$(MYLIB).o $(ODIR)/$(TEXENAME).o

DEBUG=0

CFLAGS += -DDEBUG=${DEBUG}

all : test main

main : $(ODIR)/$(EXENAME)

$(ODIR)/%.o : $(SDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)
	
$(ODIR)/$(EXENAME) : $(OBJS) $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)
	@echo " ###  check código ### "
	cppcheck --enable=warning $(SDIR)

test : $(ODIR)/$(TEXENAME)

$(ODIR)/$(TEXENAME).o : $(TDIR)/$(TEXENAME).cpp $(DEPS)
	$(CXX) -c -o $@ $< $(TFLAGS)

$(ODIR)/$(TEXENAME) : $(TOBJS) $(DEPS)
	$(CXX) -o $@ $^ $(TFLAGS)
	@echo " ### check testes ### "
	cppcheck --enable=warning $(TDIR)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~





	



	