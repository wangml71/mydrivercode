all:tcnbr tcbr tcnbw tcbw tcsl tcsi tcat tcsc tcled tckey hello

ifeq ($(ARCH),arm)
CC := arm-linux-gnueabi-gcc
else
CC := gcc
endif
tcnbr:testmychar_nonblockread.c
	$(CC) testmychar_nonblockread.c -o tcnbr
tcbr:testmychar_blockread.c
	$(CC) testmychar_blockread.c -o tcbr
tcnbw:testmychar_nonblockwrite.c
	$(CC) testmychar_nonblockwrite.c -o tcnbw
tcbw:testmychar_blockwrite.c
	$(CC) testmychar_blockwrite.c -o tcbw
tcsl:testmychar_select.c
	$(CC) testmychar_select.c -o tcsl
tcsi:testmychar_signal.c
	$(CC) testmychar_signal.c -o tcsi
tcat:testmychar_atomic.c
	$(CC) testmychar_atomic.c -o tcat
tcsc:testmychar_second.c
	$(CC) testmychar_second.c -o tcsc
tcled:testmychar_led.c
	$(CC) testmychar_led.c -o tcled
tckey:testmychar_key.c
	$(CC) testmychar_key.c -o tckey
hello:syscall_hello.c
	$(CC) syscall_hello.c -o hello

.PHONY:clean
clean:
	rm tc*
