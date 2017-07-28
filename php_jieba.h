/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_JIEBA_H
#define PHP_JIEBA_H

extern zend_module_entry jieba_module_entry;
#define phpext_jieba_ptr &jieba_module_entry

#define PHP_JIEBA_VERSION "0.0.6"

#ifdef PHP_WIN32
#	define PHP_JIEBA_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_JIEBA_API __attribute__ ((visibility("default")))
#else
#	define PHP_JIEBA_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#include "jieba.h"

PHP_MINIT_FUNCTION(jieba);
PHP_MSHUTDOWN_FUNCTION(jieba);
PHP_RINIT_FUNCTION(jieba);
PHP_RSHUTDOWN_FUNCTION(jieba);
PHP_MINFO_FUNCTION(jieba);

PHP_FUNCTION(jieba);

ZEND_BEGIN_MODULE_GLOBALS(jieba)
	zend_bool enable;
	Extractor extractor;
	Jieba jieba;
	char *dict_path;
ZEND_END_MODULE_GLOBALS(jieba)

#ifdef ZTS
#define JIEBA_G(v) TSRMG(jieba_globals_id, zend_jieba_globals *, v)
#else
#define JIEBA_G(v) (jieba_globals.v)
#endif

#endif	/* PHP_JIEBA_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
