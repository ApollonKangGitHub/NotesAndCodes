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
	.string	"SleepTime"
.LC5:
	.string	"Hours"
.LC6:
	.string	"Minutes"
.LC7:
	.string	"Rebound"
.LC8:
	.string	"Holiday"
.LC9:
	.string	"adjust"
.LC10:
	.string	"leave"
.LC11:
	.string	"Status"
	.data
	.align 32
	.type	title, @object
	.size	title, 96
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
	.quad	.LC11
	.section	.rodata
.LC12:
	.string	"Error"
.LC13:
	.string	"Monday"
.LC14:
	.string	"Tuesday"
.LC15:
	.string	"Wednesday"
.LC16:
	.string	"Thursday"
.LC17:
	.string	"Friday"
.LC18:
	.string	"Saturday"
.LC19:
	.string	"Sunday"
.LC20:
	.string	"Invalid"
	.data
	.align 32
	.type	weekString, @object
	.size	weekString, 72
weekString:
	.quad	.LC12
	.quad	.LC13
	.quad	.LC14
	.quad	.LC15
	.quad	.LC16
	.quad	.LC17
	.quad	.LC18
	.quad	.LC19
	.quad	.LC20
	.section	.rodata
	.align 8
.LC21:
	.string	"\nError:The number of parameters error!\nFormat:%s fileName \n"
	.align 8
.LC22:
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
	movl	$.LC21, %edi
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
	movl	$.LC22, %edi
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
	.align 8
.LC23:
	.string	"\nError file size = %d is too big!\n"
.LC24:
	.string	"\nRead file failure!"
