# Simplified MIPS assembler for CSE278


1. Pass in a vector of strings to a general assembler function
2. General assembler function identifies the type of instruction and passes the vector to a assembler for that type
3. Assembler for that type maps each instruction and register to the corresponding hex code
4. The string of hex codes is built along the way and returned

If it encounters an error it the resulting hex string will just contain ERROR and when the function printing to a file see that string it will make a note of it and quit.

By the end we should have
-Parser
-Assembler
-FileWriter
-main.cpp
