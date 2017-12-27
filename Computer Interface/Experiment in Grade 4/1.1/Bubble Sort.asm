#####		Bubble Sort			#####
#####		ShYy, at 2017.09.15	#####

		.text
		.globl main
main:
		la		$t0, array			# t0 is the array's addr. Const.
		move	$t1, $zero			# t1 is looping int i.
		move	$t2, $zero			# t2 is looping int j.
		li		$t3, 5				# t3 is the length of the array. In this program, is 5. Const.
		
		li		$v0, 4				# Ready to input. Print the msg1.
		la		$a0, msg1
		syscall
input:
		li		$v0, 5				# Syscall and get the number at v0.
		syscall
		
		move	$t4, $t1			# Like array operation in C, array[i * 4(Byte)] is the number. $4 is i * 4.
		mul		$t4, $t4, 4			# i * 4
		addu	$t5, $t4, $t0		# array[i * 4]
		sw		$v0, 0($t5)
		
		addi	$t1, $t1, 1			# i++
		blt		$t1, $t3, input		# If i < n, goto input, loop. 
		
		move	$t1, $zero			# Initial, i = 0.
loop1:
		move	$t2, $zero			# for(i = 0; i < n - 1; i++) -> for(j = 0; j < n - i - 1; j++)
loop2:
		move	$t4, $t2			# Get $t6 = array[j * 4(Byte)].
		mul		$t4, $t4, 4
		addu	$t8, $t4, $t0		# &array[j * 4] = $t8
		lw		$t6, 0($t8)
		
		addi	$t4, $t2, 1			# Get $t7 = array[(j + 1) * 4(Byte)]
		mul		$t4, $t4, 4
		addu	$t9, $t4, $t0		# &array[(j + 1) * 4] = $t9
		lw		$t7, 0($t9)
		
		blt		$t6, $t7, continue	# If array[j] < array[j + 1], continue.
		sw		$t6, 0($t9)			# Else Swap two numbers.
		sw		$t7, 0($t8)
		
continue:
		addi	$t2, $t2, 1			# j++
		addi	$t4, $t1, 1			# In j < n - i - 1, firstly (i + 1).
		sub		$t5, $t3, $t4		# n - i - 1
		blt		$t2, $t5, loop2		# If j < n - i - 1, continue.
		
		addi	$t1, $t1, 1			# Else go loop1, i++.
		move	$t4, $zero			# Set $t4 = 0.
		addi	$t4, $t4, 1			# Set $t4 = 1.
		sub		$t5, $t3, $t4		# In i < n - 1, solve n - 1.
		blt		$t1, $t5, loop1		# If i < n - 1, continue.
		
		li		$v0, 4				# Ready to print. Print msg2.
		la		$a0, msg2
		syscall
		move	$t1, $zero			# Else Set i = 0, used to print the array.
print:
		move	$t4, $t1			# Get array[i * 4(Byte)].
		mul		$t4, $t4, 4
		addu	$t5, $t4, $t0
		lw		$a0, 0($t5)			# Set print's parameter, array[i * 4].
		li		$v0, 1
		syscall						# Print the number.

		la		$a0, sepr			# Print the space between two number.
		li		$v0, 4
		syscall

		addi	$t1, $t1, 1			# i++
		blt		$t1, $t3, print		# Print loop.
		
		
		.data
msg1:	.asciiz	"Please input 5 numbers. Seperate by Enter.\n"
msg2:	.asciiz "The sorted array is:\n"
sepr:	.asciiz " "
array:	.space 1024