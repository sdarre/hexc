## hexc
Terminal program for converting to and from binary, decimal, and hexadecimal.  

To build, run `make`. To install, build and run `sudo make install`.  To
uninstall, run `sudo make uninstall`.

Run `hexc {operator} {string1 string2 string3...}` to produce a converted string or series of strings.  

The operators are as follows:  

| Operator | Description            | Limit (per string)                                    |
| ---------|------------------------| ------------------------------------------------------|
| -bd      | Binary to decimal      | 11111111111111111111111111111111111111111111111111111 |
| -bh      | Binary to hexadecimal  | Unlimited.                                            |
| -db      | Decimal to binary      | 18446744073709551615                                  |
| -dh      | Decimal to hexadecimal | 18446744073709551615                                  |
| -hb      | Hexadecimal to binary  | Unlimited.                                            |
| -hd      | Hexadecimal to decimal | FFFFFFFFFFFFF                                         |

hexc can be fed several strings, separated by whitespace. For example:  
```
~$ hexc -bd 10101 111
10101 -> 21
111 -> 7
~$ hexc -hb 3b9ac9ff ABC123
3B9AC9FF -> 00111011100110101100100111111111
ABC123 -> 101010111100000100100011
```  

### To-do
* Implement conversion to and from ASCII
* Implement the ability to feed text files as input
* Figure out some better way to implement HexToBin (I know it's ugly)
* Raise limit on BinToDec and HexToDec
