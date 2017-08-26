.data
 .equ MAX_LIMIT, 100

.text
 .global magic

magic:
    #prologue
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %edi

    movl $0, %eax
    movl $0, %ebx
    movl $1, %ecx
    movl $0, %edi
    jmp mid_first_loop

    # Sum of the squares
first_loop:
    addl %ecx, %ebx # EBX will have the sum of the
                    #   natural numbers
    movl %ecx, %eax # EAX is needed for multiplication
    mull %eax
    addl %eax, %edi # Sum of the squares goes to EDI
    incl %ecx
mid_first_loop:
    cmpl $MAX_LIMIT, %ecx
    jle first_loop

    # Square the sum
    movl %ebx, %eax
    mull %eax
    subl %edi, %eax # EAX = EAX - EDI
                    # Square of the sum minus
                    #   sum of the squares
    popl %edi
    popl %ebx

    #epilogue
    movl %ebp, %esp
    popl %ebp
    ret

