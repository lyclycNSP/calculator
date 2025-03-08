# Goal
**Implement a simple calculator based on the command line supporting the elementary arithmetics.**

## **Subtask**
1. Parse user input
    - Seperate user inputs into 3 parts:   
        1. The first operation number
        2. The operation symbol;
        3. The second operation number;
    - Handle wrong or bad-formatted inputs

2. Addition
    - implement integer addition
    - split floating points addition into:
        - integer part addition
        - decimal part addition
            - convert decimal part addition to integer addition
        - combine results from integer part addition and decimal part addition

3. subtraction
    - classify subtraction into 3 categories
        1. negative minus negative -> addition
        2. larger positive minus smaller negative
        3. smaller positive minus larger negative -> condition 2


 
