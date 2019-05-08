.intel_syntax noprefix
.global main

main:
  mov rax, 0
  mov rcx, 10

_loop:
  add rax, rcx
  loop _loop

  ret
