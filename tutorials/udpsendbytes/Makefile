CXX=g++
RM=rm -f
INCLUDES=-I/usr/include/opendavinci
CPPFLAGS=-Wall $(INCLUDES)
LDLIBS=-lopendavinci -lpthread

BIN=udpsendbytes
SRCS=UDPSendBytes.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) -o $(BIN) $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) $(BIN)
	$(RM) *~ .depend

include .depend
