CXX=g++
RM=rm -f
INCLUDES=-I/usr/include/opendavinci
CPPFLAGS=-Wall $(INCLUDES)
LDLIBS=-lopendavinci -lpthread

BINA=ipcsharedmemoryconsumer
SRCSA=ipcsharedmemoryconsumer.cpp
OBJSA=$(subst .cpp,.o,$(SRCSA))

BINB=ipcsharedmemoryproducer
SRCSB=ipcsharedmemoryproducer.cpp
OBJSB=$(subst .cpp,.o,$(SRCSB))

all: $(BINA) $(BINB)

$(BINA): $(OBJSA)
	$(CXX) -o $(BINA) $(OBJSA) $(LDLIBS) 

$(BINB): $(OBJSB)
	$(CXX) -o $(BINB) $(OBJSB) $(LDLIBS) 

depend: .dependA .dependB

.dependA: $(SRCSA)
	rm -f ./.dependA
	$(CXX) $(CPPFLAGS) -MM $^>>./.dependA;

.dependB: $(SRCSB)
	rm -f ./.dependB
	$(CXX) $(CPPFLAGS) -MM $^>>./.dependB;

clean:
	$(RM) $(OBJSA)
	$(RM) $(OBJSB)

dist-clean: clean
	$(RM) $(BINA)
	$(RM) $(BINB)
	$(RM) *~ .dependA .dependB

include .dependA
include .dependB
