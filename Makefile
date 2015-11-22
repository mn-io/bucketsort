app?=bucketsort_test

compile:
	@echo "\n>>>compile-gcc:Start>>>>>>>>>>>>>>>>>>>>"
	gcc -o out/${app} ${app}.c
	@echo ">>>compile-gcc:End>>>>>>>>>>>>>>>>>>>>>>"
run:
	@echo "\n>>>run-gcc:Start>>>>>>>>>>>>>>>>>>>>>>>>"
	@./out/${app}
	@echo "\n>>>run-gcc:End>>>>>>>>>>>>>>>>>>>>>>>>>>"
default: clean compile-gcc run-gcc

watch:
	when-changed ./${app}.c -c "make default app=${app}"

clean:
	rm -f ./${app}
