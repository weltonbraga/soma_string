CXX=g++

TARGET=testa_soma_string_stdin

IDIR=inc

CFLAGS=-I$(IDIR) --coverage -g -Wall -ftest-coverage -fprofile-arcs

ODIR=obj

OBJS=$(ODIR)/testa_string_soma.o $(ODIR)/string_soma.o 

DEPS=$(IDIR)/string_soma.hpp

SDIR=src

TFLAGS= -lgtest -lgtest_main -pthread -I$(IDIR) -g -Wall -ftest-coverage -fprofile-arcs

TDIR=test

TSRC=primeiroTeste.cpp

TOBJS=$(ODIR)/string_soma.o $(ODIR)/primeiroTeste.o

TTARGET=run_tests

all: $(TTARGET) $(TARGET)

$(ODIR)/%.o : $(SDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)
	
$(TARGET) : $(OBJS) $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)
	@echo " ###  Build ok ### "
	cppcheck --enable=warning $(SDIR)

test: $(TTARGET)

$(ODIR)/primeiroTeste.o: $(TDIR)/primeiroTeste.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(TFLAGS)

$(TTARGET) : $(TOBJS) $(DEPS)
	$(CXX) -o $@ $^ $(TFLAGS)
	@echo " ###  Gtest ok ### "
	
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~





	



	