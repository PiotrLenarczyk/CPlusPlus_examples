global SomeFunction

segment .text;
SomeFunction:
	MOV eax, edi; mv input arg to eax
	ADD eax, 5	; add 5 to value at eax register
	RET

