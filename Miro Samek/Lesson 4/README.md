# Lesson 4: Blink the LED

In the lesson 4, we are going to learn how to read the documents of Tiva board and TM4C123GH6PM Microcontroller. Then, we use the learned information from the documents to control the LED lights.

## Read Manuals

According to the block diagram of the Tiva's evaluation board, the LED red, green and blue are controlled by as the below figure. The figure shows that the RGB LED is connected through GPIO interface.

<figure>
	<img style="display: block;" src="https://raw.githubusercontent.com/0xyd/PureMetal/main/Miro%20Samek/Lesson%204/pics/How%20the%20LEDs%20connect%20to%20TIVA%20Board.png" alt="Fig 1. How the LEDs connect to TIVA Board">
	<figcaption style="display: block;">Fig 1. How the LEDs connect to TIVA Board</figcaption>
</figure>

If we look closer to the circuit related to the RGB LED circuit figure, the input pins are *LED_R*, *LED_G* and *LED_B*. These inputs pins are connected to the evaluation boardas shown in the second figure below. The *LED_R*, *LED_G* and *LED_B* connects to *PF1*, *PF2* and *PF3* respectively. According to the Tiva C's manual, these pins are connected to the chip through GPIO pins PF1, PF2, and PF3 (check Fig 3.). 

<figure>
	<img style="display: block;" src="https://raw.githubusercontent.com/0xyd/PureMetal/main/Miro%20Samek/Lesson%204/pics/LED%20circuit.png" alt="Fig 2. LED circuit">
	<figcaption style="display: block;">Fig 2. LED circuit</figcaption>
</figure>
<figure>
	<img style="display: block;" src="https://raw.githubusercontent.com/0xyd/PureMetal/main/Miro%20Samek/Lesson%204/pics/The%20Chip%20connect%20to%20LED.png" alt="Fig 3. The Chip connect to LED">
	<figcaption style="display: block;">Fig 3. The Chip connect to LED</figcaption>
</figure>

Memory map describes how memory is laid out in a microcontroller. The memory map consists of *Memory*, *Peripherals*, and *Private Peripheral Bus*. In the *Memory* segment, it consists of *On-chip Flash* and *Bit-banded on-chip SRAM*. As Figure 4 shows, the size of SRAM and Flash are 32.726KB and 262.144KB respectively. The registers of peripheral devices are located at *Peripherals* segment where GPIO interfaces can also be found here. Since the LED lights are controlled by PF1, PF2, and PF3, we need to lookup the keyword *GPIO Port F* in the memory map table. After the lookup, we discover that 0x40025000 is the base of *GPIO Port F*.

<figure>
	<img style="display: block;" src="https://raw.githubusercontent.com/0xyd/PureMetal/main/Miro%20Samek/Lesson%204/pics/Memory%20map%20of%20memory%20segment.png" alt="Fig 4. Memory map of memory segment">
	<figcaption style="display: block;">Fig 4. Memory map of memory segment</figcaption>
</figure>
<figure>
	<img style="display: block;" src="https://raw.githubusercontent.com/0xyd/PureMetal/main/Miro%20Samek/Lesson%204/pics/GPIO%20Port%20F%20in%20Memory%20Map.png" alt="Fig 5. GPIO Port F im Memory Map">
	<figcaption style="display: block;">Fig 5. GPIO Port F in Memory Map</figcaption>
</figure>

Before we start using GPIO pins, we have to turn on the Clock Gating of GPIO modules since the microcontroller turns them off by default to save the energy. As Fig 6 shows, we have to turn the register on by setting bit 5 to 1. The address of GPIO's Run Mode Clock Gating Control is 0x400FE608.

<figure>
	<img style="display: block;" src="https://raw.githubusercontent.com/0xyd/PureMetal/main/Miro%20Samek/Lesson%204/pics/Port%20F%20of%20GPIO%20Run%20Mode%20Clock%20Gating%20Control.png" alt="Fig 6. Port F of GPIO Run Mode Clock Gating Control">
	<figcaption style="display: block;">Fig 6. Port F of GPIO Run Mode Clock Gating Control</figcaption>
</figure>

Now it's time to configure the GPIO pins. There are two types of the register we need to set up: *GPIODATA* and *GPIO Direction*. Fig 7 writes: *values written in GPIODATA register are transferred onto the GPIO port pins if the respective pins have been configured as outputs through GPIO Direction (GPIODIR) register*. In other words, pins that are set as output in GPIO Direction register must have their data register as 1 too.

<figure>
	<img style="display: block;" src="https://raw.githubusercontent.com/0xyd/PureMetal/main/Miro%20Samek/Lesson%204/pics/GPIO%20Data%20Register.png" alt="Fig 7. Description about GPIODATA register">
	<figcaption style="display: block;">Fig 7. Description about GPIODATA register</figcaption>
</figure>

GPIODATA Register can modify the individual bits of GPIO Ports by the address mask

## Reference
1. [Embedded Systems Programming Lesson 4 Blinking the LED by Miro Samek](https://www.youtube.com/watch?v=D0VuYe77Wu0&list=PLfcIZXsDLA1-QEyrD4R9YcWWKpbCcrGVP&index=5)
2. [Data sheet of TM4C123GH6PM Microcontroller](https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf?ts=1629421963999&ref_url=https%253A%252F%252Fwww.google.com%252F)
3. [Manual of Tiva C Series TM4C123G LaunchPad Evaluation Board](https://www.ti.com/lit/ug/spmu296/spmu296.pdf?ts=1629375237888&ref_url=https%253A%252F%252Fwww.google.com%252F)
4. [Memory Mapped IO, Peripherals, and Registers](https://jsandler18.github.io/extra/peripheral.html)
5. [Clock gating by Wiki](https://en.wikipedia.org/wiki/Clock_gating)