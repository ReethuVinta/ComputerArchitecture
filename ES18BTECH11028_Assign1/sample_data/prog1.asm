# Compute and return fibonacci number
#$s0-->n, $t0-->0, $t1-->1
beq $s0, $t0, 22    #if n=0 return 0
beq $s0, $t1, 23    #if n=1 return 1
addi $sp, $sp, -4   
sw $ra, 0($sp)
addi $s0, $s0, 1    #Calculating n-1
jal -6              #Calling fib(n-1)
addi $s0, $s0, 1    #n=n+1
lw $ra, 0($sp)      #restoring return address from stack
addi $sp, $sp, 4    #Incrementing the stack pointer to push return value
addi $sp, $sp, 4    #Pushing return value to stack
sw $v0, 0($sp)      
addi $sp, $sp, -4   #Storing return address
sw $ra, 0($sp)
addi $s0, $s0, 2    #n-2
jal -15             #Calling fib(n-2)
addi $s0, $s0, 2    #n=n+2
lw $ra, 0($sp)      #restoring return address from stack
addi $sp, $sp, 4    #Incrementing the stack pointer to push return value
lw $s1, 0($sp)      #Pop return value from stack
addi $sp, $sp, 4    #Incrementing stack pointer
add $v0, $v0, $s1   #fib(n - 2)+fib(n-1)
jr $ra              #returning value
jr $ra              #When n is 0 control comes here
jr $ra              #When n is 1 control comes here