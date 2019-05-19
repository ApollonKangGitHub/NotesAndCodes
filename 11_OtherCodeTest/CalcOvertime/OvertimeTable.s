	.file	"OvertimeTable.c"
	.globl	gInfoDbgFlag
	.bss
	.align 4
	.type	gInfoDbgFlag, @object
	.size	gInfoDbgFlag, 4
gInfoDbgFlag:
	.zero	4
	.globl	gFunDbgFlag
	.align 4
	.type	gFunDbgFlag, @object
	.size	gFunDbgFlag, 4
gFunDbgFlag:
	.zero	4
	.section	.rodata
.LC0:
	.string	"DayIndex"
.LC1:
	.string	"Week"
.LC2:
	.string	"StartStamp"
.LC3:
	.string	"EndStamp"
.LC4:
	.string	"Holiday"
.LC5:
	.string	"SleepTime"
.LC6:
	.string	"Hours"
.LC7:
	.string	"Minutes"
.LC8:
	.string	"Rebound"
.LC9:
	.string	"adjust"
.LC10:
	.string	"Exception"
	.data
	.align 32
	.type	title, @object
	.size	title, 88
title:
	.quad	.LC0
	.quad	.LC1
	.quad	.LC2
	.quad	.LC3
	.quad	.LC4
	.quad	.LC5
	.quad	.LC6
	.quad	.LC7
	.quad	.LC8
	.quad	.LC9
	.quad	.LC10
	.section	.rodata
.LC11:
	.string	"Error"
.LC12:
	.string	"Monday"
.LC13:
	.string	"Tuesday"
.LC14:
	.string	"Wednesday"
.LC15:
	.string	"Thursday"
.LC16:
	.string	"Friday"
.LC17:
	.string	"Saturday"
.LC18:
	.string	"Sunday"
.LC19:
	.string	"Invalid"
	.data
	.align 32
	.type	weekString, @object
	.size	weekString, 72
weekString:
	.quad	.LC11
	.quad	.LC12
	.quad	.LC13
	.quad	.LC14
	.quad	.LC15
	.quad	.LC16
	.quad	.LC17
	.quad	.LC18
	.quad	.LC19
	.section	.rodata
	.align 8
.LC20:
	.string	"\nError:The number of parameters error!\nFormat:%s fileName \n"
	.align 8
