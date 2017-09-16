CXX=g++

TARGET=t

IDIR=inc

CFLAGS=-I$(IDIR) -Wall

ODIR=obj
OBJS=$(ODIR)/testa_string_soma.o $(ODIR)/string_soma.o 

DEPS=$(IDIR)/string_soma.hpp

SDIR=src

all : $(TARGET)

$(ODIR)/%.o : $(SDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)
	
$(TARGET) : $(OBJS) $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~





	



	