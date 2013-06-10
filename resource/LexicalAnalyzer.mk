CXX = g++ -std=gnu++0x
CXXFLAGS = -Wall -g -D LEXICALANALYZER_UNIT_TEST
INCLUDES = 
LIBS = -lboost_regex
OBJS = LexicalAnalyzer.o
PROGRAM = LexicalAnalyzer.out

all:$(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(INCLUDES) $(LIBS) -o $(PROGRAM)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS) -c $<

.PHONY: clean
clean:
	rm -f *o $(PROGRAM)
