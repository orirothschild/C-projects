DEBUG_FLAGS = -ansi -pedantic-errors -Wall -Wextra -g
DNDEBUG_FLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
CFLAGS = $(DEBUG_FLAGS)
cc = gcc

obj_dir = obj
src_dir = src
lib_dir = ../lib
tests_dir = tests
headers_dir = /home/student/hadar-klein/include
src_dir_link = $$(pwd)/src


sources := $(filter-out %_test.c, $(wildcard $(src_dir)/*.c))
tests := $(wildcard $(src_dir)/*_test.c)

headers := $(subst .c,.h, $(subst $(src_dir),$(headers_dir), $(sources)))
objects := $(subst .c,.o, $(subst $(src_dir),$(obj_dir), $(sources)))
depends := $(subst .o,.d, $(subst $(obj_dir)/,, $(objects)))
library := $(addprefix $(lib_dir)/,libds.ar)
testout := $(subst _test.c,.t, $(subst $(src_dir)/,, $(tests)))
executebles := $(subst _test.c,.out, $(subst $(src_dir)/,, $(tests)))

VPATH = src:obj:include:lib:tests

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
$(tests_dir) :
	-mkdir $(tests_dir)

.PHONY : clean
clean :
	-rm -f $(objects)
	-rm -f $(headers)
	-rm -f $(library)
	-rm -f $(tests_dir)/*.out
	-rm -f $(testout)
	-rm -f $(depends)
	-rmdir $(obj_dir)
	-rmdir $(headers_dir)
	-rmdir $(lib_dir)
	-rmdir $(tests_dir)

.PHONY : test
test : $(executebles)

-include $(testout)

%.t : $(src_dir)/%_test.c | $(tests_dir)
	echo "$(@:.t=.out) : $< $(library)" > $@
	echo '	$$(cc) $$(CFLAGS) -o $(tests_dir)/$(@:.t=.out) $< $(library)' >> $@ 

.PHONY : debug
debug :
	echo $(headers)
