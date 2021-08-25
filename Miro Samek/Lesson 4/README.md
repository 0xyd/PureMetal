# Lesson 4: Blink the LED

In the lesson 4, we are going to learn how to read the documents of Tiva board and TM4C123GH6PM Microcontroller. Then, we use the learned information from the documents to control the LED lights.

## Read Manuals

### Block Diagram of Circuits

According to the block diagram of the Tiva's evaluation board, the LED red, green and blue are controlled by as the below figure. The figure shows that the RGB LED is connected through GPIO interface.

<figure>
	<img style="display: block;" src="https://raw.githubusercontent.com/0xyd/PureMetal/main/Miro%20Samek/Lesson%204/pics/How%20the%20LEDs%20connect%20to%20TIVA%20Board.png" alt="Fig 1. How the LEDs connect to TIVA Board">
	<figcaption style="display: block;">Fig 1. How the LEDs connect to TIVA Board</figcaption>
</figure>

If we look closer to the circuit related to the RGB LED circuit figure, the input pins are *LED_R*, *LED_G* and *LED_B*. These inputs pins are connected to the evaluation boardas shown in the second figure below. The *LED_R*, *LED_G* and *LED_B* connect to *PF1*, *PF2* and *PF3* respectively. According to the Tiva C's manual, these pins are connected to the chip through GPIO pins PF1, PF2, and PF3 (check Fig 3.). 

<figure>
	<img style="display: block;" src="https://raw.githubusercontent.com/0xyd/PureMetal/main/Miro%20Samek/Lesson%204/pics/LED%20circuit.png" alt="Fig 2. LED circuit">
	<figcaption style="display: block;">Fig 2. LED circuit</figcaption>
</figure>
<figure>
	<img style="display: block;" src="https://raw.githubusercontent.com/0xyd/PureMetal/main/Miro%20Samek/Lesson%204/pics/The%20Chip%20connect%20to%20LED.png" alt="Fig 3. The Chip connect to LED">
	<figcaption style="display: block;">Fig 3. The Chip connect to LED</figcaption>
</figure>

### Memory Map

Memory map describes how memory is laid out in a microcontroller. The memory map consists of *Memory*, *Peripherals*, and *Private Peripheral Bus*. In the *Memory* segment, it consists of *On-chip Flash* and *Bit-banded on-chip SRAM*. As Figure 4 shows, the size of SRAM and Flash are 32.726KB and 262.144KB respectively. The registers of peripheral devices are located at *Peripherals* segment where GPIO interfaces can also be found here. Since the LED lights are controlled by PF1, PF2, and PF3, we need to lookup the keyword *GPIO Port F* in the memory map table. After the lookup, we discover that 0x40025000 is the base of *GPIO Port F*.

<figure>
	<img style="display: block;" src="https://raw.githubusercontent.com/0xyd/PureMetal/main/Miro%20Samek/Lesson%204/pics/Memory%20map%20of%20memory%20segment.png" alt="Fig 4. Memory map of memory segment">
	<figcaption style="display: block;">Fig 4. Memory map of memory segment</figcaption>
</figure>
<figure>
	<img style="display: block;" src="https://raw.githubusercontent.com/0xyd/PureMetal/main/Miro%20Samek/Lesson%204/pics/GPIO%20Port%20F%20in%20Memory%20Map.png" alt="Fig 5. GPIO Port F im Memory Map">
	<figcaption style="display: block;">Fig 5. GPIO Port F in Memory Map</figcaption>
</figure>

### Clock Gating of GPIO

Before we start using GPIO pins, we have to turn on the Clock Gating of GPIO modules since the microcontroller turns them off by default to save the energy. As Fig 6 shows, we have to turn the register on by setting bit 5 to 1. The address of GPIO's Run Mode Clock Gating Control is 0x400FE608.

<figure>
	<img style="display: block;" src="https://raw.githubusercontent.com/0xyd/PureMetal/main/Miro%20Samek/Lesson%204/pics/Port%20F%20of%20GPIO%20Run%20Mode%20Clock%20Gating%20Control.png" alt="Fig 6. Port F of GPIO Run Mode Clock Gating Control">
	<figcaption style="display: block;">Fig 6. Port F of GPIO Run Mode Clock Gating Control</figcaption>
</figure>

### GPIO Registers

Now it's time to configure the GPIO pins. There are three types of the register we need to set up: *GPIODATA*, *GPIO Direction*, and *GPIO Digital Enable*. GPIODATA register provides a mask as an interface that can read/write a data register without affecting other pins' states. (See details information in Figure 7.) GPIO Direction register determines the pins' input and output states. GPIO Digital Enable register activates the digital function of the pins.

#### GPIODATA Register

Keep in mind that the GPIODATA register uses bits 2-9 of the address as a mask to configure the values in the register; the last two bits are set 0 due to 4 bytes alignment. The port F has pins 0-7 so its representation in binary is 0x11111111. Since the last 2 bits of the address are 0, the binary representation is 0x1111111100 which is 0x3FC. Hence, the address of data register of Port F becomes 0x40025000 + 0x3FC = 0x400253FC. To determine which LED to blink, we have to set up the value in the data register. For instance, if we want the RED LED to turn on, we write value 0x00000002 to the address. However, this setup cannot wake up the RED LED because we have to define the pins state and enable the digital functions beforehand.


