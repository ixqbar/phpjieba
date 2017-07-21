PHP_ARG_ENABLE(jieba, whether to enable jieba support,
Make sure that the comment is aligned:
[  --enable-jieba           Enable jieba support])

if test "$PHP_JIEBA" != "no"; then
  PHP_ADD_LIBRARY(stdc++, 1, JIEBA_SHARED_LIBADD)
  PHP_ADD_INCLUDE("./cjieba/include")
  PHP_ADD_LIBRARY_WITH_PATH(cjieba, "./cjieba/lib", JIEBA_SHARED_LIBADD)
  
  PHP_SUBST(JIEBA_SHARED_LIBADD)

  PHP_NEW_EXTENSION(jieba, jieba.c, $ext_shared)
fi
