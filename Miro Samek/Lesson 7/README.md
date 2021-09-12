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

To ensure the isolation between the pin states, it is better for us to access the address of a specific pin instead. As we know already, the last 2 bits are always 0 since the system is 4-byte alignment so the first LED, red, locates at the bit 3. Thus, we access the data of the red LED as following:

```assembly
*((unsigned volatile int *)(0x40025000U + (LED_RED << 2))) = LED_RED;
//            GPIODATA_DATA = LED_RED; // Red lights up

``` 

LED_RED is marco which is 1U << 1. LED_RED << 2 shifts the bit 1 from the bit 0 to the bit 3 where the red LED locates. However, the readability of this expression is very low so that we will use array and pointer arithmetic to make code more friendly to developers. First of all, we should define a new marco for the base address instead of 0x40025000U. We can then use pointer arithmetic to access the pins' data. The red LED is 0000100 in binary representation so it is 4 bytes away from the base. The address is declared as an unsigned integer variable and the size of an unsigned integer is 2 byte. Therefore, we can access the red led's data by simply adding 2 to the address since 2 x 2(bytes). Also, the LED_RED marco is 2 in decimal so we can add GPIODATA_PORT_F_BASE by LED_RED too. In C, the pointer arithmetic is equivalent to array indexing; as result, the expression can be expressed `GPIODATA_PORT_F_BASE[LED_RED]` too.  

```c
#define GPIODATA_PORT_F_BASE (unsigned volatile int *) 0x40025000U // Define marco for the base address

*(GPIODATA_PORT_F_BASE + 2) = LED_RED;
*(GPIODATA_PORT_F_BASE + LED_RED) = LED_RED;
GPIODATA_PORT_F_BASE[LED_RED] = LED_RED
```

For the LEDs blue and green, their offset to the base address is 8 and 16 respectively. In addition, we had defined LED_BLUE and LED_GREEN to 1U << 2 and 1U << 3. Thus, we can access these 2 LEDs as following:

```c
*(GPIODATA_PORT_F_BASE + 4) = LED_BLUE;
*(GPIODATA_PORT_F_BASE + LED_BLUE) = LED_BLUE;
GPIODATA_PORT_F_BASE[LED_BLUE] = LED_BLUE

*(GPIODATA_PORT_F_BASE + 8) = LED_GREEN;
*(GPIODATA_PORT_F_BASE + LED_GREEN) = LED_GREEN;
GPIODATA_PORT_F_BASE[LED_GREEN] = LED_GREEN
```

After changing the code with the above implementations, the example works perfectly. :)


## References
1. [Arrays and Pointer Arithmetic by Miro Samek](https://www.youtube.com/watch?v=pQs8vp7JOSk&list=PLPW8O6W-1chwyTzI3BHwBLbGQoPFxPAPM&index=34)
2. [How do I check a memory address is 32-bit aligned](https://stackoverflow.com/questions/19190502/how-do-i-check-a-memory-address-is-32-bit-aligned-in-c)