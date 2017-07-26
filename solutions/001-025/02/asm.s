.data
 .equ MAX_LIMIT, 4000000

.text
 .global magic

magic:
    #prologue
    pushl %ebp
    movl %esp, %ebp

    # We are going to use this register to check the evenness of
    #   the number we are processing ;)
    pushl %ebx

    movl $0, %eax   #Current sum value

    movl $1, %ecx   #   All the registers that are going to be used
    movl $1, %edx   # for the calculation of the fibonnaci numbers

first_step:
    #Fibonnacci 1st step: EDX -> ECX
    addl %edx, %ecx

    cmpl $MAX_LIMIT, %ecx   #   Test not greater
    jge end                 # than 4 million

    movl %ecx, %ebx #   Moves the number to another register
    andl $0x1, %ebx # in order to test it's evenness.
    cmpl $0,   %ebx #
    jne second_step #   If the number is even, we add it to
    addl %ecx, %eax # our current result

second_step:
    # Fibonnacci 2nd step: ECX -> EDX (mostly the same as the
    #                                   first step, just backwards)
    addl %ecx, %edx

    cmpl $MAX_LIMIT, %edx   #   Test not greater
    jge end                 # than 4 million

    movl %edx, %ebx #   Moves the number to another register
    andl $0x1, %ebx # in order to test it's evenness.
    cmpl $0,   %ebx #
    jne first_step  #   If the number is even, we add it to
    addl %edx, %eax # our current result.

    jmp first_step  # -> back to step 1

end:
    # And here we restore it to it's previous value (before this
    #   function was called
    popl %ebx

    #epilogue
    movl %ebp, %esp
    popl %ebp
    ret

