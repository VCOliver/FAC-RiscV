# Para este exercício você deve ler 2 números da entrada padrão (geralmente o teclado) 
# e imprimir uma única linha contendo a soma destes 2 números

	.eqv SYS_exit, 10
	.eqv SYS_print_int, 1
	.eqv SYS_read_int, 5
	.eqv SYS_print_char, 11
	
	.eqv SYS_call, a7
	
	.macro readInt (%reg)
		li SYS_call, SYS_read_int
		ecall
		mv %reg, a0
	.end_macro 
	
	.text
	.globl main
	
main:
	readInt s0
	blt s0, zero, exit # Exits if less than 0
	readInt s1
	blt s1, zero, exit # Exits if less than 0
	
	add a0, s0, s1	# Sets a0 to s0 + s1
	
	jal print	# Prints the Int to the console
	
	jal exit	# Exits the program
	
print:
	li SYS_call, SYS_print_int
	ecall
	li a0 '\n'
	li SYS_call, SYS_print_char
	ecall
	
	ret
	
exit:
	li SYS_call, SYS_exit
	ecall