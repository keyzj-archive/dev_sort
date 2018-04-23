#//////////////////////////////////////////////////////////////////////////////////
#	Base make-variables: compiler, compile options, source-flag, sources directory,
#	bins directory and etc.
#//////////////////////////////////////////////////////////////////////////////////
CC = g++
CFLAGS = -Wall -Wextra -std=c++98
MAIN_ONLY_CFLAGS = -CC -P -undef -nostdinc -fdirectives-only -dDI -E
SOURCES = -c
SRC_DIR = src
BIN_DIR = bin
LIB_DIR = lib
OBJ_DIR = obj
UT_DIR = ut
PACK_DIR = pack
MAIN_DIR = main

OPENMP = openmp
TEST_LIB = boost_unit_test_framework

#//////////////////////////////////////////////////////////////////////////////////
#	Main
#
#//////////////////////////////////////////////////////////////////////////////////
MAIN = main

MAIN_SRC = $(wildcard $(SRC_DIR)/$(MAIN_DIR)/main.cpp)
MAIN_OBJ = $(MAIN_SRC:$(SRC_DIR)/$(MAIN_DIR)/%.cpp=$(OBJ_DIR)/%.o)
MAIN_DEP = $(MAIN_OBJ:%.o=%.d)

PROJECT_SRC = $(wildcard $(SRC_DIR)/*.cpp)
PROJECT_OBJ = $(PROJECT_SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
PROJECT_DEP = $(PROJECT_OBJ:%.o=%.d)

$(MAIN): $(BIN_DIR)/$(MAIN)
$(BIN_DIR)/$(MAIN): $(PROJECT_OBJ) $(MAIN_OBJ)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ -f$(OPENMP)

-include $(MAIN_DEP) $(PROJECT_DEP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(MAIN_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD $(SOURCES) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD $(SOURCES) $< -o $@

#//////////////////////////////////////////////////////////////////////////////////
#	Main only
#
#//////////////////////////////////////////////////////////////////////////////////
MAIN_ONLY = only

SORT_SRC = $(MAIN_SRC)
MAIN_ONLY_SRC = $(SORT_SRC:$(SRC_DIR)/$(MAIN_DIR)/%.cpp=$(PACK_DIR)/%.cpp)

$(MAIN_ONLY): pack $(BIN_DIR)/$(MAIN_ONLY)
$(BIN_DIR)/$(MAIN_ONLY):
	@mkdir -p $(@D)
	$(CC) $(MAIN_ONLY_SRC) -o $@ $(OMPFLAGS) -f$(OPENMP)

-include $(MAIN_DEP) $(PROJECT_DEP)

$(MAIN_ONLY_SRC): $(SORT_SRC)
	@mkdir -p $(@D)
	@set +e
	@$(CC) -D MAIN_ONLY $(MAIN_ONLY_CFLAGS) $? 1> $@ 2> /dev/null || true
	@set -e
	@sed -i '/#include \"/d' $@
	@sed -i '/#define /d' $@

#//////////////////////////////////////////////////////////////////////////////////
#	Unit tests
#
#//////////////////////////////////////////////////////////////////////////////////

UT_SRC = $(wildcard $(SRC_DIR)/$(UT_DIR)/*.cpp)
UT_OBJ = $(UT_SRC:$(SRC_DIR)/$(UT_DIR)/%.cpp=$(SRC_DIR)/%.o)
UT_DEP = $(UT_OBJ:%.o=%.d)
UT_BINS = $(UT_SRC:$(SRC_DIR)/$(UT_DIR)/%.cpp=$(BIN_DIR)/%)

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(UT_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD $(SOURCES) $< -o $@

-include $(PROJECT_DEP) $(UT_DEP)

$(BIN_DIR)/ut_%: $(OBJ_DIR)/ut_%.o $(PROJECT_OBJ)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ -l$(TEST_LIB)

#//////////////////////////////////////////////////////////////////////////////////
#	Fake targets
#
#//////////////////////////////////////////////////////////////////////////////////
.PHONY: clean
.PHONY: run
.PHONY: tests
.PHONY: pack

pack: rm_pack $(MAIN_ONLY_SRC)

rm_pack:
	@rm -f $(MAIN_ONLY_SRC)

run: $(MAIN)
	./$(BIN_DIR)/$<

run_only: $(MAIN_ONLY)
	./$(BIN_DIR)/$<

tests: $(UT_BINS)
	$(foreach test,$^,./$(test);)

clean:
	rm -f $(BIN_DIR)/*
	rm -f $(OBJ_DIR)/*.d
	rm -f $(OBJ_DIR)/*.o
	rm -f $(LIB_DIR)/*.a
	rm -f $(PACK_DIR)/*.cpp
