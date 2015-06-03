	.text
	.file	"test01.cpp"
	.section	.text.startup,"ax",@progbits
	.align	16, 0x90
	.type	__cxx_global_var_init,@function
__cxx_global_var_init:                  # @__cxx_global_var_init
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp0:
	.cfi_def_cfa_offset 16
.Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp2:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movabsq	$_ZStL8__ioinit, %rdi
	callq	_ZNSt8ios_base4InitC1Ev
	movabsq	$_ZNSt8ios_base4InitD1Ev, %rdi
	movabsq	$_ZStL8__ioinit, %rsi
	movabsq	$__dso_handle, %rdx
	callq	__cxa_atexit
	movl	%eax, -4(%rbp)          # 4-byte Spill
	addq	$16, %rsp
	popq	%rbp
	retq
.Ltmp3:
	.size	__cxx_global_var_init, .Ltmp3-__cxx_global_var_init
	.cfi_endproc

	.text
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp4:
	.cfi_def_cfa_offset 16
.Ltmp5:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp6:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movabsq	$_ZSt4cout, %rdi
	movabsq	$.L.str, %rsi
	movl	$0, -4(%rbp)
	callq	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, -16(%rbp)         # 8-byte Spill
	callq	omp_get_num_procs
	movq	-16(%rbp), %rdi         # 8-byte Reload
	movl	%eax, %esi
	callq	_ZNSolsEi
	movabsq	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %rsi
	movq	%rax, %rdi
	callq	_ZNSolsEPFRSoS_E
	movl	$4, %edi
	movq	%rax, -24(%rbp)         # 8-byte Spill
	callq	omp_set_num_threads
	movl	$0, -8(%rbp)
.LBB1_1:                                # =>This Inner Loop Header: Depth=1
	cmpl	$4, -8(%rbp)
	jge	.LBB1_4
# BB#2:                                 #   in Loop: Header=BB1_1 Depth=1
	callq	omp_get_thread_num
	movabsq	$_ZSt4cout, %rdi
	movl	%eax, %esi
	callq	_ZNSolsEi
	movabsq	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %rsi
	movq	%rax, %rdi
	callq	_ZNSolsEPFRSoS_E
	movq	%rax, -32(%rbp)         # 8-byte Spill
# BB#3:                                 #   in Loop: Header=BB1_1 Depth=1
	movl	-8(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -8(%rbp)
	jmp	.LBB1_1
.LBB1_4:
	movl	$0, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
.Ltmp7:
	.size	main, .Ltmp7-main
	.cfi_endproc

	.section	.text.startup,"ax",@progbits
	.align	16, 0x90
	.type	_GLOBAL__sub_I_test01.cpp,@function
_GLOBAL__sub_I_test01.cpp:              # @_GLOBAL__sub_I_test01.cpp
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp8:
	.cfi_def_cfa_offset 16
.Ltmp9:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp10:
	.cfi_def_cfa_register %rbp
	callq	__cxx_global_var_init
	popq	%rbp
	retq
.Ltmp11:
	.size	_GLOBAL__sub_I_test01.cpp, .Ltmp11-_GLOBAL__sub_I_test01.cpp
	.cfi_endproc

	.type	_ZStL8__ioinit,@object  # @_ZStL8__ioinit
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"Number of available processors: "
	.size	.L.str, 33

	.section	.init_array,"aw",@init_array
	.align	8
	.quad	_GLOBAL__sub_I_test01.cpp

	.ident	"Ubuntu clang version 3.5.2-0ubuntu1 (tags/RELEASE_352/final) (based on LLVM 3.5.2)"
	.section	".note.GNU-stack","",@progbits
