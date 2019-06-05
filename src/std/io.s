global outbyte
global inbyte

; stack:
; [esp + 8] -> byte to send
; [esp + 4] -> io port 
; esp -> return addr
outbyte:
	mov al, [esp + 8]
	mov dx, [esp + 4]
	out dx, al
	ret
	
; stack:
; [esp + 4] -> io port
; esp -> return addr
inbyte:
	mov dx, [esp + 4]
	in al, dx
	ret