SHELL = /bin/sh

GCC_STRICT_FLAGS = -pedantic -ansi -W -Wall -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -O2
GCC_SANITIZE_FLAGS = -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
CPPFLAGS = -I.
CFLAGS = $(GCC_STRICT_FLAGS)
LDFLAGS =
OTHER_SOURCE =
OTHER_INCLUDE =
INCLUDE_FLAGS =
LDFLAGS_EFENCE = -L/usr/local/lib -lefence $(LDFLAGS)
STAMPER = stamper

.PHONY: check vcheck scheck stress indent stamp clean

##TESTS = t/test01 t/test02 t/test03 t/test04 t/test
TESTS = t/test
STRESS = t/stress

# TODO Convert tests to tinytest.h. Already started by stubbing in t/test.c,
# so move the existing tests into this framework. Varstr will likely be used
# heavily in other scraps, so test it heavily under Valgrind and Electric Fence.

varstr.o: varstr.c varstr.h
	$(CC) -c $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) -o $@ varstr.c

check:
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i"; \
	  ( $(CC)    $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c varstr.c $(LDFLAGS) ) \
	  && ( t/a.out ); \
	done 

vcheck:
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i"; \
	  ( $(CC) -g $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c varstr.c $(LDFLAGS) ) \
	  && ( valgrind t/a.out ); \
	done 

scheck:
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i"; \
	  ( $(CC)    $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(GCC_SANITIZE_FLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c varstr.c $(LDFLAGS) ) \
	  && ( t/a.out ); \
	done 

echeck: 
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i"; \
	  ( $(CC)    $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c varstr.c $(LDFLAGS_EFENCE) ) \
	  && (  LD_PRELOAD=libefence.so ./t/a.out ); \
	done 

stress:
	@for i in $(STRESS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i"; \
	  ( $(CC)    $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c varstr.c $(LDFLAGS) ) \
	  && ( t/a.out ); \
	done 

indent:
	@indent $(INDENT_FLAGS) varstr.c
	@indent $(INDENT_FLAGS) varstr.h
	@for i in $(TESTS); \
	do \
	  indent $(INDENT_FLAGS) $$i.c; \
	done 
	@for i in $(STRESS); \
	do \
	  indent $(INDENT_FLAGS) $$i.c; \
	done 

stamp:
	@$(STAMPER) varstr.c
	@$(STAMPER) varstr.h

clean:
	@/bin/rm -f varstr.o *.o *~ *.BAK *.bak core.*
	@/bin/rm -f t/*.o t/*~ t/*.BAK t/*.bak t/core.* t/a.out

