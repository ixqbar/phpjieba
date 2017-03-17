dnl $Id$
dnl config.m4 for extension jieba

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(jieba, for jieba support,
dnl Make sure that the comment is aligned:
dnl [  --with-jieba             Include jieba support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(jieba, whether to enable jieba support,
Make sure that the comment is aligned:
[  --enable-jieba           Enable jieba support])

if test "$PHP_JIEBA" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-jieba -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/jieba.h"  # you most likely want to change this
  dnl if test -r $PHP_JIEBA/$SEARCH_FOR; then # path given as parameter
  dnl   JIEBA_DIR=$PHP_JIEBA
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for jieba files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       JIEBA_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$JIEBA_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the jieba distribution])
  dnl fi

  dnl # --with-jieba -> add include path
  dnl PHP_ADD_INCLUDE($JIEBA_DIR/include)

  dnl # --with-jieba -> check for lib and symbol presence
  dnl LIBNAME=jieba # you may want to change this
  dnl LIBSYMBOL=jieba # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $JIEBA_DIR/$PHP_LIBDIR, JIEBA_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_JIEBALIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong jieba lib version or lib not found])
  dnl ],[
  dnl   -L$JIEBA_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  
  PHP_ADD_INCLUDE("./cjieba/include")
  PHP_ADD_LIBRARY_WITH_PATH(jieba, "./cjieba/lib", JZ_SHARED_LIBADD)
  
  PHP_SUBST(JIEBA_SHARED_LIBADD)

  PHP_NEW_EXTENSION(jieba, jieba.c, $ext_shared)
fi
