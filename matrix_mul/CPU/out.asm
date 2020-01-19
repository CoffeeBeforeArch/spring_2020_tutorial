
base_mmul.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <base_mmul(int const*, int const*, int*, int)>:
   0:	85 c9                	test   %ecx,%ecx
   2:	0f 8e 85 00 00 00    	jle    8d <base_mmul(int const*, int const*, int*, int)+0x8d>
   8:	41 56                	push   %r14
   a:	49 89 fb             	mov    %rdi,%r11
   d:	8d 41 ff             	lea    -0x1(%rcx),%eax
  10:	41 55                	push   %r13
  12:	48 63 f9             	movslq %ecx,%rdi
  15:	41 89 ce             	mov    %ecx,%r14d
  18:	41 54                	push   %r12
  1a:	48 c1 e7 02          	shl    $0x2,%rdi
  1e:	49 89 f4             	mov    %rsi,%r12
  21:	55                   	push   %rbp
  22:	4d 8d 44 83 04       	lea    0x4(%r11,%rax,4),%r8
  27:	45 31 ed             	xor    %r13d,%r13d
  2a:	53                   	push   %rbx
  2b:	89 cd                	mov    %ecx,%ebp
  2d:	48 89 d3             	mov    %rdx,%rbx
  30:	4d 89 e2             	mov    %r12,%r10
  33:	45 31 c9             	xor    %r9d,%r9d
  36:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  3d:	00 00 00 
  40:	4c 89 d1             	mov    %r10,%rcx
  43:	4c 89 d8             	mov    %r11,%rax
  46:	31 f6                	xor    %esi,%esi
  48:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  4f:	00 
  50:	8b 10                	mov    (%rax),%edx
  52:	48 83 c0 04          	add    $0x4,%rax
  56:	0f af 11             	imul   (%rcx),%edx
  59:	48 01 f9             	add    %rdi,%rcx
  5c:	01 d6                	add    %edx,%esi
  5e:	49 39 c0             	cmp    %rax,%r8
  61:	75 ed                	jne    50 <base_mmul(int const*, int const*, int*, int)+0x50>
  63:	42 89 34 8b          	mov    %esi,(%rbx,%r9,4)
  67:	49 ff c1             	inc    %r9
  6a:	49 83 c2 04          	add    $0x4,%r10
  6e:	4c 39 cd             	cmp    %r9,%rbp
  71:	75 cd                	jne    40 <base_mmul(int const*, int const*, int*, int)+0x40>
  73:	41 ff c5             	inc    %r13d
  76:	48 01 fb             	add    %rdi,%rbx
  79:	49 01 fb             	add    %rdi,%r11
  7c:	49 01 f8             	add    %rdi,%r8
  7f:	45 39 ee             	cmp    %r13d,%r14d
  82:	75 ac                	jne    30 <base_mmul(int const*, int const*, int*, int)+0x30>
  84:	5b                   	pop    %rbx
  85:	5d                   	pop    %rbp
  86:	41 5c                	pop    %r12
  88:	41 5d                	pop    %r13
  8a:	41 5e                	pop    %r14
  8c:	c3                   	retq   
  8d:	c3                   	retq   
