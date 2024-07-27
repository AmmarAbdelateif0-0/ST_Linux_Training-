	.file	"trail.c"
	.text
	.globl	Globvar
	.data
	.align 4
	.type	Globvar, @object
	.size	Globvar, 4
Globvar:
	.long	6
	.globl	bssVar
	.bss
	.align 4
	.type	bssVar, @object
	.size	bssVar, 4
bssVar:
	.zero	4
	.globl	Constvar
	.section	.rodata
	.align 4
	.type	Constvar, @object
	.size	Constvar, 4
Constvar:
	.long	9
	.align 8
.LC0:
	.string	"Globvar= %d ,bssVar=%d,constvar=%d,Localvar=%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$7, -4(%rbp)
	movl	$9, %esi
	movl	bssVar(%rip), %edx
	movl	Globvar(%rip), %eax
	movl	-4(%rbp), %ecx
	movl	%ecx, %r8d
	movl	%esi, %ecx
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
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
