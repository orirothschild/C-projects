CC = g++
CFLAGS = -std=c++98 -pedantic-errors -Wall -Wextra -g -I../../../utils -I../../include
LFLAGS = -lboost_chrono -lboost_system
SRC_DIR = $(shell pwd)
OBJ_DIR = ../../bin
TEST_DIR = $(addprefix $(shell pwd)/,test)
SRC = $(filter-out %test.cpp,$(wildcard $(SRC_DIR)/*.cpp))
OBJ = $(subst .cpp,.o,$(subst $(SRC_DIR),$(OBJ_DIR),$(SRC)))
REACTOR_DIR = ../reactor
REACTOR_OBJ = $(subst .cpp,.o,$(subst $(REACTOR_DIR),$(OBJ_DIR),$(filter-out %test.cpp,$(wildcard $(REACTOR_DIR)/*.cpp))))
LOGGER_DIR = ../logger
LOGGER_OBJ = $(subst .cpp,.o,$(subst $(LOGGER_DIR),$(OBJ_DIR),$(filter-out %test.cpp,$(wildcard $(LOGGER_DIR)/*.cpp))))
DEP = $(subst .cpp,.d,$(SRC))
TEST = $(filter %test.cpp, $(wildcard $(SRC_DIR)/*.cpp))
TEST_FAKE = $(subst .cpp,.f,$(TEST)) 
EXE = $(subst .cpp,.out, $(subst $(SRC_DIR),$(TEST_DIR),$(TEST))) 
SHARED_OBJ_DIR = ../../bin
SHARED_OBJ = $(addprefix $(SHARED_OBJ_DIR)/,libtimer.so)
LOGGER_SO = $(addprefix $(SHARED_OBJ_DIR)/,liblogger.so)
REACTOR_SO = $(addprefix $(SHARED_OBJ_DIR)/,libreactor.so)
target = $(OBJ) $(SHARED_OBJ)

all : $(target)

-include $(DEP)

%.d : %.cpp | $(OBJ_DIR) $(REACTOR_OBJ) $(LOGGER_OBJ)
	$(CC) $(CFLAGS) -MM $< -MT $(subst .cpp,.o,$(subst $(SRC_DIR),$(OBJ_DIR),$^)) > $@
	echo "	$(CC) $(CFLAGS) -c -fPIC -o $(subst .cpp,.o,$(subst $(SRC_DIR),$(OBJ_DIR),$^)) $<" >> $@

$(REACTOR_OBJ) :
	(cd $(REACTOR_DIR); make)

$(LOGGER_OBJ) :
	(cd $(LOGGER_DIR); make)

$(SHARED_OBJ) : $(OBJ)
	$(CC) $(CFLAGC) -shared -o $(addprefix $(shell cd ../../bin; pwd)/,libtimer.so) $(OBJ)

$(OBJ_DIR) :
	-mkdir $(OBJ_DIR)
$(TEST_DIR) :
	-mkdir $(TEST_DIR)

.PHONY : clean test
clean :
	-rm -f $(OBJ)
	-rm -f $(TEST_FAKE)
	-rm -f $(DEP)
	-rm -f $(EXE)
	-rmdir $(TEST_DIR)
	-rm -f $(SHARED_OBJ)
	(cd $(REACTOR_DIR); make clean)
	(cd $(LOGGER_DIR); make clean)

test : $(EXE) 

-include $(TEST_FAKE)

%.f : %.cpp |  $(TEST_DIR) $(SHARED_OBJ)
	echo "$(subst .cpp,.out,$(subst $(SRC_DIR),$(TEST_DIR),$^)) : $(subst $(TEST_DIR),$(SRC_DIR),$^) $(OBJ) $(REACTOR_OBJ) $(LOGGER_OBJ)" > $@
	echo "	$(CC) $(CFLAGS) -o $(subst .cpp,.out,$(subst $(SRC_DIR),$(TEST_DIR),$^)) $^ $(SHARED_OBJ) $(REACTOR_SO) $(LOGGER_SO) $(LFLAGS)" >> $@
