#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "varstr.h"
#include "t/tinytest.h"
#include "t/tinyhelp.h"

static void
test_constr(void)
{
   struct varstr *z;

   fprintf_test_info(stdout, "test_constr", "varstr_new, varstr_free");

   z = varstr_new();
   ASSERT("Constructor test", z);
   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_cat_str(void)
{
   struct varstr *z = varstr_new();
   char      x[] = "Now is the time for all good hounds";

   fprintf_test_info(stdout, "test_cat_str", "varstr_cat, varstr_str");
   varstr_cat(z, x);
   ASSERT_STRING_EQUALS(x, varstr_str(z));
   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_cat_to_s_cat(void)
{
   struct varstr *z = varstr_new();
   char      x[] = "Now is the time for all good hounds";
   char      x2[] =
    "Now is the time for all good houndsNow is the time for all good hounds";
   char     *cp;

   fprintf_test_info(stdout, "test_cat_to_s_cat", "varstr_cat, var_to_s, varstr_str");
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
   char      x1[] = "Now is the time for all good hounds   \n\n";
   char      x2[] = "Now is the time for all good hounds";

   fprintf_test_info(stdout, "test_rtrim", "varstr_rtrim");
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
   char      x[] = "   \t\t \n\n\t                 \n\n";

   fprintf_test_info(stdout, "test_rtrim_empty", "varstr_rtrim");
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

   fprintf_test_info(stdout, "test_rtrim_null", "varstr_rtrim");
   varstr_rtrim(z);
   ASSERT_STRING_EQUALS("", varstr_str(z));
   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_ltrim(void)
{
   struct varstr *z = varstr_new();
   char      x1[] = "\t   \n Now is the time for all good hounds";
   char      x2[] = "Now is the time for all good hounds";

   fprintf_test_info(stdout, "test_ltrim", "varstr_ltrim");
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
   char      x[] = "   \t\t \n\n\t                 \n\n";

   fprintf_test_info(stdout, "test_ltrim_empty", "varstr_ltrim");
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

   fprintf_test_info(stdout, "test_ltrim_null", "varstr_ltrim");
   varstr_ltrim(z);
   ASSERT_STRING_EQUALS("", varstr_str(z));
   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_catc(void)
{
   struct varstr *z;
   char      x[] = " a b c defghij\n k lmnopq r s t u v w x y z . . .";
   int       i, len = sizeof(x);

   fprintf_test_info(stdout, "test_stub", "varstr_catc");

   z = varstr_new();
   for (i = 0; i < len; i++)
      varstr_catc(z, x[i]);
   ASSERT_STRING_EQUALS(x, varstr_str(z));
   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_compact(void)
{
   struct varstr *z;
   char      x1[] = "\f\vabc\t   def\r ghi\n\n\n jkl     ";
   char      x2[] = "abcdefghijkl";

   fprintf_test_info(stdout, "test_compact", "varstr_compact");
   z = varstr_new();
   varstr_cat(z, x1);
   varstr_compact(z);
   ASSERT_STRING_EQUALS(x2, varstr_str(z));
   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_compact_null(void)
{
   struct varstr *z;
   char      x[] = "";

   fprintf_test_info(stdout, "test_compact_null", "varstr_compact");
   z = varstr_new();
   varstr_compact(z);
   ASSERT_STRING_EQUALS(x, varstr_str(z));
   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_change_case(void)
{
   struct varstr *z;
   char      x1[] = "12345xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\t\n*";
   char      x2[] = "12345XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\t\n*";

   fprintf_test_info(stdout, "test_change_case", "varstr_tolower, varstr_toupper");
   z = varstr_new();
   varstr_cat(z, x1);
   varstr_toupper(z);
   ASSERT_STRING_EQUALS(x2, varstr_str(z));
   varstr_tolower(z);
   ASSERT_STRING_EQUALS(x1, varstr_str(z));
   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}

#if 0                                            /* 12yy */
static void
test_stub(void)
{
   struct varstr *z;

   fprintf_test_info(stdout, "test_stub", NULL);
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
   RUN(test_catc);
   RUN(test_compact);
   RUN(test_compact_null);
   RUN(test_change_case);

   return TEST_REPORT();
}
