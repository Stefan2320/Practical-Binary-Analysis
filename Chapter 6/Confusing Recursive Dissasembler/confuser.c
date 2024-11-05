#include <stdio.h>

const char tail_string[255] = "Will I be seen or not?";

// With the optimization Ghidra it's doing a jmp instead of a call
#pragma GCC optimize("02")

int test_simple_tail_call(int total, int n){
	if(n == 1) return total;
	return test_simple_tail_call(total*n,n-1);
}


int main(){
  
  int n = 4;
  int x = test_simple_tail_call(1,n);  
  printf("Result is:%d",x);
  return 0;
}


