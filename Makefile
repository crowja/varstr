SHELL = /bin/sh

GCC_STRICT_FLAGS = -pedantic -ansi -W -Wall -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -O2
CPPFLAGS = -I.
CFLAGS = $(GCC_STRICT_FLAGS)
LDFLAGS =
OTHER_SOURCE =
OTHER_INCLUDE =
INCLUDE_FLAGS =
LDFLAGS_EFENCE = -L/usr/local/lib -lefence $(LDFLAGS)

.PHONY: check vcheck indent stamp clean

TESTS = t/test01 t/test02 t/test03 t/test04 t/test
# TODO Convert tests to tinytest.h. Already started by stubbing in t/test.c,
# so move the existing tests into this framework. Varstr will likely be used
# heavily in other scraps, so test it heavily under Valgrind and Electric Fence.

varstr.o: varstr.c varstr.h
	$(CC) -c $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) -o $@ varstr.c

check: varstr.o
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i"; \
	  ( $(CC)    $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c varstr.o $(LDFLAGS) ) \
	  && ( t/a.out ); \
	done 

vcheck: varstr.o
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i"; \
	  ( $(CC) -g $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c varstr.o $(LDFLAGS) ) \
	  && ( valgrind t/a.out ); \
	done 

echeck: varstr.o
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i"; \
	  ( $(CC)    $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c varstr.o $(LDFLAGS_EFENCE) ) \
	  && (  LD_PRELOAD=libefence.so ./t/a.out ); \
	done 

indent: stamp
	@indent $(INDENT_FLAGS) varstr.c
	@indent $(INDENT_FLAGS) varstr.h
	@for i in $(TESTS); \
	do \
	  indent $(INDENT_FLAGS) $$i.c; \
	done 

stamp:
	@stamper.bash varstr.c
	@stamper.bash varstr.h

clean:
	@/bin/rm -f varstr.o *.o *~ *.BAK *.bak core.*
	@/bin/rm -f t/*.o t/*~ t/*.BAK t/*.bak t/core.* t/a.out

