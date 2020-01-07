#RC4#
DEBUG_FLAGS = -ansi -pedantic-errors -Wall -Wextra -g
DNDEBUG_FLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
CFLAGS = $(DEBUG_FLAGS)
cc = gcc

#include ../Makefile
obj_dir = obj
src_dir = src
lib_dir = ../lib

headers_dir = /home/student/hadar-klein/projects/include
src_dir_link = $$(pwd)/src

sources := $(filter-out %_test.c, $(wildcard $(src_dir)/*.c))
headers := $(subst .c,.h, $(subst $(src_dir),$(headers_dir), $(sources))) utils.h
objects := $(subst .c,.o, $(subst $(src_dir),$(obj_dir), $(sources)))
depends := $(subst .o,.d, $(subst $(obj_dir)/,, $(objects)))
library := $(addprefix $(lib_dir)/,libscheduler.ar)
tests := $(addprefix $(src_dir)/,schd_test.c)

VPATH = src:obj:include:lib


all : $(library) symlinks

# create the library files and place in the lib folder
$(library) : $(objects) | $(lib_dir)
	ar -cr $@ $(objects)

-include $(depends)

%.d : $(src_dir)/%.c | $(obj_dir)
	$(cc) $(CFLAGS) -MM -MT $(obj_dir)/$(@:.d=.o) $< > $@
	echo "	$(cc) $(CFLAGS) -c -o $(obj_dir)/$(@:.d=.o) $<" >> $@ 

# Create the symlinks and place in the headers folder
symlinks : $(headers)

%.h : | $(headers_dir)
	-ln -s $(subst $(headers_dir), $(src_dir_link), $@) $@

$(obj_dir) :
	-mkdir $(obj_dir)
$(lib_dir) :
	-mkdir $(lib_dir)
$(headers_dir) :
	-mkdir $(headers_dir)
$(dep_dir) :
	-mkdir $(dep_dir)


.PHONY : clean test debug

clean :
	-rm -f $(objects)
	-rm -f $(headers)
	-rm -f $(library)
	-rm -f test.out
	-rm -f $(depends)
	-rmdir $(obj_dir)
	-rmdir $(headers_dir)
	-rmdir $(lib_dir)
	-rmdir $(dep_dir)

test : $(library)
	$(cc) $(CFLAGS) -o test.out $(tests) $^

debug :
	echo $(objects)