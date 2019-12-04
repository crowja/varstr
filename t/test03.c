#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "varstr.h"

int
main(void)
{
   struct varstr *z = varstr_new();
#define NITER 5000
   char        str[3 * NITER + 1];
   int         i;
   int         err = 0;

   printf("t/test03\t%s\n", varstr_version());

   varstr_extend(z, 10);

   for (i = 0; i < NITER; i++) {
      varstr_cat(z, "dog");
      str[3 * i] = 'd';
      str[3 * i + 1] = 'o';
      str[3 * i + 2] = 'g';
      str[3 * i + 3] = '\0';
   }

   err += (0 == strcmp(str, varstr_str(z)) ? 0 : 1);

   printf("%s\t%s\t%s\n", "varstr", "t/test03", (err > 0 ? "failed" : "passed"));

   varstr_free(z);

   return 0;
}
