# Large Number Calculator v0.1

A simple calculator that supports four arithmetic operations 

You can manipulate numbers as large as your computer's memory allows.

## Instructions
1. Running the executable file and you will see these lines:
    > Calculator that supports four arithmetic operations(for now). Developed by Elizabeththh (v0.1)
    >
    > Enter 'q' to quit  
    > Enter any other character to continue  
    > WARNING: you could enter ONLY ONE CHARACTER or unexpected error will occur

    - If you want to quit this program, please enter `q`.  
    - Else please enter ***any other key*** to continue.  
2. Choose a **notation method** to display the result
    > Choose a notation to display result.  
    > 'e' for Scientific Notation, 'p' for Plain Number.

    - If you want the result to display in **Scientific Notation(e_notation)**, please enter a single `e`.    
    - Else enter a single `p` to tell the program you want the result displayed in **Standard Notation(plain number)**.
3. Enter the first **operation number**
    > Enter a number:
    - Enter the first operation number in **plain number**
4. Enter a valid **operator**
    > Valid operators includes '+' '-' '*' '/'   
    > Enter a operator:
    
    - Please enter one of the four operators.
    - Do not enter multiple operators.
5. Enter the second **operation number**
6. Enter a ***integer precision*** you want to display the result
    > Enter an INTEGER to set the precision you want
    > If you are to operate two integers, the precision meanshow many digits after the most significant bit you want to discard
    > If you are to operate two floating points, the precision meanshow many digits   after the decimal point you want to reserve  
    > Enter -1 means you don't want to lose precision except division, and the division precision is 20 by default

    - The precision here means how many digits after decimal point you want this program to display
    - If you enter `-1`, this program will display all the bits it calculates except division. Division display 20 bits at most after decimal points by default. You can enter your prefered precision for division of course.
7. After entering all these, the program will display the result in proper way
8. You could enter `q` to quit after getting the result, or enter any other keys to start another calculation
