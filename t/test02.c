#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "varstr.h"

int
main(void)
{
   struct varstr *z = varstr_new();
   char        str1[] = " this is some text 	 ";
   char        str2[] = "this is some text";
   char        str3[] = " this is some text 	 ZZZ";
   int         err = 0;

   printf("t/test02\t%s\n", varstr_version());

   err += (NULL == z ? 1 : 0);

   varstr_cat(z, str1);
   err += (0 == strcmp(str1, varstr_str(z)) ? 0 : 1);

   varstr_empty(z);
   varstr_cat(z, str1);
   varstr_lrtrim(z);
   err += (0 == strcmp(str2, varstr_str(z)) ? 0 : 1);

   varstr_empty(z);
   varstr_cat(z, str1);
   varstr_catc(z, 'Z');
   varstr_catc(z, 'Z');
   varstr_catc(z, 'Z');
   err += (0 == strcmp(str3, varstr_str(z)) ? 0 : 1);

   printf("%s\t%s\t%s\n", "varstr", "t/test02", (err > 0 ? "failed" : "passed"));

   varstr_free(&z);

   return 0;
}
