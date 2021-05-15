	       .data
Nvalue      :  .asciiz "Enter value of N : "
Avalue      :  .asciiz "Enter value of A : "
Rvalue      :  .asciiz "Enter value of R : "
Result      :  .asciiz "Total number of comparisions in this array is : "
array_Inc   :  .word 0:100  # Declaring an array of size 100
array_Dec   :  .word 0:100  # Declaring an array of size 100
array_Random:  .word 0:100  # Declaring an array of size 100
	       .text
	       .globl main
# N --> $s0
# A --> $s1
# R --> $s2
# array_Inc(Maintains GP in increasing order)    --> $s3
# array_Dec(Maintains GP in decreasing order)    --> $s4
# array_Random(Maintains GP in random order) --> $s5
main            : # Asking user for N value
	          li    $v0, 4
                  la    $a0, Nvalue
                  syscall                # Print to the screen
	       	  # Saving user input in $vo register
                  li    $v0, 5
    	          syscall
                  add   $s0, $v0, $zero  # Shifting the value to $s0 
	      
	      	  # Asking user for A value
	          li    $v0, 4
                  la    $a0, Avalue
                  syscall                # Print to the screen
	          # Saving user input in $vo register
                  li    $v0, 5
    	          syscall
                  add   $s1, $v0, $zero  # Shifting the value to $s1
	      
	          # Asking user for R value
	          li    $v0, 4
                  la    $a0, Rvalue
                  syscall                # Print to the screen
	          # Saving user input in $vo register
                  li    $v0, 5
    	          syscall
	          add   $s2, $v0, $zero  # Shifting the value to $s2
           	       
                  # As we have got N,A,R we will find the elements and store them in our array
		  la    $s3, array_Inc   # Loading the base address of array_Inc
		  la    $s4, array_Dec   # Loading the base address of array_Dec
		  la    $s5, array_Random# Loading the base address of array_Random
		  addi  $s6, $s6, 0      # Index to iterate inside the array while intialising elements
		  addi  $t0, $s1, 0      # Moving value of A to $t0
		  # Intially making all elements in all the array as same i.e: Increasing order
		  sw    $t0, 0($s3)      # Making array_Inc[0]=A
		  sw    $t0, 0($s4)      # Making array_Dec[0]=A
		  sw    $t0, 0($s5)      # Making array_Random[0]=A
		  addi  $s6, $s6, 1      # i=i+1
Array_ForStart:   bge   $s6, $s0, Array_Reversal # if(i>=N)break the loop and reverse the array in array_Dec
   		  addi  $t0, $s6, -1     # j=i-1
   		  sll   $t1, $t0, 2      # j*4
   		  # Adding element in array_Inc    
   		  add   $t2, $t1, $s3    # Address of array_Inc[j]= Base address of array_Inc + j*4
   		  lw    $t3, 0($t2)      # Loading value at array_Inc[i-1]
   		  mul   $t4, $t3, $s2    # array_Inc[i]=array_Inc[i-1]*R
   		  sw    $t4, 4($t2)      # Store this value at array_Inc[i]
   		  # Adding element in array_Dec     
   		  add   $t2, $t1, $s4    # Address of array_Dec[j]= Base address of array_Dec + j*4
   		  lw    $t3, 0($t2)      # Loading value at array_Dec[i-1]
   		  mul   $t4, $t3, $s2    # array_Dec[i]=array_Dec[i-1]*R
   		  sw    $t4, 4($t2)      # Store this value at array_Dec[i]
   		  # Adding element in array_Random     
   		  add   $t2, $t1, $s5    # Address of array[j]= Base address of array + j*4
   		  lw    $t3, 0($t2)      # Loading value at array[i-1]
   		  mul   $t4, $t3, $s2    # array[i]=array[i-1]*R
   		  sw    $t4, 4($t2)      # Store this value at array[i]
   		  # Incrementing iterator           
   		  addi  $s6, $s6, 1      # i=i+1
   		  j     Array_ForStart   # Loop back
    		  # Label that reverse the array_Dec to get the element of GP in decreasing order in that array		
