#Finding the score of all elements in array. Code snippet for(int i=0;i<n;i++)XOR^=A[i]; return XOR;
#n-->$s0, n-1-->$t3, Base Address-->$s1, i-->$t0, resultvalue=$s3
sll $t1, $t0, 2   #Left shifting i by 2
add $t1, $t1, $s1 #Adding this value to the base address and storing it
lw $t2, 0($t1)    #Loading value present in t1 to t2
xor $s3, $s3, $t2 #$s3=$s3 xor $t2
beq $t0, $t3, 1   #checking the equality condition i=n-1 If attains it jumps to line 13 i.e here it terminates(1 is the offset here indicating number of instructions between this instruction and the jump place)
addi $t0, $t0, 1  #Incrementing i value
