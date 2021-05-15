#Mips code for array reversal. Equivalent C code : while(i<n/2)int temp=A[i];A[i]=A[n-i-1];A[n-i-1]=temp;
# i->$t0 , j->$t1, n/2->$s1, n-1->$s0, Base address of A is in $s3
sll $t2, $t0, 2 #Left shifting i by 2
sub $t1, $s0, $t0 #finding out n-i and storing in j
sll $t3, $t1, 2 # Left shifting n-i by 2
add $t2, $t2, $s3 #Adding this value to the base address and storing it
add $t3, $t3, $s3 #Adding this value to the base address and storing it
lw $t4, 0($t2) #Loading value present in t2 to t4
sw $t2, 0($t3) #Saving value of t3 in t2
sw $t3, 0($t4) #saving value of t4 in t3
beq $t0, $s1, 2 #checking the equality condition i=n/2 If attains it jumps to line 13 i.e here it terminates(1 is the offset here indicationg number of instructions between this instruction and the jump place)
addi $t0, $t0, 1 # Incrementing i value
j -11 #Goes back to the start of the loop