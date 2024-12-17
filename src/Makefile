CXX ?= clang++
CXXFLAGS := \
			-Og \
			-ldpp \
			-Wall \
			-Wextra \
			-std=c++11 \
			-Wno-unused-command-line-argument

CFMT ?= clang-format
OUT := ../decision-tracker
OUT_DIR := build

SRCS := $(wildcard ./*.cpp)
HPPS := $(wildcard ./*.hpp ./*.h)
OBJS := $(SRCS:./%.cpp=$(OUT_DIR)/%.o)

info:
	@echo "Building for Linux..."
$(OUT_DIR)/%.o: ./%.cpp 
	$(CXX) $(CXXFLAGS) $< -o $(CWD)$@ -c

MAKE_DIR := mkdir -p $(OUT_DIR)/
CXXFLAGS += \
			-fsanitize=address \
			-fsanitize=undefined

decision-tracker:
	$(MAKE) info
	$(MAKE_DIR)
	$(MAKE) compile

compile: $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(OUT)

format:
	$(CFMT) -i $(SRCS) $(HPPS) $(HS)

clean:
	rm -rf ./$(OUT_DIR) ./$(OUT)

.PHONY: info decision-tracker compile format clean
