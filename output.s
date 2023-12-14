.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text

read:
	li $v0, 4
	la $a0, _prompt
	syscall
	li $v0, 5
	syscall
	jr $ra

write:
	li $v0, 1
	syscall
	li $v0, 4
	la $a0, _ret
	syscall
	move $v0, $0
	jr $ra


func:
	subu $sp, $sp, 4
	sw $fp, 0($sp)
	move $fp, $sp
	addi $sp, $fp, -1024
	sw $16, -4($fp)
	sw $17, -8($fp)
	sw $18, -12($fp)
	sw $19, -16($fp)
	sw $20, -20($fp)
	sw $21, -24($fp)
	sw $22, -28($fp)
	sw $23, -32($fp)
	sw $30, -36($fp)
	li $10, 0
	sw $10, -88($fp)
	lw $12, -88($fp)
	move $11, $12
	sw $11, -92($fp)
	li $13, 0
	sw $13, -96($fp)
	lw $15, -96($fp)
	move $14, $15
	sw $14, -100($fp)
label1:
	lw $9, -92($fp)
	move $8, $9
	sw $8, -104($fp)
	li $10, 5
	sw $10, -108($fp)
	lw $11, -104($fp)
	lw $12, -108($fp)
	blt $11, $12, label2
	j label3
label2:
	addi $13, $fp, -60
	sw $13, -112($fp)
	lw $8, -92($fp)
	move $15, $8
	sw $15, -116($fp)
	lw $10, -116($fp)
	li $11, 4
	sw $11, -120($fp)
	lw $11, -120($fp)
	mul $9, $10, $11
	sw $9, -116($fp)
	lw $13, -112($fp)
	lw $14, -116($fp)
	add $12, $13, $14
	sw $12, -124($fp)
	lw $8, -124($fp)
	move $15, $8
	sw $15, -128($fp)
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal read
	move $9, $v0
	sw $9, -132($fp)
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	lw $10, -128($fp)
	lw $11, -132($fp)
	sw $11, 0($10)
	lw $13, -92($fp)
	move $12, $13
	sw $12, -136($fp)
	li $14, 1
	sw $14, -140($fp)
	lw $8, -136($fp)
	lw $9, -140($fp)
	add $15, $8, $9
	sw $15, -144($fp)
	lw $11, -144($fp)
	move $10, $11
	sw $10, -92($fp)
	j label1
label3:
	li $12, 0
	sw $12, -148($fp)
	lw $14, -148($fp)
	move $13, $14
	sw $13, -92($fp)
label4:
	lw $8, -92($fp)
	move $15, $8
	sw $15, -152($fp)
	li $9, 5
	sw $9, -156($fp)
	lw $10, -152($fp)
	lw $11, -156($fp)
	blt $10, $11, label5
	j label6
label5:
	addi $12, $fp, -84
	sw $12, -160($fp)
	lw $15, -92($fp)
	move $14, $15
	sw $14, -164($fp)
	lw $9, -164($fp)
	li $10, 4
	sw $10, -168($fp)
	lw $10, -168($fp)
	mul $8, $9, $10
	sw $8, -164($fp)
	lw $12, -160($fp)
	lw $13, -164($fp)
	add $11, $12, $13
	sw $11, -172($fp)
	lw $15, -172($fp)
	move $14, $15
	sw $14, -176($fp)
	addi $8, $fp, -60
	sw $8, -180($fp)
	lw $11, -92($fp)
	move $10, $11
	sw $10, -184($fp)
	lw $13, -184($fp)
	li $14, 4
	sw $14, -188($fp)
	lw $14, -188($fp)
	mul $12, $13, $14
	sw $12, -184($fp)
	lw $8, -180($fp)
	lw $9, -184($fp)
	add $15, $8, $9
	sw $15, -192($fp)
	lw $11, -192($fp)
	move $10, $11
	sw $10, -196($fp)
	lw $13, -196($fp)
	lw $12, 0($13)
	sw $12, -200($fp)
	lw $14, -176($fp)
	lw $15, -200($fp)
	sw $15, 0($14)
	lw $9, -92($fp)
	move $8, $9
	sw $8, -204($fp)
	li $10, 1
	sw $10, -208($fp)
	lw $12, -204($fp)
	lw $13, -208($fp)
	add $11, $12, $13
	sw $11, -212($fp)
	lw $15, -212($fp)
	move $14, $15
	sw $14, -92($fp)
	j label4
label6:
	li $8, 0
	sw $8, -216($fp)
	lw $10, -216($fp)
	move $9, $10
	sw $9, -92($fp)
label7:
	lw $12, -92($fp)
	move $11, $12
	sw $11, -220($fp)
	li $13, 4
	sw $13, -224($fp)
	lw $14, -220($fp)
	lw $15, -224($fp)
	blt $14, $15, label8
	j label9
label8:
	lw $9, -92($fp)
	move $8, $9
	sw $8, -228($fp)
	li $10, 1
	sw $10, -232($fp)
	lw $12, -228($fp)
	lw $13, -232($fp)
	add $11, $12, $13
	sw $11, -236($fp)
	lw $15, -236($fp)
	move $14, $15
	sw $14, -100($fp)
