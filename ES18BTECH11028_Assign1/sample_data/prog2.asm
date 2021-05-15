#Program to find setbit
sll $t1, $s3, 2  #Equivalent C program : while(A[i]==0)i++;
add $t1, $t1, $s5 # $s3 -> i, $s5 --> Base address of A
lw $t0, 0($t1) #Loading the value of A[i]
bne $t0, $zero, 2  #Checking the equality condition
addi $s3, $s3, 1 #Incrementing the i
j -6 #Jumping back the the start of the loop i.e line No -1