MODE = pc
ifeq ($(MODE), pi)
CC = arm-linux-gnueabihf-g++
CFLAGS = -std=c++11 -pedantic-errors -Wall -Wextra -g -I../../../include -I../../ -I/home/student-02/boost_1_62_0
else
CC = g++
CFLAGS = -std=c++11 -pedantic-errors -Wall -Wextra -g -I../../../include -I../../
endif
SRC_DIR = $(shell pwd)
OBJ_DIR = ../../../bin
TEST_DIR = $(addprefix $(shell pwd)/,test)
SRC = $(filter-out %test.cpp ,$(wildcard $(SRC_DIR)/*.cpp))
OBJ = $(subst .cpp,.o,$(subst $(SRC_DIR),$(OBJ_DIR),$(SRC)))
DEP = $(subst .cpp,.d,$(SRC))
PLUGINS_DIR = ../../plugins
COMPRESSOR_DIR = ../../../framework/compressor
COMPRESSOR_OBJ = $(addprefix $(OBJ_DIR)/,compressor.o)
SHARED_OBJ = $(addprefix $(SRC_DIR)/,libwrite.so)
target = $(OBJ) $(SHARED_OBJ) $(COMPRESSOR_OBJ)

all : $(target)

-include $(DEP)

%.d : %.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MM $< -MT $(subst .cpp,.o,$(subst $(SRC_DIR),$(OBJ_DIR),$^)) > $@
	echo "	$(CC) $(CFLAGS) -c -fPIC -o $(subst .cpp,.o,$(subst $(SRC_DIR),$(OBJ_DIR),$^)) $<" >> $@

$(SHARED_OBJ) : $(OBJ) $(COMPRESSOR_OBJ)
	$(CC) $(CFLAGS) -shared -o $@ $^ -lz

$(COMPRESSOR_OBJ) :
	(cd $(COMPRESSOR_DIR); make MODE=$(MODE))

.PHONY : clean
clean :
	-rm -f $(OBJ)
	-rm -f $(TEST_FAKE)
	-rm -f $(DEP)
	-rm -f $(subst $(SRC_DIR),$(PLUGINS_DIR),$(SHARED_OBJ))
	(cd $(COMPRESSOR_DIR); make clean)