	.file	"hello.c"
	.text
	.section	.rodata
.LC0:
	.string	"hello world\n"
.LC1:
	.string	"\n"
	.text
	.globl	hello
	.type	hello, @function
hello:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	movl	%r9d, -24(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	print_str@PLT
	movl	-4(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	print_num@PLT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	print_str@PLT
	movl	-8(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	print_num@PLT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	print_str@PLT
	movl	-12(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	print_num@PLT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	print_str@PLT
	movl	-16(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	print_num@PLT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	print_str@PLT
	movl	-20(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	print_num@PLT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	print_str@PLT
	movl	-24(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	print_num@PLT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	print_str@PLT
	call	halt@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	hello, .-hello
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
