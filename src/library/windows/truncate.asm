extern strlen

section .text
global  truncate
truncate:
  ; Input:
  ;   - rcx -> char *n, the number to truncate.
  ;   - rdx -> size_t accuracy, the amount to truncate.

  ; Registers used:
  ;   - rax
  ;   - r8, rdx
  ;   - rbx
  ;   - r11, rcx
  
  push  rbx
  call  strlen
  mov   r11, rax ; rcx = strlen(n)
  inc   rdx ; increase accuracy by 1 for zeroing
  xor   eax, eax ; Set al to 0
  mov   rbx, rcx
.find_dec_loop:
  mov   r8b, byte [rbx]
  inc   rbx
  cmp   r8b, '.'
  jne   .after_if
  mov   al, 1 ; if decimal is found then set al
  jmp   .after_loop
.after_if:
  test  r8b, r8b
  jnz   .find_dec_loop
.after_loop:
  test  al, al
  jz    .return
  add   rbx, rdx
  dec   rbx
  add   rcx, r11
  cmp   rbx, rcx
  jae   .return
  mov   byte [rbx], 0
.return:
  pop   rbx
  ret