TARGET = dijkstra

SRCS = Main.cpp Vertex.cpp Edge.cpp 

CXX = g++

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) -o $(TARGET) $(SRCS)

clean: 
	rm -f $(TARGET)
