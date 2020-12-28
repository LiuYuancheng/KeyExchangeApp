



all: dh_ke.c test_all.c test.c ../../lib/format_helper.c p_resolver.c  g_resolver.c
	clang++ -o test_all  test_all.c ../../lib/format_helper.c  -lcrypto  -O3 -g
	clang++ -o test  dh_ke.c test.c ../../lib/format_helper.c  -lcrypto  -O3 -g 
	clang++ -o dhsetup  dhsetup.c  dh_ke.c  -lcrypto  -lmbedcrypto -O3 -g 
	clang++ -o p_resolver  p_resolver.c  -lcrypto  -lmbedcrypto -O3 -g 
	clang++ -o g_resolver  g_resolver.c  -lcrypto  -lmbedcrypto -O3 -g 
	clang++ -o test_correctness  test_correctness.c  dh_ke.c  -lcrypto  -lmbedcrypto -O3 -g 


clean:
	rm -f test test_all 
	rm -f dhsetup
	rm -f p_resolver
	rm -f g_resolver
	rm -f test_correctness
