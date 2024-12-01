CXX = g++
CXXFLAGS = -std=c++11 -Wall

TARGET = BufferedFileApp

# 源文件
SOURCES = CLBufferedFile.cpp CLLRUCache.cpp main.cpp

# 目标文件
OBJECTS = $(SOURCES:.cpp=.o)

# 默认目标
all: $(TARGET)

# 编译主程序
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# 编译 .cpp 文件为 .o 文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理中间文件和可执行文件
clean:
	rm -f $(TARGET) $(OBJECTS)


