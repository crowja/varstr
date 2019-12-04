#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "varstr.h"

int
main(void)
{
   struct varstr *z = varstr_new();
#define NITER 1000
   char        str[3 * NITER + 1];
   int         i;
   int         err = 0;

   printf("t/test04\t%s\n", varstr_version());

   varstr_extend(z, 20);

   for (i = 0; i < NITER; i++) {
      varstr_catc(z, 'a');
      varstr_catc(z, 'b');
      varstr_catc(z, 'c');
      str[3 * i] = 'a';
      str[3 * i + 1] = 'b';
      str[3 * i + 2] = 'c';
      str[3 * i + 3] = '\0';
   }

   err += (0 == strcmp(str, varstr_str(z)) ? 0 : 1);

   printf("%s\t%s\t%s\n", "varstr", "t/test04", (err > 0 ? "failed" : "passed"));

   varstr_free(z);

   return 0;
}
