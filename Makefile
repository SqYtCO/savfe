.PHONY: all clean

CXX := g++
CXXFLAGS := -m64 -Wall -std=c++17 -O3
LIBS := -lstdc++fs -pthread
CPPFILES := $(wildcard *.cpp) $(wildcard exceptions/*.cpp)
HEADERS := $(wildcard *.h) $(wildcard exceptions/*.h)
OBJFILES := $(patsubst %.cpp,%.o,$(CPPFILES))
OUTPUT := savfe


all: $(OUTPUT)

$(OUTPUT): $(OBJFILES)
	$(CXX) -o $@ $^ $(LIBS)

%.o: %.cpp $(HEADERS)
	$(CXX) -c $(CXXFLAGS) $<

clean:
	rm -f $(OBJFILES) $(OUTPUT)
