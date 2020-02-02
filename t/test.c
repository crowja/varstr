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

   _printf_test_name("test_constr", "varstr_new, varstr_free");

   z = varstr_new();
   ASSERT("Constructor test", z);
   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_cat_str(void)
{
   struct varstr *z = varstr_new();
   char        x[] = "Now is the time for all good hounds";

   _printf_test_name("test_cat_str", "varstr_cat, varstr_str");

   varstr_cat(z, x);
   ASSERT_STRING_EQUALS(x, varstr_str(z));

   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_cat_to_s_cat(void)
{
   struct varstr *z = varstr_new();
   char        x[] = "Now is the time for all good hounds";
   char        x2[] =
    "Now is the time for all good houndsNow is the time for all good hounds";
   char       *cp;

   _printf_test_name("test_cat_to_s_cat", "varstr_cat, var_to_s, varstr_str");

   varstr_cat(z, x);
   ASSERT_STRING_EQUALS(x, varstr_str(z));
   varstr_cat(z, cp = varstr_to_s(z));
   ASSERT_STRING_EQUALS(x2, varstr_str(z));
   free(cp);

   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_rtrim(void)
{
   struct varstr *z = varstr_new();
   char        x1[] = "Now is the time for all good hounds   \n\n";
   char        x2[] = "Now is the time for all good hounds";

   _printf_test_name("test_rtrim", "varstr_rtrim");

   varstr_cat(z, x1);
   ASSERT_STRING_EQUALS(x1, varstr_str(z));
   varstr_rtrim(z);
   ASSERT_STRING_EQUALS(x2, varstr_str(z));

   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_rtrim_empty(void)
{
   struct varstr *z = varstr_new();
   char        x[] = "   \t\t \n\n\t                 \n\n";

   _printf_test_name("test_rtrim_empty", "varstr_rtrim");

   varstr_cat(z, x);
   ASSERT_STRING_EQUALS(x, varstr_str(z));
   varstr_rtrim(z);
   ASSERT_STRING_EQUALS("", varstr_str(z));

   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_rtrim_null(void)
{
   struct varstr *z = varstr_new();

   _printf_test_name("test_rtrim_null", "varstr_rtrim");

   varstr_rtrim(z);
   ASSERT_STRING_EQUALS("", varstr_str(z));

   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_ltrim(void)
{
   struct varstr *z = varstr_new();
   char        x1[] = "\t   \n Now is the time for all good hounds";
   char        x2[] = "Now is the time for all good hounds";

   _printf_test_name("test_ltrim", "varstr_ltrim");

   varstr_cat(z, x1);
   ASSERT_STRING_EQUALS(x1, varstr_str(z));
   varstr_ltrim(z);
   ASSERT_STRING_EQUALS(x2, varstr_str(z));

   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}


static void
test_ltrim_empty(void)
{
   struct varstr *z = varstr_new();
   char        x[] = "   \t\t \n\n\t                 \n\n";

   _printf_test_name("test_ltrim_empty", "varstr_ltrim");

   varstr_cat(z, x);
   ASSERT_STRING_EQUALS(x, varstr_str(z));
   varstr_ltrim(z);
   ASSERT_STRING_EQUALS("", varstr_str(z));

   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_ltrim_null(void)
{
   struct varstr *z = varstr_new();

   _printf_test_name("test_ltrim_null", "varstr_ltrim");

   varstr_ltrim(z);
   ASSERT_STRING_EQUALS("", varstr_str(z));

   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}

#if 0                                            /* 12yy */
static void
test_stub(void)
{
   struct varstr *z;

   _printf_test_name("test_stub()", NULL);

   z = varstr_new();
   ASSERT("... TEST STUB ...", z);
   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}
#endif

int
main(void)
{
   printf("%s\n", varstr_version());

   RUN(test_constr);
   RUN(test_cat_str);
   RUN(test_cat_to_s_cat);
   RUN(test_rtrim);
   RUN(test_rtrim_empty);
   RUN(test_rtrim_null);
   RUN(test_ltrim);
   RUN(test_ltrim_empty);
   RUN(test_ltrim_null);

   return TEST_REPORT();
}
