test: hid-tests
hid-tests: $(addprefix hid-test-,SIMPLE ADVANCED MOUSE REMOTE_CONTROL UNITS UPS)

hid-test-%: hid_def.c
	@gcc -c -I../include -DHID_TEST_$* -o $@.o $<
	@objcopy -O binary -j .rodata $@.o $@.bin
	@echo Binary of $* report descriptor:
	@hd $@.bin
	@hidrd-convert -i natv -o spec $@.bin $@.txt
	@echo Text of $* report descriptor:
	@cat $@.txt
	@rm -f $@.o $@.bin $@.txt
