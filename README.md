# hexbin
Terminal program for converting to and from binary, decimal, and hexadecimal.  

Run `./hexbin {operation} {string1 string2 string3...}` to produce a converted string.  
The operations are as follows:  

| Operator | Description            |
| ---------|------------------------|
| -bd      | Binary to decimal      |
| -bh      | Binary to hexadecimal  |
| -db      | Decimal to binary      |
| -dh      | Decimal to hexadecimal |
| -hb      | Hexadecimal to binary  |
| -hd      | Hexadecimal to decimal |

hexbin can be fed several strings, separated by whitespace.  

e.g.  
```
~$ ./hexbin -bd 10101 111
10101 -> 21
111 -> 7
```  

## To-do
* Implement functionality to convert from hexadecimal
* Implement conversion to and from ASCII
* Raise upper limit on conversion from decimal to hexadecimal