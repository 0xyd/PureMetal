#define GPIO_CLOCK_GATING *((unsigned volatile int *) 0x400FE608U)
#define GPIODATA_DIR *((unsigned volatile int *) 0x40025400U)
#define GPIODATA_DEN *((unsigned volatile int *) 0x4002551CU)
#define GPIODATA_DATA *((unsigned volatile int *) 0x400253FCU)

/**
 * main.c
 */
int main(void)
{
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
