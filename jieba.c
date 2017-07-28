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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_jieba.h"
#include <unistd.h>

ZEND_DECLARE_MODULE_GLOBALS(jieba)

static int le_jieba;

#ifndef BUFSIZE
	#define BUFSIZE 2048
#endif

#define JZ_JIEBA_DICT_NAME "jieba.dict.utf8"
#define JZ_JIEBA_DICT_HMM_NAME "hmm_model.utf8"
#define JZ_JIEBA_USER_DICT_NAME "user.dict.utf8"
#define JZ_JIEBA_IDF_NAME "idf.utf8"
#define JZ_JIEBA_STP_WORDS_NAME "stop_words.utf8"

ZEND_BEGIN_ARG_INFO_EX(arg_info_jieba, 0, 0, 3)
	ZEND_ARG_INFO(0, sentence)
	ZEND_ARG_INFO(0, extract)
	ZEND_ARG_INFO(0, extract_limit)
ZEND_END_ARG_INFO()

/* {{{ jieba_functions[]
 *
 * Every user visible function must have an entry in jieba_functions[].
 */
const zend_function_entry jieba_functions[] = {
	PHP_FE(jieba, arg_info_jieba)
	PHP_FE_END
};
/* }}} */

/* {{{ jieba_module_entry
 */
zend_module_entry jieba_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"jieba",
	jieba_functions,
	PHP_MINIT(jieba),
	PHP_MSHUTDOWN(jieba),
	PHP_RINIT(jieba),
	PHP_RSHUTDOWN(jieba),
	PHP_MINFO(jieba),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_JIEBA_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_JIEBA
ZEND_GET_MODULE(jieba)
#endif


static int jieba_init()
{
	int not_change = 1;
	if (JIEBA_G(enable) != INI_INT("jieba.enable")) {
		JIEBA_G(enable) = (zend_bool)INI_INT("jieba.enable");
		not_change = 0;
	}

	if (JIEBA_G(dict_path) != INI_STR("jieba.dict_path")) {
		JIEBA_G(dict_path) = INI_STR("jieba.dict_path");
		not_change = 0;
	}

	if (1 == not_change
		|| JIEBA_G(enable) == 0
		|| JIEBA_G(dict_path) == ""
		|| JIEBA_G(dict_path) == NULL) {
		return FAILURE;
	}

	size_t jz_dict_path_len = strlen(JIEBA_G(dict_path));

	char dict_path[BUFSIZE];
	char dict_hmm_path[BUFSIZE];
	char user_dict_path[BUFSIZE];
	char idf_path[BUFSIZE];
	char stop_words_path[BUFSIZE];

	memcpy(dict_path, JIEBA_G(dict_path), jz_dict_path_len);
	memcpy(dict_hmm_path, JIEBA_G(dict_path), jz_dict_path_len);
	memcpy(user_dict_path, JIEBA_G(dict_path), jz_dict_path_len);
	memcpy(idf_path, JIEBA_G(dict_path), jz_dict_path_len);
	memcpy(stop_words_path, JIEBA_G(dict_path), jz_dict_path_len);

	if (dict_path[jz_dict_path_len - 1] != '/') {
		dict_path[jz_dict_path_len] = '/';
		dict_hmm_path[jz_dict_path_len] = '/';
		user_dict_path[jz_dict_path_len] = '/';
		idf_path[jz_dict_path_len] = '/';
		stop_words_path[jz_dict_path_len] = '/';

		jz_dict_path_len += 1;
	}

	memcpy(dict_path + jz_dict_path_len, JZ_JIEBA_DICT_NAME, sizeof(JZ_JIEBA_DICT_NAME));
	dict_path[jz_dict_path_len + sizeof(JZ_JIEBA_DICT_NAME)] = 0;

	memcpy(dict_hmm_path + jz_dict_path_len, JZ_JIEBA_DICT_HMM_NAME, sizeof(JZ_JIEBA_DICT_HMM_NAME));
	dict_hmm_path[jz_dict_path_len + sizeof(JZ_JIEBA_DICT_HMM_NAME)] = 0;

	memcpy(user_dict_path + jz_dict_path_len, JZ_JIEBA_USER_DICT_NAME, sizeof(JZ_JIEBA_USER_DICT_NAME));
	user_dict_path[jz_dict_path_len + sizeof(JZ_JIEBA_USER_DICT_NAME)] = 0;

	memcpy(idf_path + jz_dict_path_len, JZ_JIEBA_IDF_NAME, sizeof(JZ_JIEBA_IDF_NAME));
	idf_path[jz_dict_path_len + sizeof(JZ_JIEBA_IDF_NAME)] = 0;

	memcpy(stop_words_path + jz_dict_path_len, JZ_JIEBA_STP_WORDS_NAME, sizeof(JZ_JIEBA_STP_WORDS_NAME));
	stop_words_path[jz_dict_path_len + sizeof(JZ_JIEBA_STP_WORDS_NAME)] = 0;

	if (access(dict_path, R_OK|F_OK) != 0
		|| access(dict_hmm_path, R_OK|F_OK) != 0
		|| access(user_dict_path, R_OK|F_OK) != 0
		|| access(idf_path, R_OK|F_OK) != 0
		|| access(stop_words_path, R_OK|F_OK) != 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "error jieba dict path %s in php.ini", dict_path);
		return FAILURE;
	}

	if (JIEBA_G(jieba) != NULL) {
		FreeJieba(JIEBA_G(jieba));
		JIEBA_G(jieba) = NULL;
	}

	if (JIEBA_G(extractor) != NULL) {
		FreeExtractor(JIEBA_G(extractor));
		JIEBA_G(extractor) = NULL;
	}

	JIEBA_G(jieba) = NewJieba(dict_path, dict_hmm_path, user_dict_path, idf_path, stop_words_path);
	JIEBA_G(extractor) = NewExtractor(dict_path, dict_hmm_path, idf_path, stop_words_path, user_dict_path);

	return SUCCESS;
}

