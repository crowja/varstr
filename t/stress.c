#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "varstr.h"
#include "t/tinytest.h"
#include "t/tinyhelp.h"

#define MAX_ITERATIONS 3000
#define MAX_CHUNK_SIZE 50000

static void
test_build(void)
{
   struct varstr *z;
   char      buf[MAX_CHUNK_SIZE];
   int       i;
   unsigned  total = 0;

   fprintf_test_info(stdout, "test_build", "varstr_cat, varstr_empty");

   z = varstr_new();
   ASSERT("Constructor test", z);

   for (i = 0; i < MAX_ITERATIONS; i++) {
      double    u = rand() / RAND_MAX;
      if (u < 0.5) {                             /* tack on a random length string */
         int       j;
         int       len = rand() % MAX_CHUNK_SIZE;
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

#undef MAX_CHUNK_SIZE
#undef MAX_ITERATIONS

#define MAX_ITERATIONS 3000
#define MAX_CHUNK_SIZE 5000000

static void
test_rtrimmer(void)
{
   struct varstr *z;
   char      buf[MAX_CHUNK_SIZE];
   int       i;

   fprintf_test_info(stdout, "test_rtrimmer", "varstr_cat, varstr_empty, varstr_rtrim");

   z = varstr_new();
   ASSERT("Constructor test", z);

   for (i = 0; i < MAX_ITERATIONS; i++) {
      int       j;
      int       right = rand() % 4;
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

   for (i = 0; i < MAX_ITERATIONS; i++) {
      int       j;
      /* int right = rand() % MAX_CHUNK_SIZE; */
      int       right = rand() % (MAX_CHUNK_SIZE - 1);
      for (j = 0; j < MAX_CHUNK_SIZE; j++)
         buf[j] = 'a';
      for (j = right; j < MAX_CHUNK_SIZE - 1; j++)
         buf[j] = ' ';
      buf[MAX_CHUNK_SIZE - 1] = '\0';

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

#undef MAX_CHUNK_SIZE
#undef MAX_ITERATIONS

#if 0                                            /* 12yy */
static void
test_stub(void)
{
   struct varstr *z;

   fprintf_test_info(stdout, "test_stub()", NULL);

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
