MODE = pi
ifeq ($(MODE), pi)
CC = arm-linux-gnueabihf-g++
CFLAGS = -std=c++11 -pedantic-errors -Wall -Wextra -g -I../../include -I/home/student/boost_1_62_0
LFLAGS = -lboost_system -L/home/student/boost_1_62_0/stage/lib -L/home/student/hadar-klein/cpp/project/bin -Wl,-rpath=/home/pi/bin -Wall -llogger 
else
CC = g++
CFLAGS = -std=c++11 -pedantic-errors -Wall -Wextra -g -I../../include
LFLAGS = -lboost_system
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
SHARED_OBJ = $(addprefix $(SHARED_OBJ_DIR)/,liblogger.so)
target = $(OBJ) $(SHARED_OBJ)

all : $(target)

-include $(DEP)

%.d : %.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MM $< -MT $(subst .cpp,.o,$(subst $(SRC_DIR),$(OBJ_DIR),$^)) > $@
	echo "	$(CC) $(CFLAGS) -c -fPIC -o $(subst .cpp,.o,$(subst $(SRC_DIR),$(OBJ_DIR),$^)) $<" >> $@

$(SHARED_OBJ) : $(OBJ)
	$(CC) $(CFLAGC) -shared -o $(addprefix $(shell cd ../../bin; pwd)/,liblogger.so) $(OBJ)

$(OBJ_DIR) :
	-mkdir $(OBJ_DIR)
$(TEST_DIR) :
	-mkdir $(TEST_DIR)

.PHONY : clean test
clean :
	-rm -f $(OBJ)
	-rm -f $(SHARED_OBJ)
	-rm -f $(TEST_FAKE)
	-rm -f $(DEP)
	-rm -f $(EXE)
	-rmdir $(TEST_DIR)

test : $(EXE) 

-include $(TEST_FAKE)

%.f : %.cpp |  $(TEST_DIR) $(SHARED_OBJ)
	echo "$(subst .cpp,.out,$(subst $(SRC_DIR),$(TEST_DIR),$^)) : $(subst $(TEST_DIR),$(SRC_DIR),$^) $(OBJ)" > $@
ifeq ($(MODE), pi)
	echo "	$(CC) $(CFLAGS) -o $(subst .cpp,.out,$(subst $(SRC_DIR),$(TEST_DIR),$^)) $^ $(LFLAGS)" >> $@
else
	echo "	$(CC) $(CFLAGS) -o $(subst .cpp,.out,$(subst $(SRC_DIR),$(TEST_DIR),$^)) $^ $(SHARED_OBJ) $(LFLAGS)" >> $@
endif