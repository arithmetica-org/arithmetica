%include "defines.asm"

section .text
global Strlen_arithmetica
Strlen_arithmetica:
  ; Input:
  ;   - char *str -> rdi

  ;   - rcx

  xor    ecx, ecx
  mov    rax, -1
.loop:
  inc    rax
  mov    cl, byte[rdi + rax]
  test   cl, cl
  jnz    .loop
  ret