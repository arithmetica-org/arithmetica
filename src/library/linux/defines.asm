%ifdef __MACH__
  %define Strlen_arithmetica _strlen_arithmetica
  %define Truncate _truncate
  %define CALL(func) call func
%else
  %define Strlen_arithmetica strlen_arithmetica
  %define Truncate truncate
  %define CALL(func) call func wrt ..plt
%endif