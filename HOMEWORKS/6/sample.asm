#
# A simple test R2K assembly program
#
# When assembled, the object module version of this program will have
# information in the text, rdata, and data sections; it will have two
# relocation entries (corresponding to the two 'j' instructions) and two
# reference entries (where 'array' and 'count' are used); and every label
# used here will be in the symbol table.
# 
# When linked, the relocation and reference entries will disappear, and
# there will be additional symbol table entries for the startup routine
# that is always linked in by the linker.
# 

#
# Put this array in the read-only data section
#
	.rdata
array:	.word	10, 20, 12, 235, 12111, 92342, -17

#
# Put this in the initialized data section
#
	.data
count:	.word	7

#
# Now for the executable code; first, the sum(array,n) function
#
	.text
	.globl	sum		# mark it as globally available
sum:
	addi	$sp, $sp, -4	# create the stack frame
	sw	$ra, 0($sp)	# save our return address
	li	$v0, 0		# running total
	move	$t0, $a0	# array base address
	move	$t1, $a1	# number of elements to process
loop:
	slti	$t2, $t1, 1	# is the count < 1?
	bne	$t2, $zero, done	# yes
	lw	$t2, 0($a0)	# yes - add the current element
	addi	$a0, $a0, 4	# move pointer to the next element
	addi	$t1, $t1, -1	# decrement the count
	j	loop		# and continue
done:
	lw	$ra, 0($sp)	# restore our return address
	addi	$sp, $sp, 4	# tear down the stack frame
	jr	$ra		# return

#
# next, the main program
#
	.globl	main		# also globally available
main:
	addi	$sp, $sp, -4	# create the stack frame
	sw	$ra, 0($sp)	# save our return address
	la	$a0, array	# array argument
	lw	$a1, count	# number of elements
	jal	sum		# sum it up
	lw	$ra, 0($sp)	# restore our return address
	addi	$sp, $sp, 4	# tear down the stack frame
	jr	$ra		# return
