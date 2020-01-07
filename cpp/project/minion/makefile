MODE = pc
ifeq ($(MODE), pi)
CC = arm-linux-gnueabihf-g++
CFLAGS = -std=c++11 -pedantic-errors -Wall -Wextra -g -I../../utils -I../include -I/home/student/boost_1_62_0
LFLAGS = -rdynamic -ldl -lboost_system -lboost_filesystem -L/home/student/boost_1_62_0/stage/lib -L/home/student/hadar-klein/cpp/project/bin -Wl,-rpath=/home/pi/bin -Wall -lreactor -llogger -lcompressor -ldirmonitor
LIBS = 
else
CC = g++
CFLAGS = -std=c++11 -pedantic-errors -Wall -Wextra -g -I../../utils -I../include 
LFLAGS = -rdynamic -ldl -lboost_system -lboost_filesystem
LIBS = 
endif
SRC_DIR = $(shell pwd)
OBJ_DIR = ../bin
TEST_DIR = $(addprefix $(shell pwd)/,test)
SRC = $(filter-out %test.cpp ,$(wildcard $(SRC_DIR)/*.cpp))
OBJ = $(subst .cpp,.o,$(subst $(SRC_DIR),$(OBJ_DIR),$(SRC)))
REACTOR_DIR = ../framework/reactor
LOGGER_DIR = ../framework/logger
DIR_MONITOR_DIR = ../framework/dirmonitor
DEP = $(subst .cpp,.d,$(SRC))
TEST = $(filter %test.cpp, $(wildcard $(SRC_DIR)/*.cpp))
TEST_FAKE = $(subst .cpp,.f,$(TEST)) 
EXE = $(subst .cpp,.out, $(subst $(SRC_DIR),$(TEST_DIR),$(TEST))) 
SHARED_OBJ_DIR = ../bin
LOGGER_SO = $(addprefix $(SHARED_OBJ_DIR)/,liblogger.so)
REACTOR_SO = $(addprefix $(SHARED_OBJ_DIR)/,libreactor.so)
DIR_MONITOR_SO = $(addprefix $(SHARED_OBJ_DIR)/,libdirmonitor.so) 
SO = $(LOGGER_SO) $(REACTOR_SO) $(DIR_MONITOR_SO)
target = $(OBJ) $(SO)

all : $(target)

-include $(DEP)

%.d : %.cpp | $(OBJ_DIR) $(SO)
	$(CC) $(CFLAGS) -MM $< -MT $(subst .cpp,.o,$(subst $(SRC_DIR),$(OBJ_DIR),$^)) > $@
	echo "	$(CC) $(CFLAGS) -c -fPIC -o $(subst .cpp,.o,$(subst $(SRC_DIR),$(OBJ_DIR),$^)) $<" >> $@

$(REACTOR_SO) :
	(cd $(REACTOR_DIR); make MODE=$(MODE))

$(LOGGER_SO) :
	(cd $(LOGGER_DIR); make MODE=$(MODE))

$(DIR_MONITOR_SO) :
	(cd $(DIR_MONITOR_DIR); make MODE=$(MODE))

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
	(cd $(REACTOR_DIR); make clean)
	(cd $(LOGGER_DIR); make clean)
	(cd $(DIR_MONITOR_DIR); make clean)

test : $(EXE) 

-include $(TEST_FAKE)

%.f : %.cpp | $(TEST_DIR) $(REACTOR_OBJ)
	echo "$(subst .cpp,.out,$(subst $(SRC_DIR),$(TEST_DIR),$^)) : $(subst $(TEST_DIR),$(SRC_DIR),$^) $(OBJ) $(SO)" > $@
ifeq ($(MODE), pi)
	echo "	$(CC) $(CFLAGS) -o $(subst .cpp,.out,$(subst $(SRC_DIR),$(TEST_DIR),$^)) $^ $(OBJ) $(LFLAGS) $(LIBS)" >> $@
else
	echo "	$(CC) $(CFLAGS) -o $(subst .cpp,.out,$(subst $(SRC_DIR),$(TEST_DIR),$^)) $^ $(OBJ) $(SO) $(LFLAGS) $(LIBS)" >> $@
endif