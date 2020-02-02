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

#define _MAX_ITERATIONS 3000
#define _MAX_CHUNK_SIZE 50000
static void
test_build(void)
{
   struct varstr *z;
   char        buf[_MAX_CHUNK_SIZE];
   int         i;
   unsigned    total = 0;

   _printf_test_name("test_build", "varstr_cat, varstr_empty");

   z = varstr_new();
   ASSERT("Constructor test", z);

   for (i = 0; i < _MAX_ITERATIONS; i++) {
      double      u = rand() / RAND_MAX;
      if (u < 0.5) {                             /* tack on a random length string */
         int         j;
         int         len = rand() % _MAX_CHUNK_SIZE;
         for (j = 0; j < len; j++)
            buf[j] = 'a';
         buf[len] = '\0';
         total += len;
         varstr_cat(z, buf);
         ASSERT_EQUALS(total, strlen(varstr_str(z)));
      }
      else if (u < 0.9) {                        /* reset the varstr */
         varstr_cat(z, "");
      }
      else {
         varstr_empty(z);
         total = 0;
      }
   }

   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}

#undef _MAX_CHUNK_SIZE
#undef _MAX_ITERATIONS

#define _MAX_ITERATIONS 3000
#define _MAX_CHUNK_SIZE 5000000
static void
test_rtrimmer(void)
{
   struct varstr *z;
   char        buf[_MAX_CHUNK_SIZE];
   int         i;

   _printf_test_name("test_rtrimmer", "varstr_cat, varstr_empty, varstr_rtrim");

   z = varstr_new();
   ASSERT("Constructor test", z);

   for (i = 0; i < _MAX_ITERATIONS; i++) {
      int         j;
      int         right = rand() % 4;
      for (j = 0; j < 4; j++)
         buf[j] = 'a';
      for (j = right; j < 4; j++)
         buf[j] = ' ';
      buf[4] = '\0';

      varstr_empty(z);
      varstr_cat(z, buf);
      varstr_rtrim(z);
#if 0
      printf("DEBUG right %d strlen %d\n", strlen(varstr_str(z)), right);
#endif
      ASSERT_EQUALS((unsigned) right, strlen(varstr_str(z)));
   }

   for (i = 0; i < _MAX_ITERATIONS; i++) {
      int         j;
      /* int right = rand() % _MAX_CHUNK_SIZE; */
      int         right = rand() % (_MAX_CHUNK_SIZE - 1);
      for (j = 0; j < _MAX_CHUNK_SIZE; j++)
         buf[j] = 'a';
      for (j = right; j < _MAX_CHUNK_SIZE - 1; j++)
         buf[j] = ' ';
      buf[_MAX_CHUNK_SIZE - 1] = '\0';

      varstr_empty(z);
      varstr_cat(z, buf);
      varstr_rtrim(z);
#if 0
      printf("DEBUG right %d strlen %d\n", strlen(varstr_str(z)), right);
#endif
      ASSERT_EQUALS((unsigned) right, strlen(varstr_str(z)));
   }

   varstr_free(&z);
   ASSERT_EQUALS(NULL, z);
}

#undef _MAX_CHUNK_SIZE
#undef _MAX_ITERATIONS

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

   RUN(test_build);
   RUN(test_rtrimmer);

   return TEST_REPORT();
}
