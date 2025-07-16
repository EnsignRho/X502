# X502
The X502 CPU, a 32-bit reimagining of the indefatigable 6502 by Rick C. Hodgin.

Ex-tee-five-oh-two is a new take on an old idea. By limiting the register set to only 6 general purpose registers, it allows more common opcodes to be accessed using only one byte, with all opcode combinations being available in two bytes.

The register environment is based on the 6502, which used A, X and Y, which were 8-bit registers, the stack (which was technically an 8-bit register with the 9th bit always a 1), and the implicit zero page.

The X502 takes this theme and expands it to A,X,Y and adds T,U,V which share register space with F,G,R fixed-point or floating-point numbers (depending on the implementation).  The full 32-bit register forms are now called A,X,Y,T,U,V, with their 16-bit components being referred to with a W (for word) as AW,XW,YW,TW,UW,VW, and their 8-bit byte form being AB,XB,YW,TB,UB,VB.

There are 16-cores in an X502, with core 0 being the kernel core.  It handles all interrupts and is responsible for dispatching the other cores.

The X502 looks toward multi-threaded apps and introduces a very simple type of memory protecting using process base and limit registers, which indicate where in physical memory the process beings and ends.  There is no paging, and the kernel core can expand or move the process memory space as needed, but there is no mechanism for expansion.  The Zero Page concept still exists, but it's no longer implicit as it was previously.  It's now an explicitly set memory range independent of the process base and limit, which indicates where writes to that range (beginning at Zero Page Base for offset 0 in the process, and continuing forward for Zero Page Limit bytes) occur.  The idea is the kernel core can overlap the Zero Page space with a memory region shared by other cores.  In so doing, the cores can work together using hardware assisted protocols to ensure common access to some task that's being processed or coordinated across multiple cores.  By sharing the Zero Page space of their process memory, writes to that region are visible to the other processes which are also mapped to that same Zero Page space.

All stack accesses are 32-bits, and the immediates used in conjunction with the stack pointer are all indexes into the stack space.  An immediate of 1 indicates a 4-byte displacement, 2 an 8-byte displacement, and -3 a -12-byte displacement, etc.

Most operations on the X502 require only one byte opcodes.  Some require two.  The default processing mode is 32-bit on the X502, so any accesses to 16-bit or 8-bit require an OPx prefix byte which indicates what size to use for the memory operation.

This is a first draft of the ISA.  It will change over time and I hope to find the time to write an emulator, assembler, and debugger.

I want to thank Bill Mensch for creating the 6502.  I hope he enjoys seeing an evolution of his design.

Please contact me with any questions:  rick.c.hodgin@gmail.com

Rick C. Hodgin
July 15, 2025