.LC25:
	.string	"\nError days is %d!"
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
	movb	$0, -2919(%rbp)
	leaq	-1040(%rbp), %rax
	movq	%rax, -2912(%rbp)
	movq	$0, -2904(%rbp)
	movw	$0, -2918(%rbp)
	movl	-2932(%rbp), %eax
	movl	$2, %edx
	movl	$0, %esi
	movl	%eax, %edi
	call	lseek
	movw	%ax, -2918(%rbp)
	movl	-2932(%rbp), %eax
	movl	$0, %edx
	movl	$0, %esi
	movl	%eax, %edi
	call	lseek
	cmpw	$1023, -2918(%rbp)
	jbe	.L8
	movzwl	-2918(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC23, %edi
	movl	$0, %eax
	call	printf
	jmp	.L9
.L8:
	leaq	-2832(%rbp), %rax
	movq	%rax, %rdi
	call	reset_overtime_Info
	movzwl	-2918(%rbp), %edx
	movq	-2912(%rbp), %rcx
	movl	-2932(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read
	movl	%eax, -2916(%rbp)
	cmpl	$0, -2916(%rbp)
	jns	.L10
	movl	$.LC24, %edi
	call	puts
	jmp	.L9
.L10:
	movq	-2912(%rbp), %rax
	movl	$35, %esi
	movq	%rax, %rdi
	call	get_format_char_number
	movzbl	%al, %eax
	movl	%eax, -2832(%rbp)
	movl	-2832(%rbp), %eax
	cmpl	$31, %eax
	jbe	.L11
	movl	-2832(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC25, %edi
	movl	$0, %eax
	call	printf
	jmp	.L9
.L11:
	movb	$0, -2919(%rbp)
	jmp	.L12
.L13:
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
	movzbl	-2919(%rbp), %eax
	addl	$1, %eax
	movb	%al, -2919(%rbp)
.L12:
	movzbl	-2919(%rbp), %edx
	movl	-2832(%rbp), %eax
	cmpl	%eax, %edx
	jb	.L13
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
	je	.L9
	leaq	-2832(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	save_overtime_info
.L9:
	movl	-2932(%rbp), %eax
	movl	%eax, %edi
	call	close
	movl	-2936(%rbp), %eax
	movl	%eax, %edi
	call	close
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L14
	call	__stack_chk_fail
.L14:
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
	movq	-8(%rbp), %rax
	movl	$0, (%rax)
	jmp	.L16
.L18:
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
	jne	.L17
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
	movzbl	-9(%rbp), %eax
	movq	-8(%rbp), %rcx
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$32, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	je	.L17
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, (%rax)
.L17:
	movzbl	-9(%rbp), %eax
	addl	$1, %eax
	movb	%al, -9(%rbp)
.L16:
	cmpb	$30, -9(%rbp)
	jbe	.L18
	movq	-8(%rbp), %rax
	movl	4(%rax), %eax
	movl	%eax, %eax
	testq	%rax, %rax
	js	.L19
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rax, %xmm0
	jmp	.L20
.L19:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L20:
	movsd	.LC27(%rip), %xmm1
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
	movb	$0, -9(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	.L22
.L23:
	movq	-8(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -8(%rbp)
	movzbl	(%rax), %eax
	cmpb	$35, %al
	jne	.L22
	movzbl	-9(%rbp), %eax
	addl	$1, %eax
	movb	%al, -9(%rbp)
.L22:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L23
	movzbl	-9(%rbp), %eax
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
	movl	$8, 52(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 8(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 12(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 40(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 44(%rax)
	movq	-8(%rbp), %rax
	pxor	%xmm0, %xmm0
	movsd	%xmm0, 24(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 16(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 4(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 48(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 32(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 36(%rax)
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
	jmp	.L27
.L28:
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
.L27:
	cmpl	$30, -4(%rbp)
	jle	.L28
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
	ja	.L30
	cmpq	$0, -8(%rbp)
	je	.L30
	cmpq	$0, -16(%rbp)
	jne	.L31
.L30:
	movl	$-1, %eax
	jmp	.L29
.L31:
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
	movl	52(%rax), %ecx
	movq	-8(%rbp), %rsi
	movl	%edx, %eax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rsi, %rax
	addq	$68, %rax
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
.L29:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	add_dayInfo_to_overtimeInfo, .-add_dayInfo_to_overtimeInfo
	.section	.rodata
.LC28:
	.string	"w+"
	.align 8
.LC29:
	.string	"\nTotal overtime days[%d] Total minutes:%d [hours:%lf], exclude hoilday day"
	.align 8
.LC30:
	.string	"\nDetails of each day are shown below:\n"
	.align 8
.LC31:
	.string	"\n%8s%10s%16s%12s%12s%10s%12s%10s%10s%10s%8s%10s"
.LC32:
	.string	"Exception"
.LC33:
	.string	"Normal"
	.align 8
.LC34:
	.string	"\n%4d%16s%10d%14d%10d%16lf%8d%10d%10d%10d%8d%12s"
.LC35:
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
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rdi, -72(%rbp)
	movl	%esi, -76(%rbp)
	movl	$0, -60(%rbp)
	movl	-76(%rbp), %eax
	movl	$.LC28, %esi
	movl	%eax, %edi
	call	fdopen
	movq	%rax, -56(%rbp)
	movq	-72(%rbp), %rax
	movq	8(%rax), %rsi
	movq	-72(%rbp), %rax
	movl	4(%rax), %ecx
	movq	-72(%rbp), %rax
	movl	(%rax), %edx
	movq	-56(%rbp), %rax
	movq	%rsi, -88(%rbp)
	movsd	-88(%rbp), %xmm0
	movl	$.LC29, %esi
	movq	%rax, %rdi
	movl	$1, %eax
	call	fprintf
	movq	-56(%rbp), %rax
	movq	%rax, %rcx
	movl	$38, %edx
	movl	$1, %esi
	movl	$.LC30, %edi
	call	fwrite
	movq	title+88(%rip), %r12
	movq	title+80(%rip), %rbx
	movq	title+72(%rip), %r11
	movq	title+64(%rip), %r10
	movq	title+56(%rip), %r9
	movq	title+48(%rip), %r8
	movq	title+40(%rip), %rdi
	movq	title+32(%rip), %rsi
	movq	title+24(%rip), %r14
	movq	title+16(%rip), %r13
	movq	title+8(%rip), %rcx
	movq	title(%rip), %rdx
	movq	-56(%rbp), %rax
	pushq	%r12
	pushq	%rbx
	pushq	%r11
	pushq	%r10
	pushq	%r9
	pushq	%r8
	pushq	%rdi
	pushq	%rsi
	movq	%r14, %r9
	movq	%r13, %r8
	movl	$.LC31, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	addq	$64, %rsp
	movl	$0, -60(%rbp)
	jmp	.L34
.L37:
	movq	-72(%rbp), %rcx
	movl	-60(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$64, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	je	.L35
	movl	$.LC32, %r15d
	jmp	.L36
.L35:
	movl	$.LC33, %r15d
.L36:
	movq	-72(%rbp), %rcx
	movl	-60(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$52, %rax
	movl	(%rax), %ebx
	movq	-72(%rbp), %rcx
	movl	-60(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$60, %rax
	movl	(%rax), %r11d
	movq	-72(%rbp), %rcx
	movl	-60(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$56, %rax
	movl	(%rax), %r10d
	movq	-72(%rbp), %rcx
	movl	-60(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$48, %rax
	movl	(%rax), %r9d
	movq	-72(%rbp), %rcx
	movl	-60(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$32, %rax
	movl	(%rax), %r8d
	movq	-72(%rbp), %rcx
	movl	-60(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$40, %rax
	movq	(%rax), %rsi
	movq	-72(%rbp), %rcx
	movl	-60(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$20, %rax
	movl	(%rax), %edi
	movq	-72(%rbp), %rcx
	movl	-60(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$28, %rax
	movl	(%rax), %r13d
	movq	-72(%rbp), %rcx
	movl	-60(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$24, %rax
	movl	(%rax), %r12d
	movq	-72(%rbp), %rcx
	movl	-60(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%rcx, %rax
	addq	$68, %rax
	movl	(%rax), %eax
	movl	%eax, %eax
	movq	weekString(,%rax,8), %rcx
	movq	-72(%rbp), %r14
	movl	-60(%rbp), %eax
	cltq
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	addq	%r14, %rax
	addq	$16, %rax
	movl	(%rax), %edx
	movq	-56(%rbp), %rax
	subq	$8, %rsp
	pushq	%r15
	pushq	%rbx
	pushq	%r11
	pushq	%r10
	pushq	%r9
	pushq	%r8
	pushq	%rdi
	movq	%rsi, -88(%rbp)
	movsd	-88(%rbp), %xmm0
	movl	%r13d, %r9d
	movl	%r12d, %r8d
	movl	$.LC34, %esi
	movq	%rax, %rdi
	movl	$1, %eax
	call	fprintf
	addq	$64, %rsp
	addl	$1, -60(%rbp)
.L34:
	cmpl	$30, -60(%rbp)
	jle	.L37
	movq	-56(%rbp), %rax
	movq	%rax, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movl	$.LC35, %edi
	call	fwrite
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	fclose
	nop
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	save_overtime_info, .-save_overtime_info
	.section	.rodata
.LC36:
	.string	"SATRT\n"
.LC37:
	.string	"\n%%OVERTIME-FUN-DBG:%s-%d-%s"
.LC38:
	.string	","
.LC39:
	.string	"dayInfo->dayIndex"
.LC40:
	.string	"%s:%d "
.LC41:
	.string	"dayInfo->week"
.LC42:
	.string	":"
.LC43:
	.string	"dayInfo->startTimeStamp"
.LC44:
	.string	"-"
.LC45:
	.string	"dayInfo->endTimeStamp"
.LC46:
	.string	"dayInfo->adjustFlag"
.LC47:
	.string	"dayInfo->holidayFlag"
.LC48:
	.string	"\n"
.LC49:
	.string	"dayInfo->leaveFlag"
.LC50:
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
	movq	$0, -104(%rbp)
	movq	$0, -112(%rbp)
	movq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	reset_day_info
	movl	gInfoDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L39
	movl	$10, %edi
	call	putchar
.L39:
	movl	gFunDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L40
	movl	$.LC36, %ecx
	movl	$279, %edx
	movl	$__FUNCTION__.3838, %esi
	movl	$.LC37, %edi
	movl	$0, %eax
	call	printf
.L40:
	movq	$0, -96(%rbp)
	leaq	-112(%rbp), %rdx
	movq	-120(%rbp), %rax
	movl	$.LC38, %esi
	movq	%rax, %rdi
	call	strtok_r
	movq	%rax, -104(%rbp)
	cmpq	$0, -104(%rbp)
	je	.L41
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-128(%rbp), %rax
	movl	%edx, (%rax)
	movl	gInfoDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L41
	movl	$62, %esi
	movl	$.LC39, %edi
	call	get_str_elements
	movq	%rax, -96(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-96(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC40, %edi
	movl	$0, %eax
	call	printf
.L41:
	movq	$0, -88(%rbp)
	leaq	-112(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC38, %esi
	movl	$0, %edi
	call	strtok_r
	movq	%rax, -104(%rbp)
	cmpq	$0, -104(%rbp)
	je	.L42
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-128(%rbp), %rax
	movl	%edx, 52(%rax)
	movl	gInfoDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L42
	movl	$62, %esi
	movl	$.LC41, %edi
	call	get_str_elements
	movq	%rax, -88(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-88(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC40, %edi
	movl	$0, %eax
	call	printf
.L42:
	movq	$0, -80(%rbp)
	leaq	-112(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC42, %esi
	movl	$0, %edi
	call	strtok_r
	movq	%rax, -104(%rbp)
	cmpq	$0, -104(%rbp)
	je	.L43
	movq	-104(%rbp), %rax
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
	je	.L43
	movl	$62, %esi
	movl	$.LC43, %edi
	call	get_str_elements
	movq	%rax, -80(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-80(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC40, %edi
	movl	$0, %eax
	call	printf
.L43:
	movq	$0, -72(%rbp)
	leaq	-112(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC44, %esi
	movl	$0, %edi
	call	strtok_r
	movq	%rax, -104(%rbp)
	cmpq	$0, -104(%rbp)
	je	.L44
	movq	-128(%rbp), %rax
	movl	8(%rax), %ebx
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	leal	(%rbx,%rax), %edx
	movq	-128(%rbp), %rax
	movl	%edx, 8(%rax)
	movl	gInfoDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L44
	movl	$62, %esi
	movl	$.LC43, %edi
	call	get_str_elements
	movq	%rax, -72(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-72(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC40, %edi
	movl	$0, %eax
	call	printf
.L44:
	movq	$0, -64(%rbp)
	leaq	-112(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC42, %esi
	movl	$0, %edi
	call	strtok_r
	movq	%rax, -104(%rbp)
	cmpq	$0, -104(%rbp)
	je	.L45
	movq	-104(%rbp), %rax
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
	je	.L45
	movl	$62, %esi
	movl	$.LC45, %edi
	call	get_str_elements
	movq	%rax, -64(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-64(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC40, %edi
	movl	$0, %eax
	call	printf
.L45:
	movq	$0, -56(%rbp)
	leaq	-112(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC38, %esi
	movl	$0, %edi
	call	strtok_r
	movq	%rax, -104(%rbp)
	cmpq	$0, -104(%rbp)
	je	.L46
	movq	-128(%rbp), %rax
	movl	12(%rax), %ebx
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	leal	(%rbx,%rax), %edx
	movq	-128(%rbp), %rax
	movl	%edx, 12(%rax)
	movl	gInfoDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L46
	movl	$62, %esi
	movl	$.LC45, %edi
	call	get_str_elements
	movq	%rax, -56(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-56(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC40, %edi
	movl	$0, %eax
	call	printf
.L46:
	movq	$0, -48(%rbp)
	leaq	-112(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC38, %esi
	movl	$0, %edi
	call	strtok_r
	movq	%rax, -104(%rbp)
	cmpq	$0, -104(%rbp)
	je	.L47
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-128(%rbp), %rax
	movl	%edx, 44(%rax)
	movl	gInfoDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L47
	movl	$62, %esi
	movl	$.LC46, %edi
	call	get_str_elements
	movq	%rax, -48(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-48(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC40, %edi
	movl	$0, %eax
	call	printf
.L47:
	movq	$0, -40(%rbp)
	leaq	-112(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC38, %esi
	movl	$0, %edi
	call	strtok_r
	movq	%rax, -104(%rbp)
	cmpq	$0, -104(%rbp)
	je	.L48
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-128(%rbp), %rax
	movl	%edx, 40(%rax)
	movl	gInfoDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L48
	movl	$62, %esi
	movl	$.LC47, %edi
	call	get_str_elements
	movq	%rax, -40(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-40(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC40, %edi
	movl	$0, %eax
	call	printf
.L48:
	movq	$0, -32(%rbp)
	leaq	-112(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC48, %esi
	movl	$0, %edi
	call	strtok_r
	movq	%rax, -104(%rbp)
	cmpq	$0, -104(%rbp)
	je	.L49
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-128(%rbp), %rax
	movl	%edx, 36(%rax)
	movl	gInfoDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L49
	movl	$62, %esi
	movl	$.LC49, %edi
	call	get_str_elements
	movq	%rax, -32(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, %edx
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC40, %edi
	movl	$0, %eax
	call	printf
.L49:
	movl	gFunDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L52
	movl	$.LC50, %ecx
	movl	$313, %edx
	movl	$__FUNCTION__.3838, %esi
	movl	$.LC37, %edi
	movl	$0, %eax
	call	printf
.L52:
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L51
	call	__stack_chk_fail
.L51:
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
.LC51:
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
	movl	$0, -12(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
	movl	gFunDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L54
	movl	$.LC36, %ecx
	movl	$322, %edx
	movl	$__FUNCTION__.3854, %esi
	movl	$.LC37, %edi
	movl	$0, %eax
	call	printf
.L54:
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	testl	%eax, %eax
	je	.L55
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	testl	%eax, %eax
	je	.L55
	movq	-24(%rbp), %rax
	movl	12(%rax), %edx
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	%eax, %edx
	jbe	.L55
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	testl	%eax, %eax
	jne	.L56
.L55:
	movq	-24(%rbp), %rax
	movl	40(%rax), %eax
	testl	%eax, %eax
	jne	.L88
	movq	-24(%rbp), %rax
	movl	44(%rax), %eax
	testl	%eax, %eax
	jne	.L88
	movq	-24(%rbp), %rax
	movl	52(%rax), %eax
	cmpl	$5, %eax
	ja	.L88
	movq	-24(%rbp), %rax
	movl	$1, 48(%rax)
	jmp	.L88
.L56:
	movq	-24(%rbp), %rax
	movl	36(%rax), %eax
	testl	%eax, %eax
	je	.L59
	movq	-24(%rbp), %rax
	movl	$510, 8(%rax)
.L59:
	movq	-24(%rbp), %rax
	movl	44(%rax), %eax
	testl	%eax, %eax
	jne	.L60
	movq	-24(%rbp), %rax
	movl	40(%rax), %eax
	testl	%eax, %eax
	jne	.L61
	movq	-24(%rbp), %rax
	movl	52(%rax), %eax
	testl	%eax, %eax
	je	.L61
	movq	-24(%rbp), %rax
	movl	52(%rax), %eax
	cmpl	$5, %eax
	ja	.L61
.L60:
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	$540, %eax
	ja	.L62
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	cmpl	$1079, %eax
	ja	.L63
.L62:
	movq	-24(%rbp), %rax
	movl	$1, 48(%rax)
	jmp	.L53
.L63:
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	$510, %eax
	jbe	.L64
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	$525, %eax
	ja	.L65
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	cmpl	$1139, %eax
	ja	.L66
.L65:
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	$525, %eax
	jbe	.L67
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	cmpl	$1155, %eax
	jbe	.L67
.L66:
	movq	-24(%rbp), %rax
	movl	$0, 48(%rax)
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	cmpl	$1229, %eax
	ja	.L64
	jmp	.L53
.L67:
	movq	-24(%rbp), %rax
	movl	$1, 48(%rax)
	jmp	.L53
.L64:
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	$510, %eax
	jbe	.L69
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	$525, %eax
	jbe	.L70
	movl	$30, %edx
	jmp	.L71
.L70:
	movl	$15, %edx
.L71:
	movq	-24(%rbp), %rax
	movl	%edx, 32(%rax)
.L69:
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	cmpl	$1230, %eax
	ja	.L72
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	leal	-990(%rax), %edx
	jmp	.L73
.L72:
	movl	$135, %edx
.L73:
	movq	-24(%rbp), %rax
	movl	%edx, 4(%rax)
	movq	-24(%rbp), %rax
	movl	32(%rax), %eax
	testl	%eax, %eax
	je	.L74
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	movl	$990, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	jmp	.L75
.L74:
	movl	$480, %eax
.L75:
	movl	%eax, -12(%rbp)
	jmp	.L76
.L61:
	movl	$0, -12(%rbp)
	movq	-24(%rbp), %rax
	movl	$0, 32(%rax)
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	$719, %eax
	jbe	.L77
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	cmpl	$810, %eax
	ja	.L78
	movq	-24(%rbp), %rax
	movl	$1, 48(%rax)
	jmp	.L53
.L78:
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	$810, %eax
	ja	.L79
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	movl	$810, %edx
	subl	%eax, %edx
	jmp	.L80
.L79:
	movl	$0, %edx
.L80:
	movq	-24(%rbp), %rax
	movl	%edx, 4(%rax)
	jmp	.L76
.L77:
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	cmpl	$810, %eax
	ja	.L81
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	cmpl	$719, %eax
	jbe	.L82
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	leal	-720(%rax), %edx
	jmp	.L83
.L82:
	movl	$0, %edx
.L83:
	movq	-24(%rbp), %rax
	movl	%edx, 4(%rax)
	jmp	.L76
.L81:
	movq	-24(%rbp), %rax
	movl	$90, 4(%rax)
.L76:
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	movl	$510, %edx
	cmpl	$510, %eax
	cmovb	%edx, %eax
	movl	%eax, -4(%rbp)
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	subl	-4(%rbp), %eax
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	movl	4(%rax), %eax
	subl	%eax, %edx
	movq	-24(%rbp), %rax
	movl	32(%rax), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	subl	-12(%rbp), %eax
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	movl	%edx, 16(%rax)
	movq	-24(%rbp), %rax
	movl	16(%rax), %eax
	movl	%eax, %eax
	testq	%rax, %rax
	js	.L84
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rax, %xmm0
	jmp	.L85
.L84:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L85:
	movsd	.LC27(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, 24(%rax)
	movl	gInfoDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L86
	movq	-24(%rbp), %rax
	movl	40(%rax), %r8d
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
	movl	-12(%rbp), %edi
	pushq	%rdi
	movq	%rsi, -32(%rbp)
	movsd	-32(%rbp), %xmm0
	movl	%r10d, %r8d
	movl	%eax, %esi
	movl	$.LC51, %edi
	movl	$1, %eax
	call	printf
	addq	$32, %rsp
.L86:
	movl	gFunDbgFlag(%rip), %eax
	testl	%eax, %eax
	je	.L89
	movl	$.LC50, %ecx
	movl	$444, %edx
	movl	$__FUNCTION__.3854, %esi
	movl	$.LC37, %edi
	movl	$0, %eax
	call	printf
	nop
	jmp	.L89
.L88:
	nop
	jmp	.L53
.L89:
	nop
.L53:
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
	jmp	.L91
.L93:
	nop
.L91:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L94
	movq	-16(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -16(%rbp)
	movzbl	(%rax), %eax
	cmpb	$35, %al
	jne	.L93
	jmp	.L94
.L96:
	movq	-8(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -8(%rbp)
	movq	-16(%rbp), %rdx
	leaq	1(%rdx), %rcx
	movq	%rcx, -16(%rbp)
	movzbl	(%rdx), %edx
	movb	%dl, (%rax)
.L94:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L95
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$10, %al
	jne	.L96
.L95:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L97
	movl	$0, %eax
	jmp	.L98
.L97:
	movq	-16(%rbp), %rax
.L98:
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
	jmp	.L100
.L102:
	movq	-8(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -8(%rbp)
	movzbl	(%rax), %eax
	cmpb	-12(%rbp), %al
	je	.L104
.L100:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L102
	jmp	.L101
.L104:
	nop
.L101:
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	get_str_elements, .-get_str_elements
	.section	.rodata
	.align 32
	.type	__FUNCTION__.3838, @object
	.size	__FUNCTION__.3838, 32
__FUNCTION__.3838:
	.string	"get_day_info_from_dayInfoBuffer"
	.align 32
	.type	__FUNCTION__.3854, @object
	.size	__FUNCTION__.3854, 38
__FUNCTION__.3854:
	.string	"calc_day_overtime_info_from_base_info"
	.align 8
.LC27:
	.long	0
	.long	1078853632
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
