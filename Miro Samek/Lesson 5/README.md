# Lesson 5: Preprocessor and Volatile

In the previous lesson, we access the memory address of the registers to control the LED blinks by declaring pointer variables. In convention, however, embedded engineer tends to use the Marco to define the registers because the readability of code is much better than declaring variables for the addresses of the registers.

## Preprocessor

Preprocessor, a.k.a marco preprocessor is a program invoked by compiler to process the code before actual compiling. It can include headers, do macro expansion, establish conditional compilation, and line control. When we use marco *define*, the preprocessor will replace the target code with the defined string before the compilation. The define syntax is as following:

```c
#define <identifier> <replacement token list>
#define <identifier>(<parameter list>) <replacement token list>
```

Let's rewrite the code in lesson 4 with the *define* syntax:

```c
#define GPIO_CLOCK_GATING *((unsigned int *) 0x400FE608U)
#define GPIODATA_DIR *((unsigned int *) 0x40025400U)
#define GPIODATA_DEN *((unsigned int *) 0x4002551CU)
#define GPIODATA_DATA *((unsigned int *) 0x400253FCU)

/**
 * main.c
 */
int main(void)
{
//    The previous declaration
//    unsigned int *GPIO_CLOCK_GATING = (unsigned int *) 0x400FE608U;
//    unsigned int *GPIODATA_DIR = (unsigned int *) 0x40025400U;
//    unsigned int *GPIODATA_DEN = (unsigned int *) 0x4002551CU;
//    unsigned int *GPIODATA_DATA = (unsigned int *) 0x400253FCU;

    GPIO_CLOCK_GATING = 0x20U;
    GPIODATA_DIR = 0x0EU;
    GPIODATA_DEN = 0x0EU;

    int counter = 0;

    while (1) {

        ++counter;
        if (counter < 1e5) {
            GPIODATA_DATA = 0x02U; // Red lights out
        }
        if (counter >= 1e5 && counter < 2e5) {
            GPIODATA_DATA = 0x04U; // Blue lights out
        }
        if (counter >= 2e5 && counter < 3e5) {
            GPIODATA_DATA = 0x08U; // Green lights out
        }
        if (counter >= 3e5) {
            counter = 0;
        }
    }

	return 0;
}

```

In the syntax *define NAME *((unsigned int *) ADDRESS)*, we use (unsigned int &#42;) to declare what type of pointer the address is and use the other &#42; as a dereference operator so that we can assign the value to address by a simple expression *NAME = value;*. 

## Volatile

Keyword volatile tells compiler not to optimize the code that envolves the volatile variable. That means the compiler won't cache the values of the volatile variable automatically. Instead, the value of a volatile variable is always stayed in the main memory and the compiler will generate specific code to access the value in the memory for every data manipulation. This feature suits the circumstance where the value of a memory address is changable through hardware interface. Thus, the volatile keyword should be added to the memory address of GPIO pins. 

So, the declaration of the register becomes:
```c
#define GPIO_CLOCK_GATING *((unsigned volatile int *) 0x400FE608U)
#define GPIODATA_DIR *((unsigned volatile int *) 0x40025400U)
#define GPIODATA_DEN *((unsigned volatile int *) 0x4002551CU)
#define GPIODATA_DATA *((unsigned volatile int *) 0x400253FCU)
```


## Reference
1. [Embedded Systems Programming Lesson 4 Blinking the LED by Miro Samek](https://www.youtube.com/watch?v=eEyvVA0bmcA&list=PLfcIZXsDLA1-QEyrD4R9YcWWKpbCcrGVP&index=6)
2. [C Preprocessor by Wiki](https://en.wikipedia.org/wiki/C_preprocessor)
3. [Why is volatile needed in C?](https://stackoverflow.com/questions/246127/why-is-volatile-needed-in-c)
