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



## Reference
1. [Variables and Pointers by Miro Samek](https://www.youtube.com/watch?v=v9bWFYcwJJo&list=PLfcIZXsDLA1-QEyrD4R9YcWWKpbCcrGVP&index=5)
