# 8085-emulator
Now try all assembly level programming without actually buying the hardware

This Emulator works in CLI(command line mode)

Emulator works in 3 phases...

PHASE 1:

  when single argument(i.e only executable filename is given)
  
    * Allows user to write an assembly program and then execute it.
    * At end display the contents of registers and memory
PHASE 2:

  when two parameters are given/passed(executable file+ assembly program file)
  
    * Checks whether addressing is given or not
    * Do all task of phase 1
PHASE 3:

  when three arguments are given/passed(executable file+assembly proram file+ KEYWORD*)       KEYWORD = DEBUG/DEBUGGER/debug/debug....
  
    * Displays debugger menu and perform operation selected
    * All tasks of phase 2
    
INSTRUCTION SET:
Load and Store - MOV , MVI , LXI , LDA , STA , LHLD , SHLD , STAX , XCHG 
Arithmetic - ADD , ADI , SUB , INR , DCR , INX , DCX , DAD , SUI 
Logical - CMA , CMP 
Branching - JMP , JC , JNC , JZ , JNZ 
One Additional command SET is developed to set data into valid memory locations (Eg - SET 2500,0A )

DEBUGGER MENU:
1. break or b `line no`:- It will set break point on given line number.
2. run or r :- Run the program until it ends or breakpoint is encountered.
3. step or s :- It will run the program one instruction at a time.
4. print or p:- It prints the value of register or memory location. for ex p A will print the value of register A. p x2500 will print the value at memory location x2500 if any.
5. quit or q:- quits the debugger.
6. help:- will show all the commands of debugger




DO LET US KNOW ABOUT CONS OF IT......(BY COMMENTNG)

SO THAT WE CAN FIX IT IN LATER VERSIONS.......
