CXX = g++ -std=gnu++0x
CXXFLAGS = -Wall -g -D TOKENTYPE_UNIT_TEST
INCLUDES = 
LIBS =
OBJS = TokenType.o
PROGRAM = TokenType.out

all:$(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(INCLUDES) $(LIBS) -o $(PROGRAM)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS) -c $<

.PHONY: clean
clean:
	rm -f *o $(PROGRAM)
