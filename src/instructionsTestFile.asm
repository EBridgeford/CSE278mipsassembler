lw $ra,0($sp)
sw $ra,0($sp)
add $a0,$v0,$zero
sub $a0,$v0,$zero
addi $t1, $t1, 1
or $t0, $t1, $t2
and $v0, $a0, $v0
ori $v0, $a0, 1024
addi $v0, $zero, 1024
slt $s4, $s0, $t1
slti $t0, $s1, 1
sll $t2, $t1, 1
srl $v0, $a0, 31
#beq $s2, $t1, 100
#j 1000
jr $s1
#jal 1010

addi $t0, $zero, 16
addi $t1,$zero, 16
add $s0, $zero, $zero
add $s1, $zero, $zero
add $t2, $zero, $zero
add $s0, $t1,$zero

add $s2, $s2, $s1
sll $s2, $s2, 2
sw $t2, 1024($s2)
addi $t2, $t2, 1
addi $s0, $s0, 1
#bne $s0, $t0, -8
#move $s0, $zero
addi $s1, $s1, 1
#bne $s1, $t1, -12
