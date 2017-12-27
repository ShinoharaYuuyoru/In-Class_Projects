.386
.model	flat,stdcall
.data
.code
main	proc	C	a:DWORD,	b:DWORD
mov eax, b
add eax, a
	ret
end	main