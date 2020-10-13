MPATH=./zew/riscv-mingw/bin

GAS=$(MPATH)/riscv64-unknown-elf-as.exe
GLD=$(MPATH)/riscv64-unknown-elf-ld.exe
GOBJDUMP=$(MPATH)/riscv64-unknown-elf-objdump.exe
GOBJCOPY=$(MPATH)/riscv64-unknown-elf-objcopy.exe
GREADELF=$(MPATH)/riscv64-unknown-elf-readelf.exe

LD_OPTIONS=-nostartfiles 






.PHONY: all
all: ./exe/main ./exe/maindb test

./exe/main: main.c input_output.c instruction.c processor.c
	clang input_output.c instruction.c processor.c main.c -o ./exe/main
	@ echo "\e[01m kompilacja \e[32m main \e[39mprzebiegła pomyślnie\e[00m"
./exe/maindb: main.c input_output.c instruction.c processor.c
	clang input_output.c instruction.c processor.c main.c -g -o ./exe/maindb
	@ echo "\e[01m kompilacja \e[32m maindb \e[39m przebiegła pomyślnie\e[00m"



exe/instruction_test: testbench/instruction_testbench.c
	clang++ testbench/instruction_testbench.c instruction.c  -I ./  -o exe/instruction_test


.PHONY: clear

.PHONY: clean

clear:clean

clean:
	rm ./exe/* || echo " "

.PHONY: test

.PHONY: fast
#szybka kompilacja i uruchomienie podstawowych podzespołów

#uruchomienie testów
test: ./exe/main exe/instruction_test ./exe/maindb
	./exe/main -code ./iob/codetest 
	./exe/main -codeb ./iob/maincode.bin -din ./iob/maindata.bin || echo " "
	./exe/main -codeb ./iob/ngsfcode.bin -din ./iob/ngsfdata.bin || ./exe/main -codeb ./iob/ngsfcode.bin  || echo " "
	echo "\e[41m\e[01m !!!\e[00m"
	./exe/maindb -codeb ./iob/testluicode.bin 
	#./main -r
	#./main -w -r
	#./exe/instruction_test || echo " "

#%.a:%.c
#	cat $? | less

.PRECIOUS:./iob/%data.bin
.PRECIOUS:./iob/%code.bin
.PRECIOUS:./iopl/%.lst
.PRECIOUS:./iopl/%elf.lst
.PRECIOUS:./iopl/%_ps
.PRECIOUS:./iopl/%.o
.PRECIOUS:./iocmp/testlui2_q


%.asmc: ./iopl/%.lst ./iopl/%elf.lst ./iob/%code.bin  ./iob/%data.bin 
	echo " " >$@
./iob/%data.bin: ./iopl/%_ps
	wine $(GOBJCOPY) -j ".data" -O binary $? $@
	@ echo "\e[01m wygenerowanie \e[32m" $@ " \e[39m przebiegło pomyślnie [6/6]\e[00m"
./iob/%code.bin: ./iopl/%_ps
	wine $(GOBJCOPY) -j ".text" -O binary $? $@
	@ echo "\e[01m wygenerowanie \e[32m" $@ " \e[39m przebiegło pomyślnie [5/6]\e[00m"
./iopl/%elf.lst: ./iopl/%_ps
	wine $(GREADELF) -a $? > $@
	@ echo "\e[01m wygenerowanie \e[32m" $@ " \e[39m przebiegło pomyślnie [4/6]\e[00m"
./iopl/%.lst: ./iopl/%_ps
	wine $(GOBJDUMP) -DxS $? > $@
	@ echo "\e[01m wygenerowanie \e[32m" $@ " \e[39m przebiegło pomyślnie [3/6]\e[00m"
./iopl/%_ps: ./iopl/%.o
	wine $(GLD) $(LD_OPTIONS) -Tlinker.ld $? -o $@
	@ echo "\e[01m wygenerowanie \e[32m" $@ " \e[39m przebiegło pomyślnie [2/6]\e[00m"

./iopl/%.o: ./ioasm/%.s
	wine $(GAS) $? -o $@
	@ echo "\e[01m wygenerowanie \e[32m" $@ " \e[39m przebiegło pomyślnie [1/6]\e[00m"


.PHONY: ASM
.PHONY:ASM2

ASM: ./exe/main testlui2.asmc testaddi1.asmc 
	./exe/main -codeb ./iob/testlui2code.bin -regoutb ./iocmp/testlui2_q > /dev/null
	tail -c+5 ./iocmp/testlui2_q > ./iocmp/testlui2_q2 
	(cmp ./iocmp/testlui2_q2 ./iocmp/testlui2_p -l && echo "lui: \e[42mPASS\e[00m") || echo "\nlui:\e[41mFAIL\e[00m" 
	./exe/main -codeb ./iob/testaddi1code.bin -regoutb ./iocmp/testaddi1_q > /dev/null
	tail -c+5 ./iocmp/testaddi1_q > ./iocmp/testaddi1_q2 
	(cmp ./iocmp/testaddi1_q2 ./iocmp/testaddi1_p -l && echo "addi: \e[42mPASS\e[00m") || echo "\naddi:\e[41mFAIL\e[00m" 

ASM2:./exe/main 
	
	
	
#.PHONY: AASM

#AASM: *.asmc











