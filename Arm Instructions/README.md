# Instructions in ARM

1. MOV{S} {condition} Register, Operand \
Copy value from the operand to the register. \
With S suffix, the condition code flags are updated on the result of the operation \
"condition" is an optional condition code. \

2. STR{type}{cond} Register_s, [Register_d] \
Stores a word/Byte to a memory. \
Register_s: The register to store. \
Register_d: The location of storage the register points to. \

3. LDR{type}{cond} Register_d, [Register_s] \
Loads a value from the address which Regisiter_s points to. \

4. ADD{S}{cond} {Register_d}, Register_s, Operand \
Add without carry flag (CF). \
Note 1: When the sum of two unsigned number is over the capacity, CF flag is set. \
Note 2: When substracted one unsigned number from another bigger unsigned number, CF flag is set. \


## Reference
1. [ARM and Thumn Instructions](https://developer.arm.com/documentation/dui0489/i/arm-and-thumb-instructions)
2. [Explanation of str in ARM assembly](https://stackoverflow.com/questions/35310272/explanation-of-str-in-arm-assembly)
3. [STR and LDR instruction in ARM Assembly](https://stackoverflow.com/questions/40742645/str-and-ldr-instruction-in-arm-assembly)
4. [Carry Flag, Auxiliary Flag and Overflow Flag in Assembly](https://stackoverflow.com/questions/19301498/carry-flag-auxiliary-flag-and-overflow-flag-in-assembly)
5. [Arm Instruction Sets](https://iitd-plos.github.io/col718/ref/arm-instructionset.pdf)