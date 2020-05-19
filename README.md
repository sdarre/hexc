## hexc
Terminal program for converting to and from any base from 2 to 36.  **Not yet tested in Windows**.  

To build, run `make`. To install, build and run `sudo make install`.  To
uninstall, run `sudo make uninstall`.

Run `hexc [operator] [strings]` or `hexc -i[input base] -o[output base] [strings]` to produce a converted string or series of strings. 

The operators are as follows:  

| Operator   | Description            | Operator   | Description            |
|:----------:|------------------------|:----------:|------------------------|
| -bd        | Binary to decimal      | -hb        | Hexadecimal to binary  |
| -bh        | Binary to hexadecimal  | -hd        | Hexadecimal to decimal |
| -bo        | Binary to octal        | -ho        | Hexadecimal to octal   |
| -db        | Decimal to binary      | -ob        | Octal to binary        |
| -dh        | Decimal to hexadecimal | -od        | Octal to decimal       |
| -do        | Decimal to octal       | -oh        | Octal to hexadecimal   |  

hexc can be fed several strings, separated by whitespace. Bases can range from 2 to 36 (inclusive). The maximum value that can be entered for any given string is 18446744073709551615 (in decimal).  

### Examples
```
~$ hexc -bd 10101 111
10101 -> 21
111 -> 7
~$ hexc -i8 -o16 312
312 -> CA
```
