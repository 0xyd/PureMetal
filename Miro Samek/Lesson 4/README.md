# Lesson 4: Blink the LED

In the lesson 4, we are going to learn how to read the documents of Tiva board and TM4C123GH6PM Microcontroller. Then, we use the learned information from the documents to control the LED lights.

According to the block diagram of the Tiva's evaluation board, the LED red, green and blue are controlled by as the below figure. The figure shows that the RGB LED is connected through GPIO interface.

<figure style="text-align: center;">
	<img style="display: block;" src="https://raw.githubusercontent.com/0xyd/PureMetal/main/Miro%20Samek/Lesson%204/pics/How%20the%20LEDs%20connect%20to%20TIVA%20Board.png" alt="How the LEDs connect to TIVA Board">
	<figcaption style="display: block;">Fig 1. How the LEDs connect to TIVA Board</figcaption>
</figure>

If we look closer to the circuit related to the RGB LED circuit figure, the output pins are *LED_R*, *LED_G* and *LED_B*. These output pins are connected to the evaluation boardas shown in the second figure below. The *LED_R*, *LED_G* and *LED_B* connects to *PF1*, *PF2* and *PF3* respectively. According to the Tiva C's manual, the output pins are connected to the board through GPIO pins PF1, PF2, and PF3.
![LED outputs circuit](https://raw.githubusercontent.com/0xyd/PureMetal/main/Miro%20Samek/Lesson%204/pics/LED%20RGB%20output%20circuits.png)

![LED outputs to the board](https://raw.githubusercontent.com/0xyd/PureMetal/main/Miro%20Samek/Lesson%204/pics/LED%20Outputs%20to%20the%20Board%20Input.png)

Memory map describes how memory is laid out in a microcontroller. The memory map consists of *Memory*, *Peripherals*, and *Private Peripheral Bus*. In the *Memory* segment, it consists of *On-chip Flash* and *Bit-banded on-chip SRAM*. The registers of peripheral devices are located at *Peripherals* segment where GPIO interfaces can also be found here. 

## Reference
1. [Embedded Systems Programming Lesson 4 Blinking the LED by Miro Samek](https://www.youtube.com/watch?v=D0VuYe77Wu0&list=PLfcIZXsDLA1-QEyrD4R9YcWWKpbCcrGVP&index=5)
2. [Data sheet of TM4C123GH6PM Microcontroller](https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf?ts=1629421963999&ref_url=https%253A%252F%252Fwww.google.com%252F)
3. [Manual of Tiva C Series TM4C123G LaunchPad Evaluation Board](https://www.ti.com/lit/ug/spmu296/spmu296.pdf?ts=1629375237888&ref_url=https%253A%252F%252Fwww.google.com%252F)
4. [Memory Mapped IO, Peripherals, and Registers](https://jsandler18.github.io/extra/peripheral.html)