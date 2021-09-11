# Lesson 7: Arrays and Pointer Arithmetic

Normally, assigning a value to a dereferenced pointer can handle most of the use case. The process of assigning is read/write instructions in assembly. For example, when we want to light up the red LED by *GPIODATA_DATA = LED_RED*, the compiler will generate the following instructions:

```assembly
0000029a:   494A                ldr        r1, [pc, #0x128]
0000029c:   2002                movs       r0, #2
0000029e:   6008                str        r0, [r1]
```

The controller first loads the address of the variable *GPIODATA_DATA* to the register 1. Then it copies value 0x02 to the register 0 and writes the value to the dereferenced address where the register 1 points to.

However, this implementation exists a problem because the read/write instruction will perform incorrectly when interrupts happen. If there is an interrupt happends between instruction ldr and movs, the str will likely load the non-updated value of the register 0 to the register 1.

To ensure the value won't be modified incorrectly, we would like to use pointer arithmetic to manipulate the data of the LED instead. Now, we are going to change the code in the example 6 to this manner.

## Example

According to the manual of the microcontroller, the base address of the data register of the port F is 0x40025000. In the previous practice, we allow the program to change all the data of the pins at once by assigning a masked value to the address 0x400253FC. This implementation does not isolated the pins properly and it is easy for embedded system engineer to misconfigure data.  

To ensure the isolation between pin states, we use the core material of the current lesson, arrays and pointer arithmetic, to implement it. As we know already, the last 2 bits are always 0 since the system is 4-byte alignment. The data of the red LED locates at the bit 3, we can  

## References
1. [Arrays and Pointer Arithmetic by Miro Samek](https://www.youtube.com/watch?v=pQs8vp7JOSk&list=PLPW8O6W-1chwyTzI3BHwBLbGQoPFxPAPM&index=34)
2. [How do I check a memory address is 32-bit aligned](https://stackoverflow.com/questions/19190502/how-do-i-check-a-memory-address-is-32-bit-aligned-in-c)