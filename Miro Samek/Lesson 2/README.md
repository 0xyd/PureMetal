# Lesson 2: Flow of Control

## Example 1

```c
int main(void)
{
    int counter = 0;
    while (counter < 3) {
        ++counter;
    }
	return 0;
}
```

```asm
          main():
00000298:   F1AD0D08            sub.w      r13, r13, #8
 8            int counter = 0;
0000029c:   2000                movs       r0, #0
0000029e:   9000                str        r0, [r13]
 9            while (counter < 3) {
000002a0:   9800                ldr        r0, [r13]
000002a2:   2803                cmp        r0, #3
000002a4:   DA05                bge        $C$L2
10                ++counter;
          $C$L1:
000002a6:   9800                ldr        r0, [r13]
000002a8:   1C40                adds       r0, r0, #1
000002aa:   9000                str        r0, [r13]
 9            while (counter < 3) {
000002ac:   9800                ldr        r0, [r13]
000002ae:   2803                cmp        r0, #3
000002b0:   DBF9                blt        $C$L1
12        	return 0;
          $C$L2:
000002b2:   2000                movs       r0, #0
13        }
```



## Example 2

The same example but with the register optimization.



## References
1. [How to calculate 2's complement in hexidecimal](https://electronics.stackexchange.com/questions/32159/twos-complement-of-hexadecimal)