static void jieba_deinit()
{
	if (JIEBA_G(jieba) != NULL) {
		FreeJieba(JIEBA_G(jieba));
		JIEBA_G(jieba) = NULL;
	}
	if (JIEBA_G(extractor) != NULL) {
		FreeExtractor(JIEBA_G(extractor));
		JIEBA_G(extractor) = NULL;
	}
}

PHP_INI_BEGIN()
	PHP_INI_ENTRY("jieba.enable",    "0", PHP_INI_ALL, NULL)
	PHP_INI_ENTRY("jieba.dict_path", "",  PHP_INI_ALL, NULL)
PHP_INI_END()

static void php_jieba_init_globals(zend_jieba_globals *jieba_globals)
{
	jieba_globals->enable    = 0;
	jieba_globals->jieba     = NULL;
	jieba_globals->extractor = NULL;
	jieba_globals->dict_path = NULL;
}


/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(jieba)
{
	ZEND_INIT_MODULE_GLOBALS(jieba, php_jieba_init_globals, NULL);

	REGISTER_INI_ENTRIES();

	jieba_init();

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(jieba)
{
	jieba_deinit();

	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(jieba)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(jieba)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(jieba)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "jieba support", "enabled");
	php_info_print_table_row(2, "version", PHP_JIEBA_VERSION);
	php_info_print_table_row(2, "author", "QQ:174171262");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */

PHP_FUNCTION(jieba)
{
	char *sentence = NULL;
#if PHP_MAJOR_VERSION >= 7
	size_t sentence_len = 0;
	zend_long action = 0;
	zend_long limit = 50;
#else
	int sentence_len = 0;
	long action = 0;
	long limit = 50;
#endif

	jieba_init();

	if (JIEBA_G(enable) == 0) {
		php_error_docref(NULL, E_WARNING, "phpjieba not enable in your php.ini");
		RETURN_FALSE;
	}

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|ll", &sentence, &sentence_len, &action, &limit) == FAILURE
		|| sentence_len == 0
		|| action > 2
		|| action < 0
		|| limit <= 0) {
		RETURN_FALSE;
	}

	CJiebaWord *words;
	CJiebaWord *x;

	array_init(return_value);
	switch (action) {
	case 0:
		words = Extract(JIEBA_G(extractor), sentence, sentence_len, limit);
		break;
	case 1:
		words = CutForSearch(JIEBA_G(jieba), sentence, sentence_len);
		break;
	case 2:
		words = CutWithTag(JIEBA_G(jieba), sentence, sentence_len);
		break;
	}

	int total = 0, index = 0, next_index;
	for (x = words; x && x->word; x++) {
		total++;
	}

	while (index < total) {
		if (limit <= 0) {
			break;
		}

		if (action != 2) {
			#if PHP_MAJOR_VERSION >= 7
			add_next_index_stringl(return_value, words[index].word, words[index].len);
			#else
			add_next_index_stringl(return_value, words[index].word, words[index].len, 1);
			#endif
			limit--;
		} else {
			next_index = index + 1;
			#if PHP_MAJOR_VERSION >= 7
				add_assoc_stringl_ex(return_value, words[index].word, words[index].len, (char *)words[next_index].word, words[next_index].len);
			#else
				add_assoc_stringl_ex(return_value, words[index].word, words[index].len + 1, (char *)words[next_index].word, words[next_index].len, 1);
			#endif
			index++;
		}

		if (words[index].free) {
			free((char *)words[index].word);
			words[index].free = 0;
		}
		if (index > 0 && words[index - 1].free) {
			free((char *)words[index - 1].word);
			words[index - 1].free = 0;
		}

		index++;
	}
	FreeWords(words);
}


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
