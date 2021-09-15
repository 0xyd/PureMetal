#define GPIO_CLOCK_GATING *((unsigned volatile int *) 0x400FE608U)
#define GPIODATA_DIR *((unsigned volatile int *) 0x40025400U)
#define GPIODATA_DEN *((unsigned volatile int *) 0x4002551CU)
#define GPIODATA_DATA *((unsigned volatile int *) 0x400253FCU)
#define GPIODATA_PORT_F_BASE ((unsigned volatile int *) 0x40025000U)

#define LED_RED  (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)

void controlLED(int *rgb);

int main(void)
{
    GPIO_CLOCK_GATING = 0x20U;
    GPIODATA_DIR = LED_RED | LED_BLUE | LED_GREEN;
    GPIODATA_DEN = LED_RED | LED_BLUE | LED_GREEN;

    int counter = 0;
    int rgb[3] = {0, 0, 0};

    while (1) {

        ++counter;
        if (counter < 1e5) { // Red lights up
            rgb[0] = 1;
        }
        if (counter >= 1e5 && counter < 2e5) { // Blue and Red light up
            rgb[1] = 1;
        }
        if (counter >= 2e5 && counter < 3e5) { // All light up
            rgb[2] = 1;
        }
        if (counter >= 3e5 && counter < 4e5) { // Red turns off
            rgb[0] = 0;
        }
        if (counter >= 4e5 && counter < 5e5) { // Green turns off
            rgb[1] = 0;
        }
        if (counter >= 5e5 && counter < 6e5) { // Blue turns off
            rgb[2] = 0;
        }
        if (counter >= 6e5) {
            counter = 0;
        }
        controlLED(rgb);
    }

    return 0;
}

/* Light LEDs with an array to control,
 * the 0, 1 and 2 elements are red, blue and green respectively
 * */
void controlLED(int *rgb) {

    if (rgb[0] == 1) {
        GPIODATA_PORT_F_BASE[LED_RED] = LED_RED;
    } else {
        GPIODATA_PORT_F_BASE[LED_RED] &= ~LED_RED;
    }

    if (rgb[1] == 1) {
        GPIODATA_PORT_F_BASE[LED_BLUE] = LED_BLUE;
    } else {
        GPIODATA_PORT_F_BASE[LED_BLUE] &= ~LED_BLUE;
    }

    if (rgb[2] == 1) {
        GPIODATA_PORT_F_BASE[LED_GREEN] = LED_GREEN;
    } else {
        GPIODATA_PORT_F_BASE[LED_GREEN] &= ~LED_GREEN;
    }
}
