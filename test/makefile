output: crc32_test_0.o crc32.o;\
    gcc crc32_test_0.o crc32.o -o output;

# edit : crc32_test_0.o crc32.o;\
	# gcc -o edit crc32_test_0.o crc32.o;

crc32_test_0.o : crc32_test_0.c;\
    gcc -c crc32_test_0.c;
crc32.o : ../crc32.c;\
	gcc -c ../crc32.c;

clean :;\
    rm crc32_test_0.o crc32.o;