Array_Reversal:   li    $t0, 0           # i=0
		  addi  $t1, $s0, -1     # n-1
		  srl   $t2, $s0,  1     # n/2
	Start:    bge   $t0, $t2, Print_All # if(i>=n/2) Break the loop and go the Print_All label
		  sll   $t3, $t0, 2      # i*4
		  add   $t3, $t3, $s4    # Address of array_Dec[j]= Base address of array_Dec + j*4 
		  lw    $t4, 0($t3)      # Load value  	 
		  sll   $t5, $t1, 2      # $t1*4
		  add   $t5, $t5, $s4    # Address of array_Dec[j]= Base address of array_Dec + j*4 
		  lw    $t6, 0($t5)      # Load value 
		  # Swapping values
		  add   $t7, $t4, $zero  # temp = A[i]
		  sw    $t6, 0($t3)      # A[i] = A[i-1]
		  sw    $t7, 0($t5)      # A[i-1] = temp
		  # Incrementing, Decrementing iterators
		  addi  $t0, $t0, 1      # i++
		  addi  $t1, $t1, -1     # j--
		  j     Start            # Looping back
                  # Function to perform Insertion Sort on array
Insertion_Sort:   # Function starts
		  addi  $t0, $zero, 1    # i=1
		  addi  $v1, $zero, 0    # Variable to count the comparisions done
	for_start: # Loop begins   
	          bge   $t0, $a1, for_end # if(i>=n) the for loop breaks and goes to print_prep label
		  sll   $t1, $t0, 2      # i*4
		  add   $t1, $t1, $a2    # Address of A[i]= Base address of A + i*4
		  lw    $t2, 0($t1)      # Loading the value at A[i]
		  addi  $t3, $t0, -1     # j=i-1
	while_start:	
	 	  blt   $t3, $zero, while_end # if(j<0) end the while loop
		  sll   $t4, $t3, 2      # j*4
		  add   $t4, $t4, $a2    # Address of A[j]= Base address of A + j*4
		  lw    $t5, 0($t4)      # Loading the value at A[j] --> This is TEMP value
		  addi  $v1, $v1, 1      # Incrementing the count of comparisions
		  ble   $t5, $t2, while_end # if(A[j]<=temp) end the while loop
		  addi  $t6, $t3, 1      # j+1
		  sll   $t7, $t6, 2      # (j+1)*4
		  add   $t7, $t7, $a2    # Address of A[j+1]= Base address of A + (j+1)*4
		  sw    $t5, 0($t7)      # A[j+1]=A[j]
		  addi  $t3, $t3, -1     # j=j-1
		  j     while_start	 # Continue the loop
		# After while loop from above breaks, this part will be executed
	while_end:   
		  addi  $t8, $t3, 1      # j+1
		  sll   $t9, $t8, 2      # (j+1)*4
		  add   $t9, $t9, $a2    # Address of A[j+1]= Base address of A + (j+1)*4
		  sw    $t2, 0($t9)      # A[j+1]=temp
		  addi  $t0, $t0, 1      # i+=1
		  j     for_start        # Giving the control to for_start again
	for_end : # If for loop  breaks, control comes here
		  jr    $ra	  	 # Function returns
		  # Function to randomise the elements in array
Randomise:        addi  $t0, $a2, -1     # n-1
	For_Start: # Loop begins
	 	  ble   $t0, $zero, For_End # if(i>=0)loop breaks
	 	  li    $a1, 9       	 # Setting upper limit 
	 	  li    $v0, 42          # Calling for random integer
	 	  syscall                # Gives random number in $a0
	 	  addi  $t1, $a0, 0      # Shifting the number into j
	 	  addi  $t2, $t0, 1      # i+1
	 	  div   $t1, $t2	 # random number/i+1
	 	  mfhi  $t3	  	 # random number % i+1
	 	  # This part does the swapping
	 	  sll   $t4, $t0, 2      # i*4
		  add   $t4, $t4, $a3    # Address of A[i]= Base address of A + i*4
		  lw    $t5, 0($t4)	 # Loading the value	 
		  sll   $t6, $t3, 2      # j*4
		  add   $t6, $t6, $a3    # Address of A[j]= Base address of A + j*4
		  lw    $t7, 0($t6)	 # Loading the value	 
		  add   $t8, $t5, $zero  # temp = A[i]
		  sw    $t7, 0($t4) 	 # A[i] = A[i]
		  sw    $t8, 0($t6)	 # A[j] = temp
		  addi  $t0, $t0, -1	 # i+=1
		  j     For_Start        # Looping back
	For_End:  # If the loop breaks control comes here	           
	       	  jr    $ra		 # Returning from function
		  # Labels where all the functions are called and outputs are printed	 	  	  	 	 	 	 	 	 	 
