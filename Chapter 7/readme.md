

### Make a copy of the date binary and modify the appearance of it. 

`date` - a simple command that is used to display the current date, nothing fancy.

The first step is to copy the binary into a local folder. If we use the `strings` command on `date`, we can see that there are some format (fmt) specifiers. Let's try to change the default way it displays the date.

## Original way:
Thu Nov 29 09:07:33 PM EET 2024
%a %b %e %H:%M:%S %Z %Y


If we search for this format and change it to something else, we see that the date still looks the same. This means the `date` command might retrieve the format from somewhere else.

Running `ltrace` on the binary will show you that it calls `nl_langinfo()` (you can also see this in GDB if you have the patience). This function takes an `item` as a parameter, and based on its value, it returns a specific format string (for more info use the `man` pages).

To confirm this theory, we can check it in GDB by setting a breakpoint at `nl_langinfo()`. In GDB, we see that the parameter for `nl_langinfo()` is `0x20006c`. To see exactly what this value represents we can look into `langinfo.h`, where the items are defined in an unnamed enum.

After playing a bit with it, I found that the default item from the enum is `_DATE_FMT`.

Cool! So we know that we can't directly modify the format but with `hexedit` we can modify contents from the help menu.

The next step would be to see if we can use the format defined in the binary instead of the one provided by `nl_langinfo()`. After some debugging, we find that if there is an invalid item for `nl_langinfo()`, it will look in the binary for the format. This means we can control the format.


Let's look at the disassembly (objdump -M intel -d -j .text date | grep -A 5 -B 3 "nl_"):
```
    4584:	bf 6c 00 02 00       	mov    edi,0x2006c <------------------------------------ make this -1 (invalid item)
    4589:	e8 12 f2 ff ff       	call   37a0 <nl_langinfo@plt>
    458e:	80 38 00             	cmp    BYTE PTR [rax],0x0
    4591:	49 89 c5             	mov    r13,rax
    4594:	0f 85 a4 fe ff ff    	jne    443e <__sprintf_chk@plt+0xb2e>
    459a:	4c 8d 2d 64 00 01 00 	lea    r13,[rip+0x10064]        <----- modify format that is at that offset from rip 
```

To make the item argument invalid we can just search the bytes `6c 00 02 00` in hexedit and change them to an invalid value.
To modify the format I just searched for the default format and changed some bytes in there.



