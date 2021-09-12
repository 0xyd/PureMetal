#define GPIO_CLOCK_GATING *((unsigned volatile int *) 0x400FE608U)
#define GPIODATA_DIR *((unsigned volatile int *) 0x40025400U)
#define GPIODATA_DEN *((unsigned volatile int *) 0x4002551CU)
#define GPIODATA_DATA *((unsigned volatile int *) 0x400253FCU)
#define GPIODATA_PORT_F_BASE ((unsigned volatile int *) 0x40025000U)

#define LED_RED  (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)

int main(void)
{

    GPIO_CLOCK_GATING = 0x20U;
    GPIODATA_DIR = LED_RED | LED_BLUE | LED_GREEN;
    GPIODATA_DEN = LED_RED | LED_BLUE | LED_GREEN;

    int counter = 0;

    while (1) {

        ++counter;
        if (counter < 1e3) {
            GPIODATA_PORT_F_BASE[LED_RED] = LED_RED;
//            *(GPIODATA_PORT_F_BASE + 2) = LED_RED;
//            *((unsigned volatile int *)(0x40025000U + (LED_RED << 2))) = LED_RED;
//            GPIODATA_DATA = LED_RED; // Red lights up
        }
        if (counter >= 1e3 && counter < 2e3) {
            GPIODATA_PORT_F_BASE[LED_BLUE] = LED_BLUE;
//            *(GPIODATA_PORT_F_BASE + 4) = LED_BLUE;
//            GPIODATA_DATA |= LED_BLUE; // Blue and Red light up
        }
        if (counter >= 2e3 && counter < 3e3) {
            *(GPIODATA_PORT_F_BASE + 8) = LED_GREEN;
//            GPIODATA_DATA |= LED_GREEN; // All light up
        }
        if (counter >= 3e3 && counter < 4e3) {
            GPIODATA_PORT_F_BASE[LED_RED] &= ~LED_RED;
//            GPIODATA_DATA &= ~LED_RED;  // Red turns off
        }
        if (counter >= 4e3 && counter < 5e3) {
            GPIODATA_PORT_F_BASE[LED_GREEN] &= ~LED_GREEN;
//            GPIODATA_DATA &= ~LED_GREEN; // Green turns off
        }
        if (counter >= 5e3 && counter < 6e3) {
            GPIODATA_PORT_F_BASE[LED_BLUE] &= ~LED_BLUE;
//            GPIODATA_DATA &= ~LED_BLUE;  // Blue turns off
        }
        if (counter >= 6e3) {
            counter = 0;
        }
    }

    return 0;
}
