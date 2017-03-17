all: demo
demo: libjieba.a
	gcc -o demo demo.c -L./lib -ljieba -lstdc++ -lm
libjieba.a:
	g++ -o lib/jieba.o -c -DLOGGING_LEVEL=LL_WARNING -I./deps/ include/jieba.cpp
	ar rs lib/libjieba.a lib/jieba.o 
clean:
	rm -f lib/*.a lib/*.o demo
