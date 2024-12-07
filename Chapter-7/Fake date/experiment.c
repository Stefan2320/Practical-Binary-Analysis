#include <langinfo.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
   printf("%x", _DATE_FMT);
   printf("%s\n", nl_langinfo(_DATE_FMT));
   exit(EXIT_SUCCESS);
}