<figure>
	<img style="display: block;" src="https://raw.githubusercontent.com/0xyd/PureMetal/main/Miro%20Samek/Lesson%204/pics/Data%20Register%20Operation.png" alt="Fig 7. Description about GOIPDATA register operation">
	<figcaption style="display: block;">Fig 7. Description about GOIPDATA register operation</figcaption>
</figure>

#### GPIODATA Direction Register

In Fig 8, it says: *values written in GPIODATA register are transferred onto the GPIO port pins if the respective pins have been configured as outputs through GPIO Direction (GPIODIR) register*. In other words, whenever a pin state of GPIODATA register is 1, then its corresponding bits in GPIO Direction register must be 1 too.

<figure>
	<img style="display: block;" src="https://raw.githubusercontent.com/0xyd/PureMetal/main/Miro%20Samek/Lesson%204/pics/GPIO%20Data%20Register.png" alt="Fig 8. Description about GPIODATA register">
	<figcaption style="display: block;">Fig 8. Description about GPIODATA register</figcaption>
</figure>

To set up GPIO Direction register of the Port F, we have to find where it locates. According to the manual, GPIO Port F's Direction register locates at 0x40025400 (Base of Port F: 0x40025000 + offset 0x400). Since the *LED_R*, *LED_G* and *LED_B* connect to *PF1*, *PF2* and *PF3*, the bit 1, 2, and 3 are set to 1. As Fig 8 shows, the bits port 0-7 represent port 0 to 7 respectively so we should assign value 00001110 to the address 0x40025400. 

<figure>
	<img style="display: block;" src="https://raw.githubusercontent.com/0xyd/PureMetal/main/Miro%20Samek/Lesson%204/pics/8%20pins%20of%20GPIODATA%20Direction%20register.png" alt="Fig 9. 8 pins of GPIODATA Direction register">
	<figcaption style="display: block;">Fig 9. 8 pins of GPIODATA Direction register</figcaption>
</figure>

#### GPIODATA Digital Enable Register

Then, we have to enable the digital function of the ports as well. Similar to GPIO Direction register, we have to activate  *PF1*, *PF2* and *PF3* by setting up bit 1,2, and 3 to 1 in the address 0x4002551C (0x40025000 + offset 0x51C).

<figure>
	<img style="display: block;" src="https://raw.githubusercontent.com/0xyd/PureMetal/main/Miro%20Samek/Lesson%204/pics/Description%20about%20GPIO%20Digital%20Enable%20register.png" alt="Fig 10. Description about the GPIO Digital Enable Register">
	<figcaption style="display: block;">Fig 10. Description about the GPIO Digital Enable Register</figcaption>
</figure>

## Implementation

In the implementation, we want the Tiva board to light up Red, Blue, and Green one at a time. The implementation is as below:

```c
int main(void)
{
    unsigned int *GPIO_CLOCK_GATING = (unsigned int *) 0x400FE608U;
    unsigned int *GPIODATA_DIR = (unsigned int *) 0x40025400U;
    unsigned int *GPIODATA_DEN = (unsigned int *) 0x4002551CU;
    unsigned int *GPIODATA_DATA = (unsigned int *) 0x400253FCU;

    *GPIO_CLOCK_GATING = 0x20U;
    *GPIODATA_DIR = 0x0EU;
    *GPIODATA_DEN = 0x0EU;

    int counter = 0;

    while (1) {

        ++counter;
        if (counter < 1e5) {
            *GPIODATA_DATA = 0x02U; // Red lights out
        }
        if (counter >= 1e5 && counter < 2e5) {
            *GPIODATA_DATA = 0x04U; // Blue lights out
        }
        if (counter >= 2e5 && counter < 3e5) {
            *GPIODATA_DATA = 0x08U; // Green lights out
        }
        if (counter >= 3e5) {
            counter = 0;
        }
    }

	return 0;
}

```

As what we have learned from the manual, we have to activate the clock gating of GPIO's port F by setting the 5th bit to 1. In hexadeciaml, it is 0x20U. Besides, we have to set all the pins 1, 2, and 3 to 1 as the output pins and must activate their digital functions. Thus, we have to set up bits 1-3 in the data direction register and data digital enable register to 1 which is 0x0EU in hexadeciaml. After that, we can control light by manipulate the data register: 0x02, 0x04, and 0x08 are red, blue, and green LEDs respectively. 

The demo can be found [here](https://youtu.be/F7MbO46YJ_Y).




## Reference
1. [Embedded Systems Programming Lesson 4 Blinking the LED by Miro Samek](https://www.youtube.com/watch?v=D0VuYe77Wu0&list=PLfcIZXsDLA1-QEyrD4R9YcWWKpbCcrGVP&index=5)
2. [Data sheet of TM4C123GH6PM Microcontroller](https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf?ts=1629421963999&ref_url=https%253A%252F%252Fwww.google.com%252F)
3. [Manual of Tiva C Series TM4C123G LaunchPad Evaluation Board](https://www.ti.com/lit/ug/spmu296/spmu296.pdf?ts=1629375237888&ref_url=https%253A%252F%252Fwww.google.com%252F)
4. [Memory Mapped IO, Peripherals, and Registers](https://jsandler18.github.io/extra/peripheral.html)
5. [Clock gating by Wiki](https://en.wikipedia.org/wiki/Clock_gating)