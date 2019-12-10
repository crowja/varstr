#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "varstr.h"
#include "t/tinytest.h"

#ifdef  _COLOR_CODE
#undef  _COLOR_CODE
#endif
#define _COLOR_CODE       0x1B

#ifdef  _COLOR_RED
#undef  _COLOR_RED
#endif
#define _COLOR_RED        "[1;31m"

#ifdef  _COLOR_GREEN
#undef  _COLOR_GREEN
#endif
#define _COLOR_GREEN      "[1;32m"

#ifdef  _COLOR_YELLOW
#undef  _COLOR_YELLOW
#endif
#define _COLOR_YELLOW     "[1;33m"

#ifdef  _COLOR_RESET
#undef  _COLOR_RESET
#endif
#define _COLOR_RESET      "[0m"

static void
_printf_test_name(char *name, char *info)
{
   printf("%c%s%s%c%s", _COLOR_CODE, _COLOR_YELLOW, name, _COLOR_CODE, _COLOR_RESET);

   if (NULL != info)
      printf(" [%s]\n", info);
   else
      printf("\n");
}

static void
test_constr(void)
{
   struct varstr *z;

   _printf_test_name("test_constr()", NULL);

   z = varstr_new();
   ASSERT("Constructor test", z);
   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}

#if 0
static void
test_stub(void)
{
   struct varstr *z;

   _printf_test_name("test_stub()", NULL);

   z = varstr_new();
   ASSERT("... TEST STUB ...", z);
   varstr_free(&z);
   ASSERT_EQUALS(&z);
}
#endif

int
main(void)
{
   printf("%s\n", varstr_version());

   RUN(test_constr);

   return TEST_REPORT();
}
