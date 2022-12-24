extern strlen

section .text
global  truncate
truncate:
  ; Input:
  ;   - rdi -> char *n, the number to truncate.
  ;   - rsi -> size_t accuracy, the amount to truncate.

  ; Registers used:
  ;   - rax
  ;   - rcx
  ;   - rbx
  ;   - rdx
  
  push  rbx
  call  strlen
  mov   rcx, rax ; rcx = strlen(n)
  inc   rsi ; increase accuracy by 1 for zeroing
  xor   eax, eax ; Set al to 0
  mov   rbx, rdi
.find_dec_loop:
  mov   dl, byte [rbx]
  inc   rbx
  cmp   dl, '.'
  jne   .after_if
  mov   al, 1 ; if decimal is found then set al
  jmp   .after_loop
.after_if:
  test  dl, dl
  jnz   .find_dec_loop
.after_loop:
  test  al, al
  jz    .return
  add   rbx, rsi
  dec   rbx
  add   rdi, rcx
  cmp   rbx, rdi
  jae   .return
  mov   byte [rbx], 0
.return:
  pop   rbx
  ret