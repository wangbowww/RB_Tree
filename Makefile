# 编译器
CC = g++
# 编译器标志
CFLAGS = -MMD -MP -c -Isrc/h -Wall -O2 -lws2_32
LFLAGE = -Wall -lws2_32
# 源文件目录
SRC_DIR = src/cpp
# 对象文件目录
OBJ_DIR = build
# 目标文件文件夹
BIN_DIR = bin

# 可执行文件名称
TARGET_SRC = $(wildcard $(SRC_DIR)/main/*.cpp)
TARGET = $(TARGET_SRC:$(SRC_DIR)/main/%.cpp=$(BIN_DIR)/%.exe)
TARGET_OBJ = $(TARGET_SRC:$(SRC_DIR)/main/%.cpp=$(OBJ_DIR)/main/%.o)

# 找到所有的 .cpp 文件
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# 将 .cpp 文件的列表转换为 .o 文件的列表
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
# 每个.o文件的依赖表文件
DEPS = $(OBJECTS:.o=.d) $(TARGET_OBJ:.o=.d)


# 默认目标
all: print dirs $(TARGET) 

print:

# 创建文件夹目标
dirs:
	if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	if not exist "$(OBJ_DIR)/main" mkdir "$(OBJ_DIR)/main"

# 链接目标
$(BIN_DIR)/%.exe: $(OBJECTS) $(OBJ_DIR)/main/%.o
	$(CC) $^ -o $@ $(LFLAGE)

# 从 .cpp 生成 .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $< -o $@ $(CFLAGS)
$(OBJ_DIR)/main/%.o: $(SRC_DIR)/main/%.cpp
	$(CC) $< -o $@ $(CFLAGS)

-include $(DEPS)

# 清理目标
clean:
	del /Q $(BIN_DIR)\*.exe
	del /Q $(OBJ_DIR)\*.o
	del /Q $(OBJ_DIR)\*.d
	rmdir /s /q $(OBJ_DIR)
.PHONY: all clean dirs
