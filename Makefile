CXXFLAGS := -std=c++20 -Wall -Wextra -I/home/marcin/lib/drogon/include -I/home/marcin/lib/json-schema-validator/include
CXX := g++

LDFLAGS := -L/home/marcin/lib/drogon/lib -L/home/marcin/lib/json-schema-validator/lib -Wl,-rpath,/home/marcin/lib/drogon/lib:/home/marcin/lib/json-schema-validator/lib -ldrogon -lnlohmann_json_schema_validator -ltrantor -ljsoncpp -pthread -luuid 
CXXFLAGS += $(LDFLAGS)

DEBUG ?= 0 

ifeq ($(DEBUG), 1)
CXXFLAGS += -g -O0
else
CXXFLAGS += -O3  
endif

# Directories
SRCDIR := src
BUILDDIR := bin

TESTDIR := tests
TEST_BINDIR := test_bin


# Find all source files recursively
# SRCS := $(shell find $(SRCDIR) -name '*.cc')
SRCS := $(wildcard $(SRCDIR)/*.cc) $(wildcard $(SRCDIR)/**/*.cc)

TEST_SRCS := $(wildcard $(TESTDIR)/*.cc) $(wildcard $(TESTDIR)/**/*.cc)

# Derive object file names from source files
OBJS := $(SRCS:$(SRCDIR)/%.cc=$(BUILDDIR)/%.o)

TEST_OBJS := $(TEST_SRCS:$(TESTDIR)/%.cc=$(TEST_BINDIR)/%.o)
# Derive dependency files from object files
DEPS := $(OBJS:.o=.d)

TEST_DEPS := $(TEST_OBJS:.o=.d)

# Targets
TARGET := $(BUILDDIR)/server.out
TEST_TARGETS := $(TEST_OBJS:.o=)

.PHONY: all clean info run test

all: $(TARGET)
# Linking
$(TARGET): $(OBJS)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@


# Compiling
$(BUILDDIR)/%.o: $(SRCDIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

#Build tests
# Additional targets
test: $(TEST_TARGETS)
	@for test_target in $(TEST_TARGETS); do \
        echo "Running $$test_target"; \
        ./$$test_target; \
	done
# Linking for tests
#
$(TEST_BINDIR)/%: $(TEST_BINDIR)/%.o $(filter-out $(BUILDDIR)/server.o,$(OBJS))
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -lgmock -lgtest -lgtest_main $^ -o $@

# Compiling for tests
$(TEST_BINDIR)/%.o: $(TESTDIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@


# Include dependency files
-include $(DEPS)
-include $(TEST_DEPS)

run: $(TARGET)
	@$(TARGET)


clean:
	@rm -r $(BUILDDIR)
	@rm -r $(TEST_BINDIR)


info:
	@echo "OBJS: $(OBJS)"
	@echo "SRCS: $(SRCS)"
	@echo "DEPS: $(DEPS)"
	@echo ""
	@echo "TESTSRCS: $(TEST_SRCS)"
	@echo "TEST_DEPS: $(TEST_DEPS)"
	@echo "TEST_OBJS: $(TEST_OBJS)"
	@echo "TEST_TARGETS: $(TEST_TARGETS)"
 
