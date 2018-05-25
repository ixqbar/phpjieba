all: demo
demo: libcjieba.a
	gcc -O2 -o demo demo.c -L./lib -lcjieba -lstdc++ -lm
libcjieba.a:
	g++ -O2 -o lib/cjieba.o -c -DLOGGING_LEVEL=LL_WARNING -I./deps/ include/jieba.cpp
	g++ -O2 -fPIC -o lib/libcjieba.so -c -DLOGGING_LEVEL=LL_WARNING -I./deps/ include/jieba.cpp
	ar rs lib/libcjieba.a lib/cjieba.o 
clean:
	rm -f lib/*.a lib/*.o lib/*.so demo
