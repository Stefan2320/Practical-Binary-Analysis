#include <stdio.h>

const char glob[256] = "Global data";
int global_variable;

void test(){
	printf("Inside test.\n");
}

asm(
".text\n" 
".byte 0x8e,0x20,0x5c,0x00,0x69,0x69,0x70"
);

int main(){
  test();
  return 0;
}