Print_All:        # Printing array_Inc array and number of comparisions in Insertion sort
		  move  $a1, $s0         # Moving n into $a1
		  move  $a2, $s3	 # Moving array_Inc into $a2
		  jal   print_array      # Printing the array_Inc array
		  move  $a1, $s0         # Moving n into $a1
		  move  $a2, $s3	 # Moving array_Inc into $a2
		  li    $v0, 4
                  la    $a0, Result      # Printing the string in Result
                  syscall                # Print to the screen
		  jal   Insertion_Sort   # Calling the insertion sort function
		  li    $v0, 1           # System call code for printing integer 
    		  add   $a0, $v1, $zero  # Moving the value into a0 for printing
    		  syscall	         # Printing to screen
		  addi  $a0, $0, 0xA     # Ascii code for LF
                  addi  $v0, $0, 0xB     # Syscall prints the lower 8 bits of $a0 as an ascii character.
                  syscall		 # Printing to screen
		  # Printing array_Dec array and number of comparisions in Insertion sort 
		  move  $a1, $s0	 # Moving n into $a1
		  move  $a2, $s4	 # Moving array_Dec into $a2
		  jal   print_array	 # Printing the array_Dec array
		  move  $a1, $s0 	 # Moving n into $a1   
		  move  $a2, $s4	 # Moving array_Dec into $a2
		  li    $v0, 4
                  la    $a0, Result	 # Printing the string in Result
                  syscall                # Print to the screen
		  jal   Insertion_Sort   # Calling the insertion sort function		   
		  li    $v0, 1           # System call code for printing integer 
    		  add   $a0, $v1, $zero  # Moving the value into a0 for printing
    		  syscall
		  addi  $a0, $0, 0xA     # Ascii code for LF
                  addi  $v0, $0, 0xB     # Syscall 11 prints the lower 8 bits of $a0 as an ascii character.
                  syscall		 # Printing to screen
        	  # Printing array_Random array and number of comparisions in Insertion sort 	
		  move  $a2, $s0	 # Moving n into $a2
		  move  $a3, $s5	 # Moving array_Random into $a3
		  jal   Randomise	 # Calling the function that randomizes the function
		  move  $a1, $s0	 # Moving n into $a1
		  move  $a2, $s5	 # Moving array_Random into $a2
		  jal   print_array	 # Printing the array_Dec array 
		  move  $a1, $s0	 # Moving n into $a1
		  move  $a2, $s5	 # Moving array_Random into $a2
		  li    $v0, 4     
                  la    $a0, Result      # Printing the string in Result
                  syscall                # Print to the screen
		  jal Insertion_Sort	 # Calling the insertion sort function		   
		  li    $v0, 1           # System call code for printing integer 
    		  add   $a0, $v1, $zero  # Moving the value into a0 for printing
    		  syscall
		  addi  $a0, $0, 0xA 	 # Ascii code for LF
                  addi  $v0, $0, 0xB 	 # Syscall 11 prints the lower 8 bits of $a0 as an ascii character.
        	  syscall
		  # Exiting the program		   
	          jal   exit
	          # Function that prints the passed array 
print_array:      add   $t0, $zero, $zero # i=0
	For_start: 
		  bge   $t0, $a1, For_end # if(i>=n)break the loop and give control to exit	
		  sll   $t1, $t0, 2       # i*4
		  add   $t1, $t1, $a2     # Address of A[i]= Base address of A + i*4
    		  lw    $t2, 0($t1)       # Load the value at address A[i] 
    		  li    $v0, 1            # System call code for printing integer 
    		  add   $a0, $t2, $zero   # Moving the value into a0 for printing
    		  syscall                 # Print to the screen     
    		  addi  $a0, $zero,32     # Printing a space to the screen
    		  addi  $v0, $zero,11  
    		  syscall	          # Print to the screen
    		  addi  $t0, $t0, 1       # i=i+1
    		  j     For_start         # Run the loop again    		
	For_end:	
		  addi  $a0, $0, 0xA      # Ascii code for LF
        	  addi  $v0, $0, 0xB      # Syscall 11 prints the lower 8 bits of $a0 as an ascii character.
        	  syscall
  		  jr    $ra		  # Returning from function
exit:
		  li    $v0, 10        # Code for the program to end
 		  syscall	      	      	      	      	   