# KeyExchangeApp





intall NTL: https://www.shoup.net/ntl/doc/tour-unix.html

install GMP: sudo apt-get install libgmp3-dev

install GF2X: sudo apt install libgf2x-dev


install mbedTLS: sudo apt-get install -y libmbedtls-dev

install google glog: sudo apt install libgoogle-glog-dev


cd XKCP
mkdir temp
export CC='g++ -fPIC'
make generic64/libkeccak.so
cd bin/generic64
sudo cp -r libkeccak.a.headers /usr/local/include/libkeccak.so.headers
sudo cp -r libkeccak.so /usr/lib/libkeccak.so

select: For independent pk/sk



Error: 

k_resolver.c:47:2: error: no matching function for call to 'BIO_dump_fp'
        BIO_dump_fp(stdout, k, RSA_CRYPTO_PUBLICKEYBYTES);
        ^~~~~~~~~~~
/usr/include/openssl/bio.h:637:5: note: candidate function not viable: no known conversion from 'unsigned char *' to 'const char *' for 2nd argument
int BIO_dump_fp(FILE *fp, const char *s, int len);
    ^
1 error generated.
make: *** [Makefile:8: all] Error 1

Install openSSL 3.0.0

link: https://www.howtoforge.com/tutorial/how-to-install-openssl-from-source-on-linux/

or 

link: https://cloudwafer.com/blog/installing-openssl-on-ubuntu-16-04-18-04/


cd /usr/local/src/
wget https://www.openssl.org/source/openssl-3.0.0-alpha1.tar.gz

https://drive.google.com/file/d/1cFqExn21dKB7fZWrV7_q3faEqQQXCZ4o/view



error message : 

C:/Works/SingtelTw/QSG_Project/KeyExchangeApp/KeyExchangeApp/app/src/main/cpp/native-lib.cpp:112: error: undefined reference to 'CKeGateWay::ShareWith(char*, char*, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >&)'



https://stackoverflow.com/questions/22159183/android-ndk-jni-undefined-reference-to-function-defined-in-custom-header-fil