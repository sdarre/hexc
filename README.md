## hexc
Terminal program for converting to and from binary, decimal, and hexadecimal.  

Simply run `make` to install and `make clean` to uninstall.  

Run `hexc {operator} {string1 string2 string3...}` to produce a converted string or series of strings.  

The operators are as follows:  

| Operator | Description            | Limit (per string)                                    |
| ---------|------------------------| ------------------------------------------------------|
| -bd      | Binary to decimal      | 11111111111111111111111111111111111111111111111111111 |
| -bh      | Binary to hexadecimal  | Unlimited.                                            |
| -db      | Decimal to binary      | 9199999999999999999                                   |
| -dh      | Decimal to hexadecimal | 4294967295                                            |
| -hb      | Hexadecimal to binary  | Unlimited.                                            |
| -hd      | Hexadecimal to decimal | FFFFFFFFFFFFF                                         |

hexc can be fed several strings, separated by whitespace. For example:  
```
~$ hexc -bd 10101 111
10101 -> 21
111 -> 7
~$ hexc -hb 3b9ac9ff
3B9AC9FF -> 00111011100110101100100111111111
```  

### To-do
* Implement conversion to and from ASCII
* Implement the ability to feed text files as input
* Raise upper limit on conversion from decimal to hexadecimal and vice versa
