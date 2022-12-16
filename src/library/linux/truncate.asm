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
  sete  al ; if decimal is found then set al
  test  al, al
  jnz   .after_loop
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
  xor   eax, eax
  mov   byte [rbx], al
.return:
  pop   rbx
  ret