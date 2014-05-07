cLogMerge: logmerge.o logger.o scanner.o
	gcc -Wall -g -o cLogMerge logmerge.o logger.o scanner.o
logmerge.o: logmerge.c logger.c
	gcc -Wall -c logmerge.c logger.c
logger.o: logger.c scanner.c
	gcc -Wall -c logger.c scanner.c
scanner.o: scanner.c
	gcc -Wall -c scanner.c
clean: 
	rm -rf *.o *.dSYM