label10:
	lw $9, -100($fp)
	move $8, $9
	sw $8, -240($fp)
	li $10, 5
	sw $10, -244($fp)
	lw $11, -240($fp)
	lw $12, -244($fp)
	blt $11, $12, label11
	j label12
label11:
	addi $13, $fp, -60
	sw $13, -248($fp)
	lw $8, -92($fp)
	move $15, $8
	sw $15, -252($fp)
	lw $10, -252($fp)
	li $11, 4
	sw $11, -256($fp)
	lw $11, -256($fp)
	mul $9, $10, $11
	sw $9, -252($fp)
	lw $13, -248($fp)
	lw $14, -252($fp)
	add $12, $13, $14
	sw $12, -260($fp)
	lw $8, -260($fp)
	move $15, $8
	sw $15, -264($fp)
	lw $10, -264($fp)
	lw $9, 0($10)
	sw $9, -268($fp)
	addi $11, $fp, -60
	sw $11, -272($fp)
	lw $14, -100($fp)
	move $13, $14
	sw $13, -276($fp)
	lw $8, -276($fp)
	li $9, 4
	sw $9, -280($fp)
	lw $9, -280($fp)
	mul $15, $8, $9
	sw $15, -276($fp)
	lw $11, -272($fp)
	lw $12, -276($fp)
	add $10, $11, $12
	sw $10, -284($fp)
	lw $14, -284($fp)
	move $13, $14
	sw $13, -288($fp)
	lw $8, -288($fp)
	lw $15, 0($8)
	sw $15, -292($fp)
	lw $9, -268($fp)
	lw $10, -292($fp)
	bgt $9, $10, label13
	j label14
label13:
	addi $11, $fp, -60
	sw $11, -296($fp)
	lw $14, -92($fp)
	move $13, $14
	sw $13, -300($fp)
	lw $8, -300($fp)
	li $9, 4
	sw $9, -304($fp)
	lw $9, -304($fp)
	mul $15, $8, $9
	sw $15, -300($fp)
	lw $11, -296($fp)
	lw $12, -300($fp)
	add $10, $11, $12
	sw $10, -308($fp)
	lw $14, -308($fp)
	move $13, $14
	sw $13, -312($fp)
	lw $8, -312($fp)
	lw $15, 0($8)
	sw $15, -316($fp)
	addi $9, $fp, -60
	sw $9, -320($fp)
	lw $12, -92($fp)
	move $11, $12
	sw $11, -324($fp)
	lw $14, -324($fp)
	li $15, 4
	sw $15, -328($fp)
	lw $15, -328($fp)
	mul $13, $14, $15
	sw $13, -324($fp)
	lw $9, -320($fp)
	lw $10, -324($fp)
	add $8, $9, $10
	sw $8, -332($fp)
	lw $12, -332($fp)
	move $11, $12
	sw $11, -336($fp)
	addi $13, $fp, -60
	sw $13, -340($fp)
	lw $8, -100($fp)
	move $15, $8
	sw $15, -344($fp)
	lw $10, -344($fp)
	li $11, 4
	sw $11, -348($fp)
	lw $11, -348($fp)
	mul $9, $10, $11
	sw $9, -344($fp)
	lw $13, -340($fp)
	lw $14, -344($fp)
	add $12, $13, $14
	sw $12, -352($fp)
	lw $8, -352($fp)
	move $15, $8
	sw $15, -356($fp)
	lw $10, -356($fp)
	lw $9, 0($10)
	sw $9, -360($fp)
	lw $11, -336($fp)
	lw $12, -360($fp)
	sw $12, 0($11)
	addi $13, $fp, -60
	sw $13, -364($fp)
	lw $8, -100($fp)
	move $15, $8
	sw $15, -368($fp)
	lw $10, -368($fp)
	li $11, 4
	sw $11, -372($fp)
	lw $11, -372($fp)
	mul $9, $10, $11
	sw $9, -368($fp)
	lw $13, -364($fp)
	lw $14, -368($fp)
	add $12, $13, $14
	sw $12, -376($fp)
	lw $8, -376($fp)
	move $15, $8
	sw $15, -380($fp)
	lw $10, -316($fp)
	move $9, $10
	sw $9, -384($fp)
	lw $11, -380($fp)
	lw $12, -384($fp)
	sw $12, 0($11)
label14:
	lw $14, -100($fp)
	move $13, $14
	sw $13, -388($fp)
	li $15, 1
	sw $15, -392($fp)
	lw $9, -388($fp)
	lw $10, -392($fp)
	add $8, $9, $10
	sw $8, -396($fp)
	lw $12, -396($fp)
	move $11, $12
	sw $11, -100($fp)
	j label10
label12:
	lw $14, -92($fp)
	move $13, $14
	sw $13, -400($fp)
	li $15, 1
	sw $15, -404($fp)
	lw $9, -400($fp)
	lw $10, -404($fp)
	add $8, $9, $10
	sw $8, -408($fp)
	lw $12, -408($fp)
	move $11, $12
	sw $11, -92($fp)
	j label7
