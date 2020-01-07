MODE = pc
ifeq ($(MODE), pi)
CC = arm-linux-gnueabihf-g++
CFLAGS = -std=c++11 -pedantic-errors -Wall -Wextra -g -I../../include -I/home/student/boost_1_62_0
else
CC = g++
CFLAGS = -std=c++11 -pedantic-errors -Wall -Wextra -g -I../../include
endif
SRC_DIR = $(shell pwd)
OBJ_DIR = ../../bin
TEST_DIR = $(addprefix $(shell pwd)/,test)
SRC = $(filter-out %test.cpp,$(wildcard $(SRC_DIR)/*.cpp))
OBJ = $(subst .cpp,.o,$(subst $(SRC_DIR),$(OBJ_DIR),$(SRC)))
DEP = $(subst .cpp,.d,$(SRC))
TEST = $(filter %test.cpp, $(wildcard $(SRC_DIR)/*.cpp))
TEST_FAKE = $(subst .cpp,.f,$(TEST))
EXE = $(subst .cpp,.out, $(subst $(SRC_DIR),$(TEST_DIR),$(TEST)))
SHARED_OBJ_DIR = ../../bin
SHARED_OBJ = $(addprefix $(SHARED_OBJ_DIR)/,libcompressor.so)
target = $(OBJ) $(SHARED_OBJ)

all : $(target)

-include $(DEP)

%.d : %.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MM $< -MT $(subst .cpp,.o,$(subst $(SRC_DIR),$(OBJ_DIR),$^)) > $@
	echo "	$(CC) $(CFLAGS) -c -fPIC -o $(subst .cpp,.o,$(subst $(SRC_DIR),$(OBJ_DIR),$^)) $<" >> $@

$(SHARED_OBJ) : $(OBJ)
	$(CC) $(CFLAGS) -shared -o $@ $<

$(OBJ_DIR) :
	-mkdir $(OBJ_DIR)
$(TEST_DIR) :
	-mkdir $(TEST_DIR)

.PHONY : clean
clean :
	-rm -f $(OBJ)
	-rm -f $(SHARED_OBJ)
	-rm -f $(DEP)