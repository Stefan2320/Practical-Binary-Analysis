
1. Confusing objdump


Write a program that confuses objdumpsuch that it interprets data as code, or vice versa.
You’ll probably need to use some inline disassembly to achieve this (for instance, using
gcc’s asmkeyword).

* objdump is a *linear dissasembler* meaning that it will parse all the bytes of a binary and decode them in some instructions. The risk in this approach is that it may decode *inline data* as instructions instead of data.
* we can use `strip <binary>` to strip the symbols of it.

By adding some inline data we change some instructions when the binary is stripped.

Normal:
```
 1165:	5c                   	pop    rsp
    1166:	00 69 69             	add    BYTE PTR [rcx+0x69],ch
    1169:	70                   	.byte 0x70

000000000000116a <main>:
    116a:	f3 0f 1e fa          	endbr64
    116e:	55                   	push   rbp
    116f:	48 89 e5             	mov    rbp,rsp
```

Stripped:
```
1165:	5c                   	pop    rsp
1166:	00 69 69             	add    BYTE PTR [rcx+0x69],ch
1169:	70 f3                	jo     115e <puts@plt+0x10e> <----- instead of 70 it is 70 f3
116b:	0f 1e fa             	nop    edx
116e:	55                   	push   rbp
```


2. Confusing a Recursive Disassembler
Write another program, this time so that it tricks your favorite recursive disassembler’s function detection algorithm. There are various ways to do this. For
instance, you could create a tail-called function or a function that has a switch with multiple return cases. See how far you can go with confusing the disassembler!

* A recursive dissasembler goes with the control flow of the binary, basically follows the call, jumps and return to recusively travers the CFG of a program.
* Some recursive dissasemblers are: IDA Pro, Ghidra, Binary Ninja, Radare2.
* To confuse a recursive dissasembler we can  


