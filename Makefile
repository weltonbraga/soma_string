CXX=g++

EXENAME=testa_soma_string_stdin

MYLIB=string_soma

IDIR=inc

CFLAGS=-I$(IDIR) --coverage -g -Wall -ftest-coverage -fprofile-arcs

ODIR=obj

OBJS=$(ODIR)/$(EXENAME).o $(ODIR)/$(MYLIB).o 

DEPS=$(IDIR)/$(MYLIB).hpp

SDIR=src

TFLAGS= -lgtest -lgtest_main -pthread -I$(IDIR) -g -Wall -ftest-coverage -fprofile-arcs

TDIR=test

TEXENAME=testa_string_soma

TSRC=$(TEXENAME).cpp

TOBJS=$(ODIR)/$(MYLIB).o $(ODIR)/$(TEXENAME).o

all: $(TEXENAME) $(EXENAME)

$(ODIR)/%.o : $(SDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)
	
$(EXENAME) : $(OBJS) $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)
	@echo " ###  Build ok ### "
	cppcheck --enable=warning $(SDIR)

test: $(TEXENAME)

$(ODIR)/$(TEXENAME).o: $(TDIR)/$(TEXENAME).cpp $(DEPS)
	$(CXX) -c -o $@ $< $(TFLAGS)

$(TEXENAME) : $(TOBJS) $(DEPS)
	$(CXX) -o $@ $^ $(TFLAGS)
	@echo " ###  Gtest ok ### "
	
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~





	



	