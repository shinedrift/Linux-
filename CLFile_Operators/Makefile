CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = BufferedFileApp
SOURCES = CLBufferedFile.cpp CLLRUCache.cpp main.cpp

# 测试目标
TEST_TARGET = TestLRUCache
TEST_SOURCES = LRUCache_test.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# 编译测试
$(TEST_TARGET): $(TEST_SOURCES) 
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SOURCES)

clean:
	rm -f $(TARGET) $(TEST_TARGET)
