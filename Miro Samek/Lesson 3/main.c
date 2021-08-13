

/**
 * main.c
 */
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
