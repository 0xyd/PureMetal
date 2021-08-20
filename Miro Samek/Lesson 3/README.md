# Lesson 3:  Variables and Pointers

## Example

```c
int global_counter = 0;

int main(void)
{
    int local_counter = 0;
    while (global_counter < 3) {
        ++global_counter;
        ++local_counter;
    }

    int i = 0;
    int *global_counter_ptr = &global_counter;

    for(;i<10; i++) {
        ++(*global_counter_ptr);
    }

    global_counter_ptr = (int *)0x20000200;

    for(i=0;i<10; i++) {
        ++(*global_counter_ptr);
    }

	return 0;
}
```

In this example, we declare 2 variables: *global_counter* and *local_counter*. One is local variable and the other one is the global variable. Unlike the local variable, we cannot view the global variable in the *View->Variables* directly. Therefore, we have to use function *View->Expressions* to look up the address of the *global_counter*. The display result is shown as below:

```assembly
0x20000200 global_counter
0x20000200 0x00000017 0x00000479 0x00000000	0x00000000
```

We now know that the address of *global_counter* is 0x20000200 which is 4 bytes. Therefore, the size of pointers on this platform is 4 bytes. Since integer is 4 bytes as well, the following 4 bytes are used for storing the integer value of *global_counter*. When the program is finished, the value is 0x00000017. 

In the code, there are two approaches to assign memory address to a pointer. We can use address operator *&* to access the address of a variable (ex: *&ast;global_counter_ptr = &global_counter)*. Or, we can assign the memory address by explicit memory address with type casting (ex: *global_counter_ptr = (int &ast;)0x20000200;*). As the experiment has shown, these both approaches have incremented the variable successfully.

Since the ARM architecture is RISC architecture, every data manipulation is done in registers. That means the processor will load the value from memory to register before the calculation. Let's see the following example:
```assembly
11            while (global_counter < 3) {
          main():
000003b4:   490D                ldr        r1, [pc, #0x34]
000003b6:   6808                ldr        r0, [r1]
000003b8:   2803                cmp        r0, #3
000003ba:   DA04                bge        $C$L2
12                ++global_counter;
          $C$L1:
000003bc:   6808                ldr        r0, [r1]
000003be:   1C40                adds       r0, r0, #1
000003c0:   2803                cmp        r0, #3
000003c2:   6008                str        r0, [r1]
000003c4:   DBFA                blt        $C$L1
```

When the processor executes 000003b4, it loads the value to which the address pc + 0x34 points into r1 register. Here, the value in PC is 000003b4 so the addition result becomes 000003EC. By Expression View in CCS, we find out the address 000003EC stores a value 20000200, the address of *global_counter*. Then the processor executes 000003b6 instruction which dereference the address r1 stores. Therefore, the value store in 20000200 is put into r0 register and the processor compares its value with constant 3. Similarily, when the processor increments the value of *global_counter*, it first dereferences the address storing in r1 register and loads the dereferenced results into r0. Then, it adds r0 value with 1 and stores it back to the r0 register.  


## Reference
1. [Variables and Pointers by Miro Samek](https://www.youtube.com/watch?v=v9bWFYcwJJo&list=PLfcIZXsDLA1-QEyrD4R9YcWWKpbCcrGVP&index=5)