.LC21:
	.string	"\nOpen file[input file:%s, output file:%s] or create file failure[fdi:%d,fdo:%d]!\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$304, %rsp
	movl	%edi, -292(%rbp)
	movq	%rsi, -304(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-272(%rbp), %rdx
	movl	$0, %eax
	movl	$16, %ecx
	movq	%rdx, %rdi
	rep stosq
	leaq	-144(%rbp), %rdx
	movl	$0, %eax
	movl	$16, %ecx
	movq	%rdx, %rdi
	rep stosq
	movl	$-1, -280(%rbp)
	movl	$-1, -276(%rbp)
	cmpl	$1, -292(%rbp)
	jg	.L2
	movq	-304(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rsi
	movl	$.LC20, %edi
	movl	$0, %eax
	call	printf
	movl	$1, %edi
	call	exit
.L2:
	movq	-304(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rdx
	leaq	-272(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcpy
	movq	-304(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rdx
	leaq	-144(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcpy
	leaq	-144(%rbp), %rax
	movq	$-1, %rcx
	movq	%rax, %rdx
	movl	$0, %eax
	movq	%rdx, %rdi
	repnz scasb
	movq	%rcx, %rax
	notq	%rax
	leaq	-1(%rax), %rdx
	leaq	-144(%rbp), %rax
	addq	%rdx, %rax
	movabsq	$32770349001437742, %rsi
	movq	%rsi, (%rax)
	leaq	-272(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	open
	movl	%eax, -280(%rbp)
	leaq	-144(%rbp), %rax
	movl	$436, %edx
	movl	$578, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	open
	movl	%eax, -276(%rbp)
	cmpl	$0, -280(%rbp)
	js	.L3
	cmpl	$0, -276(%rbp)
	jns	.L4
.L3:
	movl	-276(%rbp), %esi
	movl	-280(%rbp), %ecx
	leaq	-144(%rbp), %rdx
	leaq	-272(%rbp), %rax
	movl	%esi, %r8d
	movq	%rax, %rsi
	movl	$.LC21, %edi
	movl	$0, %eax
	call	printf
	movl	$1, %edi
	call	exit
.L4:
	movl	-276(%rbp), %edx
	movl	-280(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	calc_over_time
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L6
	call	__stack_chk_fail
.L6:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.section	.rodata
.LC22:
	.string	"\nRead file failure!"
	.text
	.type	calc_over_time, @function
calc_over_time:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$2944, %rsp
	movl	%edi, -2932(%rbp)
	movl	%esi, -2936(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-1040(%rbp), %rdx
	movl	$0, %eax
	movl	$128, %ecx
	movq	%rdx, %rdi
	rep stosq
	movq	$0, -1072(%rbp)
	movq	$0, -1064(%rbp)
	movq	$0, -1056(%rbp)
	movq	$0, -1048(%rbp)
	movl	$-1, -2916(%rbp)
	movb	$0, -2917(%rbp)
	leaq	-1040(%rbp), %rax
	movq	%rax, -2912(%rbp)
	movq	$0, -2904(%rbp)
	leaq	-2832(%rbp), %rax
	movq	%rax, %rdi
	call	reset_overtime_Info
	movq	-2912(%rbp), %rcx
	movl	-2932(%rbp), %eax
	movl	$1024, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read
	movl	%eax, -2916(%rbp)
	cmpl	$0, -2916(%rbp)
	jns	.L8
	movl	$.LC22, %edi
	call	puts
	movl	$1, %edi
	call	exit
.L8:
	movq	-2912(%rbp), %rax
	movl	$35, %esi
	movq	%rax, %rdi
	call	get_format_char_number
	movzbl	%al, %eax
	movl	%eax, -2832(%rbp)
	movb	$0, -2917(%rbp)
	jmp	.L9
.L10:
	leaq	-1072(%rbp), %rax
	movl	$32, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	leaq	-2896(%rbp), %rax
	movq	%rax, %rdi
	call	reset_day_info
	leaq	-1072(%rbp), %rdx
	movq	-2912(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	get_day_info_from_overtimeTable
	movq	%rax, -2912(%rbp)
	leaq	-2896(%rbp), %rdx
	leaq	-1072(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	get_day_info_from_dayInfoBuffer
	leaq	-2896(%rbp), %rax
	movq	%rax, %rdi
	call	calc_day_overtime_info_from_base_info
	leaq	-2896(%rbp), %rdx
	leaq	-2832(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	add_dayInfo_to_overtimeInfo
	movzbl	-2917(%rbp), %eax
	addl	$1, %eax
	movb	%al, -2917(%rbp)
.L9:
	movzbl	-2917(%rbp), %edx
	movl	-2832(%rbp), %eax
	cmpl	%eax, %edx
	jb	.L10
	leaq	-2832(%rbp), %rax
	movq	%rax, %rdi
	call	calc_month_overtime_all_days
	movl	-2936(%rbp), %edx
	leaq	-2832(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	save_overtime_info
	movl	gInfoDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L11
	leaq	-2832(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	save_overtime_info
.L11:
	movl	-2932(%rbp), %eax
	movl	%eax, %edi
	call	close
	movl	-2936(%rbp), %eax
	movl	%eax, %edi
	call	close
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L12
	call	__stack_chk_fail
.L12:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	calc_over_time, .-calc_over_time
	.type	calc_month_overtime_all_days, @function
calc_month_overtime_all_days:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	movb	$0, -9(%rbp)
	movq	-8(%rbp), %rax
	movl	$0, 4(%rax)
	movq	-8(%rbp), %rax
	pxor	%xmm0, %xmm0
	movsd	%xmm0, 8(%rax)
	jmp	.L14
.L16:
	movzbl	-9(%rbp), %eax
	movq	-8(%rbp), %rcx
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$52, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L15
	movzbl	-9(%rbp), %eax
	movq	-8(%rbp), %rcx
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$56, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L15
	movq	-8(%rbp), %rax
	movl	4(%rax), %ecx
	movzbl	-9(%rbp), %eax
	movq	-8(%rbp), %rsi
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rsi, %rax
	addq	$32, %rax
	movl	(%rax), %eax
	leal	(%rcx,%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 4(%rax)
.L15:
	movzbl	-9(%rbp), %eax
	addl	$1, %eax
	movb	%al, -9(%rbp)
.L14:
	movzbl	-9(%rbp), %edx
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jb	.L16
	movq	-8(%rbp), %rax
	movl	4(%rax), %eax
	movl	%eax, %eax
	testq	%rax, %rax
	js	.L17
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rax, %xmm0
	jmp	.L18
.L17:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L18:
	movsd	.LC24(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movq	-8(%rbp), %rax
	movsd	%xmm0, 8(%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	calc_month_overtime_all_days, .-calc_month_overtime_all_days
	.type	get_format_char_number, @function
get_format_char_number:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	%esi, %eax
	movb	%al, -28(%rbp)
	movb	$0, -1(%rbp)
	jmp	.L20
.L21:
	movq	-24(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -24(%rbp)
	movzbl	(%rax), %eax
	cmpb	$35, %al
	jne	.L20
	movzbl	-1(%rbp), %eax
	addl	$1, %eax
	movb	%al, -1(%rbp)
.L20:
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L21
	movzbl	-1(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	get_format_char_number, .-get_format_char_number
	.type	reset_day_info, @function
reset_day_info:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$0, (%rax)
	movq	-8(%rbp), %rax
	movl	$0, 48(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 8(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 12(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 36(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 40(%rax)
	movq	-8(%rbp), %rax
	pxor	%xmm0, %xmm0
	movsd	%xmm0, 24(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 16(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 4(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 44(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 32(%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	reset_day_info, .-reset_day_info
	.type	reset_overtime_Info, @function
reset_overtime_Info:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	movq	-24(%rbp), %rax
	movl	$0, (%rax)
	movq	-24(%rbp), %rax
	movl	$0, 4(%rax)
	movq	-24(%rbp), %rax
	pxor	%xmm0, %xmm0
	movsd	%xmm0, 8(%rax)
	movl	$0, -4(%rbp)
	jmp	.L25
.L26:
	movl	-4(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	leaq	16(%rax), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, %rdi
	call	reset_day_info
	addl	$1, -4(%rbp)
.L25:
	cmpl	$30, -4(%rbp)
	jle	.L26
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	reset_overtime_Info, .-reset_overtime_Info
	.type	add_dayInfo_to_overtimeInfo, @function
add_dayInfo_to_overtimeInfo:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$31, %eax
	ja	.L28
	cmpq	$0, -8(%rbp)
	je	.L28
	cmpq	$0, -16(%rbp)
	jne	.L29
.L28:
	movl	$-1, %eax
	jmp	.L27
.L29:
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	movq	-16(%rbp), %rax
	movl	(%rax), %ecx
	movq	-8(%rbp), %rsi
	movl	%edx, %eax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rsi, %rax
	addq	$16, %rax
	movl	%ecx, (%rax)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	movq	-16(%rbp), %rax
	movl	12(%rax), %ecx
	movq	-8(%rbp), %rsi
	movl	%edx, %eax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rsi, %rax
	addq	$28, %rax
	movl	%ecx, (%rax)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	movq	-16(%rbp), %rax
	movl	36(%rax), %ecx
	movq	-8(%rbp), %rsi
	movl	%edx, %eax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rsi, %rax
	addq	$52, %rax
	movl	%ecx, (%rax)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	movq	-16(%rbp), %rax
	movsd	24(%rax), %xmm0
	movq	-8(%rbp), %rcx
	movl	%edx, %eax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$40, %rax
	movsd	%xmm0, (%rax)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	movq	-16(%rbp), %rax
	movl	16(%rax), %ecx
	movq	-8(%rbp), %rsi
	movl	%edx, %eax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rsi, %rax
	addq	$32, %rax
	movl	%ecx, (%rax)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	movq	-16(%rbp), %rax
	movl	8(%rax), %ecx
	movq	-8(%rbp), %rsi
	movl	%edx, %eax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rsi, %rax
	addq	$24, %rax
	movl	%ecx, (%rax)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	movq	-16(%rbp), %rax
	movl	48(%rax), %ecx
	movq	-8(%rbp), %rsi
	movl	%edx, %eax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rsi, %rax
	addq	$64, %rax
	movl	%ecx, (%rax)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	movq	-16(%rbp), %rax
	movl	4(%rax), %ecx
	movq	-8(%rbp), %rsi
	movl	%edx, %eax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rsi, %rax
	addq	$20, %rax
	movl	%ecx, (%rax)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	movq	-16(%rbp), %rax
	movl	44(%rax), %ecx
	movq	-8(%rbp), %rsi
	movl	%edx, %eax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rsi, %rax
	addq	$60, %rax
	movl	%ecx, (%rax)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	movq	-16(%rbp), %rax
	movl	32(%rax), %ecx
	movq	-8(%rbp), %rsi
	movl	%edx, %eax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rsi, %rax
	addq	$48, %rax
	movl	%ecx, (%rax)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	movq	-16(%rbp), %rax
	movl	40(%rax), %ecx
	movq	-8(%rbp), %rsi
	movl	%edx, %eax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rsi, %rax
	addq	$56, %rax
	movl	%ecx, (%rax)
.L27:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	add_dayInfo_to_overtimeInfo, .-add_dayInfo_to_overtimeInfo
	.section	.rodata
.LC25:
	.string	"w+"
	.align 8
.LC26:
	.string	"\nTotal overtime minutes:%d [hours:%lf], exclude hoilday and adjust day"
	.align 8
.LC27:
	.string	"\nDetails of each day are shown below:\n"
	.align 8
.LC28:
	.string	"\n%8s%10s%16s%12s%12s%12s%10s%12s%12s%12s%12s"
.LC29:
	.string	"Normal"
	.align 8
.LC30:
	.string	"\n%4d%16s%10d%14d%12d%10d%16lf%8d%14d%8d%16s"
.LC31:
	.string	"\n\n"
	.text
	.type	save_overtime_info, @function
save_overtime_info:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$48, %rsp
	.cfi_offset 14, -24
	.cfi_offset 13, -32
	.cfi_offset 12, -40
	.cfi_offset 3, -48
	movq	%rdi, -56(%rbp)
	movl	%esi, -60(%rbp)
	movl	$0, -44(%rbp)
	movl	-60(%rbp), %eax
	movl	$.LC25, %esi
	movl	%eax, %edi
	call	fdopen
	movq	%rax, -40(%rbp)
	movq	-56(%rbp), %rax
	movq	8(%rax), %rcx
	movq	-56(%rbp), %rax
	movl	4(%rax), %edx
	movq	-40(%rbp), %rax
	movq	%rcx, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	movl	$.LC26, %esi
	movq	%rax, %rdi
	movl	$1, %eax
	call	fprintf
	movq	-40(%rbp), %rax
	movq	%rax, %rcx
	movl	$38, %edx
	movl	$1, %esi
	movl	$.LC27, %edi
	call	fwrite
	movq	title+80(%rip), %rbx
	movq	title+72(%rip), %r11
	movq	title+64(%rip), %r10
	movq	title+56(%rip), %r9
	movq	title+48(%rip), %r8
	movq	title+40(%rip), %rdi
	movq	title+32(%rip), %rsi
	movq	title+24(%rip), %r13
	movq	title+16(%rip), %r12
	movq	title+8(%rip), %rcx
	movq	title(%rip), %rdx
	movq	-40(%rbp), %rax
	subq	$8, %rsp
	pushq	%rbx
	pushq	%r11
	pushq	%r10
	pushq	%r9
	pushq	%r8
	pushq	%rdi
	pushq	%rsi
	movq	%r13, %r9
	movq	%r12, %r8
	movl	$.LC28, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	addq	$64, %rsp
	movl	$0, -44(%rbp)
	jmp	.L32
.L35:
	movq	-56(%rbp), %rcx
	movl	-44(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$60, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	je	.L33
	movl	$.LC10, %r14d
	jmp	.L34
.L33:
	movl	$.LC29, %r14d
.L34:
	movq	-56(%rbp), %rcx
	movl	-44(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$56, %rax
	movl	(%rax), %r11d
	movq	-56(%rbp), %rcx
	movl	-44(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$48, %rax
	movl	(%rax), %r10d
	movq	-56(%rbp), %rcx
	movl	-44(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$32, %rax
	movl	(%rax), %r9d
	movq	-56(%rbp), %rcx
	movl	-44(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$40, %rax
	movq	(%rax), %rsi
	movq	-56(%rbp), %rcx
	movl	-44(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$20, %rax
	movl	(%rax), %r8d
	movq	-56(%rbp), %rcx
	movl	-44(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$52, %rax
	movl	(%rax), %edi
	movq	-56(%rbp), %rcx
	movl	-44(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$28, %rax
	movl	(%rax), %r12d
	movq	-56(%rbp), %rcx
	movl	-44(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$24, %rax
	movl	(%rax), %ebx
	movq	-56(%rbp), %rcx
	movl	-44(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$64, %rax
	movl	(%rax), %eax
	movl	%eax, %eax
	movq	weekString(,%rax,8), %rcx
	movq	-56(%rbp), %r13
	movl	-44(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%r13, %rax
	addq	$16, %rax
	movl	(%rax), %edx
	movq	-40(%rbp), %rax
	pushq	%r14
	pushq	%r11
	pushq	%r10
	pushq	%r9
	pushq	%r8
	pushq	%rdi
	movq	%rsi, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	movl	%r12d, %r9d
	movl	%ebx, %r8d
	movl	$.LC30, %esi
	movq	%rax, %rdi
	movl	$1, %eax
	call	fprintf
	addq	$48, %rsp
	addl	$1, -44(%rbp)
.L32:
	movq	-56(%rbp), %rax
	movl	(%rax), %edx
	movl	-44(%rbp), %eax
	cmpl	%eax, %edx
	ja	.L35
	movq	-40(%rbp), %rax
	movq	%rax, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movl	$.LC31, %edi
	call	fwrite
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	fclose
	nop
	leaq	-32(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	save_overtime_info, .-save_overtime_info
	.section	.rodata
.LC32:
	.string	"SATRT\n"
.LC33:
	.string	"\n%%OVERTIME-FUN-DBG:%s-%d-%s"
.LC34:
	.string	","
.LC35:
	.string	"dayInfo->dayIndex"
.LC36:
	.string	"%s:%d "
.LC37:
	.string	"dayInfo->week"
.LC38:
	.string	":"
.LC39:
	.string	"dayInfo->startTimeStamp"
.LC40:
	.string	"-"
.LC41:
	.string	"dayInfo->endTimeStamp"
.LC42:
	.string	"dayInfo->adjustFlag"
.LC43:
	.string	"\n"
.LC44:
	.string	"dayInfo->holidayFlag"
.LC45:
	.string	"END\n"
	.text
	.type	get_day_info_from_dayInfoBuffer, @function
get_day_info_from_dayInfoBuffer:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$120, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -120(%rbp)
	movq	%rsi, -128(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	$0, -96(%rbp)
	movq	$0, -104(%rbp)
	movq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	reset_day_info
	movl	gInfoDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L37
	movl	$10, %edi
	call	putchar
.L37:
	movl	gFunDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L38
	movl	$.LC32, %ecx
	movl	$242, %edx
	movl	$__FUNCTION__.3834, %esi
	movl	$.LC33, %edi
	movl	$0, %eax
	call	printf
.L38:
	movq	$0, -88(%rbp)
	leaq	-104(%rbp), %rdx
	movq	-120(%rbp), %rax
	movl	$.LC34, %esi
	movq	%rax, %rdi
	call	strtok_r
	movq	%rax, -96(%rbp)
	cmpq	$0, -96(%rbp)
	je	.L39
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-128(%rbp), %rax
	movl	%edx, (%rax)
	movl	gInfoDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L39
	movl	$62, %esi
	movl	$.LC35, %edi
	call	get_str_elements
	movq	%rax, -88(%rbp)
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-88(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC36, %edi
	movl	$0, %eax
	call	printf
.L39:
	movq	$0, -80(%rbp)
	leaq	-104(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC34, %esi
	movl	$0, %edi
	call	strtok_r
	movq	%rax, -96(%rbp)
	cmpq	$0, -96(%rbp)
	je	.L40
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-128(%rbp), %rax
	movl	%edx, 48(%rax)
	movl	gInfoDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L40
	movl	$62, %esi
	movl	$.LC37, %edi
	call	get_str_elements
	movq	%rax, -80(%rbp)
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-80(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC36, %edi
	movl	$0, %eax
	call	printf
.L40:
	movq	$0, -72(%rbp)
	leaq	-104(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC38, %esi
	movl	$0, %edi
	call	strtok_r
	movq	%rax, -96(%rbp)
	cmpq	$0, -96(%rbp)
	je	.L41
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	sall	$2, %eax
	movl	%eax, %edx
	sall	$4, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, %edx
	movq	-128(%rbp), %rax
	movl	%edx, 8(%rax)
	movl	gInfoDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L41
	movl	$62, %esi
	movl	$.LC39, %edi
	call	get_str_elements
	movq	%rax, -72(%rbp)
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-72(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC36, %edi
	movl	$0, %eax
	call	printf
.L41:
	movq	$0, -64(%rbp)
	leaq	-104(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC40, %esi
	movl	$0, %edi
	call	strtok_r
	movq	%rax, -96(%rbp)
	cmpq	$0, -96(%rbp)
	je	.L42
	movq	-128(%rbp), %rax
	movl	8(%rax), %ebx
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	leal	(%rbx,%rax), %edx
	movq	-128(%rbp), %rax
	movl	%edx, 8(%rax)
	movl	gInfoDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L42
	movl	$62, %esi
	movl	$.LC39, %edi
	call	get_str_elements
	movq	%rax, -64(%rbp)
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-64(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC36, %edi
	movl	$0, %eax
	call	printf
.L42:
	movq	$0, -56(%rbp)
	leaq	-104(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC38, %esi
	movl	$0, %edi
	call	strtok_r
	movq	%rax, -96(%rbp)
	cmpq	$0, -96(%rbp)
	je	.L43
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	sall	$2, %eax
	movl	%eax, %edx
	sall	$4, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, %edx
	movq	-128(%rbp), %rax
	movl	%edx, 12(%rax)
	movl	gInfoDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L43
	movl	$62, %esi
	movl	$.LC41, %edi
	call	get_str_elements
	movq	%rax, -56(%rbp)
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-56(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC36, %edi
	movl	$0, %eax
	call	printf
.L43:
	movq	$0, -48(%rbp)
	leaq	-104(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC34, %esi
	movl	$0, %edi
	call	strtok_r
	movq	%rax, -96(%rbp)
	cmpq	$0, -96(%rbp)
	je	.L44
	movq	-128(%rbp), %rax
	movl	12(%rax), %ebx
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	leal	(%rbx,%rax), %edx
	movq	-128(%rbp), %rax
	movl	%edx, 12(%rax)
	movl	gInfoDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L44
	movl	$62, %esi
	movl	$.LC41, %edi
	call	get_str_elements
	movq	%rax, -48(%rbp)
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-48(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC36, %edi
	movl	$0, %eax
	call	printf
.L44:
	movq	$0, -40(%rbp)
	leaq	-104(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC34, %esi
	movl	$0, %edi
	call	strtok_r
	movq	%rax, -96(%rbp)
	cmpq	$0, -96(%rbp)
	je	.L45
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-128(%rbp), %rax
	movl	%edx, 40(%rax)
	movl	gInfoDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L45
	movl	$62, %esi
	movl	$.LC42, %edi
	call	get_str_elements
	movq	%rax, -40(%rbp)
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-40(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC36, %edi
	movl	$0, %eax
	call	printf
.L45:
	movq	$0, -32(%rbp)
	leaq	-104(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC43, %esi
	movl	$0, %edi
	call	strtok_r
	movq	%rax, -96(%rbp)
	cmpq	$0, -96(%rbp)
	je	.L46
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-128(%rbp), %rax
	movl	%edx, 36(%rax)
	movl	gInfoDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L46
	movl	$62, %esi
	movl	$.LC44, %edi
	call	get_str_elements
	movq	%rax, -32(%rbp)
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC36, %edi
	movl	$0, %eax
	call	printf
.L46:
	movl	gFunDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L49
	movl	$.LC45, %ecx
	movl	$272, %edx
	movl	$__FUNCTION__.3834, %esi
	movl	$.LC33, %edi
	movl	$0, %eax
	call	printf
.L49:
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L48
	call	__stack_chk_fail
.L48:
	addq	$120, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	get_day_info_from_dayInfoBuffer, .-get_day_info_from_dayInfoBuffer
	.section	.rodata
	.align 8
.LC46:
	.string	"\n####dayIndex:%d,endTimeStamp:%d,startTimeStamp:%d, sleepTime:%dreboundTime:%d, workTimes:%d, minutes:%d, hours:%lf, holidayFlag:%d\n"
	.text
	.type	calc_day_overtime_info_from_base_info, @function
calc_day_overtime_info_from_base_info:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
	movl	gFunDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L51
	movl	$.LC32, %ecx
	movl	$280, %edx
	movl	$__FUNCTION__.3848, %esi
	movl	$.LC33, %edi
	movl	$0, %eax
	call	printf
.L51:
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	testl	%eax, %eax
	je	.L52
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	testl	%eax, %eax
	je	.L52
	movq	-24(%rbp), %rax
	movl	12(%rax), %edx
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	%eax, %edx
	jbe	.L52
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	testl	%eax, %eax
	jne	.L53
.L52:
	movq	-24(%rbp), %rax
	movl	36(%rax), %eax
	testl	%eax, %eax
	jne	.L77
	movq	-24(%rbp), %rax
	movl	$1, 44(%rax)
	jmp	.L77
.L53:
	movq	-24(%rbp), %rax
	movl	40(%rax), %eax
	testl	%eax, %eax
	jne	.L56
	movq	-24(%rbp), %rax
	movl	36(%rax), %eax
	testl	%eax, %eax
	jne	.L57
	movq	-24(%rbp), %rax
	movl	48(%rax), %eax
	testl	%eax, %eax
	je	.L57
	movq	-24(%rbp), %rax
	movl	48(%rax), %eax
	cmpl	$5, %eax
	ja	.L57
.L56:
	movl	$480, -8(%rbp)
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	$540, %eax
	ja	.L58
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	cmpl	$1079, %eax
	ja	.L59
.L58:
	movq	-24(%rbp), %rax
	movl	$1, 44(%rax)
	jmp	.L50
.L59:
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	$510, %eax
	jbe	.L60
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	$525, %eax
	jbe	.L61
	movl	$30, %edx
	jmp	.L62
.L61:
	movl	$15, %edx
.L62:
	movq	-24(%rbp), %rax
	movl	%edx, 32(%rax)
.L60:
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	cmpl	$1230, %eax
	jbe	.L63
	movq	-24(%rbp), %rax
	movl	$135, 4(%rax)
	jmp	.L65
.L63:
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	leal	-990(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, 4(%rax)
	jmp	.L65
.L57:
	movl	$0, -8(%rbp)
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	$719, %eax
	jbe	.L66
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	cmpl	$810, %eax
	ja	.L67
	movq	-24(%rbp), %rax
	movl	$1, 44(%rax)
	jmp	.L50
.L67:
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	$810, %eax
	ja	.L68
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	movl	$810, %edx
	subl	%eax, %edx
	jmp	.L69
.L68:
	movl	$0, %edx
.L69:
	movq	-24(%rbp), %rax
	movl	%edx, 4(%rax)
	jmp	.L65
.L66:
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	cmpl	$810, %eax
	ja	.L70
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	cmpl	$719, %eax
	jbe	.L71
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	leal	-720(%rax), %edx
	jmp	.L72
.L71:
	movl	$0, %edx
.L72:
	movq	-24(%rbp), %rax
	movl	%edx, 4(%rax)
	jmp	.L65
.L70:
	movq	-24(%rbp), %rax
	movl	$90, 4(%rax)
.L65:
	movq	-24(%rbp), %rax
	movl	12(%rax), %edx
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	movl	$510, %ecx
	cmpl	$510, %eax
	cmovb	%ecx, %eax
	subl	%eax, %edx
	movq	-24(%rbp), %rax
	movl	4(%rax), %eax
	subl	%eax, %edx
	movq	-24(%rbp), %rax
	movl	32(%rax), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	subl	-8(%rbp), %eax
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	movl	%edx, 16(%rax)
	movq	-24(%rbp), %rax
	movl	16(%rax), %eax
	movl	%eax, %eax
	testq	%rax, %rax
	js	.L73
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rax, %xmm0
	jmp	.L74
.L73:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L74:
	movsd	.LC24(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, 24(%rax)
	movl	gInfoDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L75
	movq	-24(%rbp), %rax
	movl	36(%rax), %r8d
	movq	-24(%rbp), %rax
	movq	24(%rax), %rsi
	movq	-24(%rbp), %rax
	movl	16(%rax), %edi
	movq	-24(%rbp), %rax
	movl	32(%rax), %r9d
	movq	-24(%rbp), %rax
	movl	4(%rax), %r10d
	movq	-24(%rbp), %rax
	movl	8(%rax), %ecx
	movq	-24(%rbp), %rax
	movl	12(%rax), %edx
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	subq	$8, %rsp
	pushq	%r8
	pushq	%rdi
	movl	-8(%rbp), %edi
	pushq	%rdi
	movq	%rsi, -32(%rbp)
	movsd	-32(%rbp), %xmm0
	movl	%r10d, %r8d
	movl	%eax, %esi
	movl	$.LC46, %edi
	movl	$1, %eax
	call	printf
	addq	$32, %rsp
.L75:
	movl	gFunDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L78
	movl	$.LC45, %ecx
	movl	$378, %edx
	movl	$__FUNCTION__.3848, %esi
	movl	$.LC33, %edi
	movl	$0, %eax
	call	printf
	nop
	jmp	.L78
.L77:
	nop
	jmp	.L50
.L78:
	nop
.L50:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	calc_day_overtime_info_from_base_info, .-calc_day_overtime_info_from_base_info
	.type	get_day_info_from_overtimeTable, @function
get_day_info_from_overtimeTable:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -8(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L80
.L82:
	nop
.L80:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L83
	movq	-16(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -16(%rbp)
	movzbl	(%rax), %eax
	cmpb	$35, %al
	jne	.L82
	jmp	.L83
.L85:
	movq	-8(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -8(%rbp)
	movq	-16(%rbp), %rdx
	leaq	1(%rdx), %rcx
	movq	%rcx, -16(%rbp)
	movzbl	(%rdx), %edx
	movb	%dl, (%rax)
.L83:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L84
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$10, %al
	jne	.L85
.L84:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L86
	movl	$0, %eax
	jmp	.L87
.L86:
	movq	-16(%rbp), %rax
.L87:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	get_day_info_from_overtimeTable, .-get_day_info_from_overtimeTable
	.type	get_str_elements, @function
get_str_elements:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	%esi, %eax
	movb	%al, -12(%rbp)
	jmp	.L89
.L91:
	movq	-8(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -8(%rbp)
	movzbl	(%rax), %eax
	cmpb	-12(%rbp), %al
	je	.L93
.L89:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L91
	jmp	.L90
.L93:
	nop
.L90:
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	get_str_elements, .-get_str_elements
	.section	.rodata
	.align 32
	.type	__FUNCTION__.3834, @object
	.size	__FUNCTION__.3834, 32
__FUNCTION__.3834:
	.string	"get_day_info_from_dayInfoBuffer"
	.align 32
	.type	__FUNCTION__.3848, @object
	.size	__FUNCTION__.3848, 38
__FUNCTION__.3848:
	.string	"calc_day_overtime_info_from_base_info"
	.align 8
.LC24:
	.long	0
	.long	1078853632
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