label9:
	li $13, 0
	sw $13, -412($fp)
	lw $15, -412($fp)
	move $14, $15
	sw $14, -92($fp)
label15:
	lw $9, -92($fp)
	move $8, $9
	sw $8, -416($fp)
	li $10, 5
	sw $10, -420($fp)
	lw $11, -416($fp)
	lw $12, -420($fp)
	blt $11, $12, label16
	j label17
label16:
	addi $13, $fp, -60
	sw $13, -424($fp)
	lw $8, -92($fp)
	move $15, $8
	sw $15, -428($fp)
	lw $10, -428($fp)
	li $11, 4
	sw $11, -432($fp)
	lw $11, -432($fp)
	mul $9, $10, $11
	sw $9, -428($fp)
	lw $13, -424($fp)
	lw $14, -428($fp)
	add $12, $13, $14
	sw $12, -436($fp)
	lw $8, -436($fp)
	move $15, $8
	sw $15, -440($fp)
	lw $10, -440($fp)
	lw $9, 0($10)
	sw $9, -444($fp)
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	lw $11, -444($fp)
	move $a0, $11
	jal write
	sw $11, -444($fp)
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	lw $13, -92($fp)
	move $12, $13
	sw $12, -448($fp)
	li $14, 1
	sw $14, -452($fp)
	lw $8, -448($fp)
	lw $9, -452($fp)
	add $15, $8, $9
	sw $15, -456($fp)
	lw $11, -456($fp)
	move $10, $11
	sw $10, -92($fp)
	j label15
label17:
	li $12, 0
	sw $12, -460($fp)
	lw $14, -460($fp)
	move $13, $14
	sw $13, -92($fp)
label18:
	lw $8, -92($fp)
	move $15, $8
	sw $15, -464($fp)
	li $9, 5
	sw $9, -468($fp)
	lw $10, -464($fp)
	lw $11, -468($fp)
	blt $10, $11, label19
	j label20
label19:
	addi $12, $fp, -84
	sw $12, -472($fp)
	lw $15, -92($fp)
	move $14, $15
	sw $14, -476($fp)
	lw $9, -476($fp)
	li $10, 4
	sw $10, -480($fp)
	lw $10, -480($fp)
	mul $8, $9, $10
	sw $8, -476($fp)
	lw $12, -472($fp)
	lw $13, -476($fp)
	add $11, $12, $13
	sw $11, -484($fp)
	lw $15, -484($fp)
	move $14, $15
	sw $14, -488($fp)
	lw $9, -488($fp)
	lw $8, 0($9)
	sw $8, -492($fp)
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	lw $10, -492($fp)
	move $a0, $10
	jal write
	sw $10, -492($fp)
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	lw $12, -92($fp)
	move $11, $12
	sw $11, -496($fp)
	li $13, 1
	sw $13, -500($fp)
	lw $15, -496($fp)
	lw $8, -500($fp)
	add $14, $15, $8
	sw $14, -504($fp)
	lw $10, -504($fp)
	move $9, $10
	sw $9, -92($fp)
	j label18
label20:
	li $11, 0
	sw $11, -508($fp)
	lw $12, -508($fp)
	move $v0, $12
	lw $16, -4($fp)
	lw $17, -8($fp)
	lw $18, -12($fp)
	lw $19, -16($fp)
	lw $20, -20($fp)
	lw $21, -24($fp)
	lw $22, -28($fp)
	lw $23, -32($fp)
	lw $30, -36($fp)
	move $sp, $fp
	addi $sp, $sp, 4
	lw $fp, 0($fp)
	jr $ra

main:
	subu $sp, $sp, 4
	sw $fp, 0($sp)
	move $fp, $sp
	addi $sp, $fp, -1024
	sw $16, -4($fp)
	sw $17, -8($fp)
	sw $18, -12($fp)
	sw $19, -16($fp)
	sw $20, -20($fp)
	sw $21, -24($fp)
	sw $22, -28($fp)
	sw $23, -32($fp)
	sw $30, -36($fp)
	li $v1, 0
	subu $sp, $sp, 4
	sw $v1, 0($sp)
	subu $sp, $sp, 4
	sw $ra, 0($sp)
	jal func
	move $13, $v0
	sw $13, -40($fp)
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	lw $v1, 0($sp)
	add $sp, $sp, $v1
	lw $15, -40($fp)
	move $14, $15
	sw $14, -60($fp)
	li $8, 0
	sw $8, -44($fp)
	lw $9, -44($fp)
	move $v0, $9
	lw $16, -4($fp)
	lw $17, -8($fp)
	lw $18, -12($fp)
	lw $19, -16($fp)
	lw $20, -20($fp)
	lw $21, -24($fp)
	lw $22, -28($fp)
	lw $23, -32($fp)
	lw $30, -36($fp)
	move $sp, $fp
	addi $sp, $sp, 4
	lw $fp, 0($fp)
	jr $ra
