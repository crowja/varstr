#include <stdlib.h>
#include <stdio.h>
#include "varstr.h"

int
main(void)
{
   struct varstr *z = varstr_new();

   printf("%s\t%s\t%s\n", "varstr", "t/test01", (NULL == z ? "failed" : "passed"));

   varstr_free(z);

   return 0;
}
