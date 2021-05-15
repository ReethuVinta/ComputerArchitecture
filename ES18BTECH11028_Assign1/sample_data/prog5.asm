#Mips code for cheching whether a given number is prime or not
#Equivalent C code for(int i=2;i<n;i++){if(n%i==0)return 0;}return 1;
#i-->$t0, n-->$s0
addi $t0, $zero, 2 #int i=2
slt $t1, $t0, $s0  #if(i>num)
bne $t1, $zero, 2
addi $v0, $zero, 1 # Its prime return 1
jr $ra
div $s0, $t0       #p=n%i
slti $t4, $t3, 1
beq $t4, $zero, 2  #if p==0 it is not prime
add $v0, $zero, $zero
jr $ra             #return 0
addi $t0, $t0, 1   #x++
j -10              # Jumps tp statement number 5