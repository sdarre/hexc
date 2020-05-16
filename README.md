## hexc
Terminal program for converting to and from any base from 2 to 36.  

To build, run `make`. To install, build and run `sudo make install`.  To
uninstall, run `sudo make uninstall`.

Run `hexc {operator} {strings}` or `hexc {-i[input base size] -o[output base size]} {strings}` to produce a converted string or series of strings.  

The operators are as follows:  

| Operator | Description            |
| ---------|------------------------|
| -bd      | Binary to decimal      |
| -bh      | Binary to hexadecimal  |
| -bo      | Binary to octal        |
| -db      | Decimal to binary      |
| -dh      | Decimal to hexadecimal |
| -do      | Decimal to octal       |
| -hb      | Hexadecimal to binary  |
| -hd      | Hexadecimal to decimal |
| -ho      | Hexadecimal to octal   |
| -ob      | Octal to binary        |
| -od      | Octal to decimal       |
| -oh      | Octal to hexadecimal   |

hexc can be fed several strings, separated by whitespace. Bases can range from 2 to 36 (inclusive).  

### Examples
```
~$ hexc -bd 10101 111
10101 -> 21
111 -> 7
~$ hexc -i8 -o16
312 -> CA
```