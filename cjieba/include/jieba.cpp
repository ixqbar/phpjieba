extern "C" {
#include "jieba.h"
}

#include "cppjieba/Jieba.hpp"
#include "cppjieba/KeywordExtractor.hpp"

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {

Jieba NewJieba(const char* dict_path, const char* hmm_path, const char* user_dict, const char *idf_path, const char *stop_words_path) {
	Jieba handle = (Jieba) (new cppjieba::Jieba(dict_path, hmm_path, user_dict, idf_path, stop_words_path));
	return handle;
}

void FreeJieba(Jieba handle) {
	cppjieba::Jieba* x = (cppjieba::Jieba*) handle;
	delete x;
}

CJiebaWord* Cut(Jieba handle, const char* sentence, size_t len) {
	cppjieba::Jieba* x = (cppjieba::Jieba*) handle;
	vector<string> words;
	string s(sentence, len);
	x->Cut(s, words);

	CJiebaWord* res = (CJiebaWord*) malloc(sizeof(CJiebaWord) * (words.size() + 1));
	size_t offset = 0;
	for (size_t i = 0; i < words.size(); i++) {
		res[i].word = sentence + offset;
		res[i].len = words[i].size();
		res[i].free = 0;
		offset += res[i].len;
	}
	if (offset != len) {
		free(res);
		return NULL;
	}
	res[words.size()].word = NULL;
	res[words.size()].len = 0;
	res[words.size()].free = 0;

	return res;
}

CJiebaWord* CutForSearch(Jieba handle, const char* sentence, size_t len) {
	cppjieba::Jieba* x = (cppjieba::Jieba*) handle;
	vector<string> words;
	string s(sentence, len);
	x->CutForSearch(s, words);

	CJiebaWord* res = (CJiebaWord*) malloc(sizeof(CJiebaWord) * (words.size() + 1));
	for (size_t i = 0; i < words.size(); i++) {
		res[i].word = (char *) malloc(words[i].size());
		strncpy((char *) res[i].word, words[i].data(), words[i].size());
		res[i].len = words[i].size();
		res[i].free = 1;
	}

	res[words.size()].word = NULL;
	res[words.size()].len = 0;
	res[words.size()].free = 0;

	return res;
}

CJiebaWord* CutWithoutTagName(Jieba handle, const char* sentence, size_t len, const char* tagname) {
	cppjieba::Jieba* x = (cppjieba::Jieba*) handle;
	vector<pair<string, string> > tag_words;
	x->Tag(string(sentence, len), tag_words);

	CJiebaWord* res = (CJiebaWord*) malloc(sizeof(CJiebaWord) * (tag_words.size() + 1));
	size_t i, j, offset = 0;
	for (i = 0, j = 0; i < tag_words.size(); i++) {
		if (tag_words[i].second != tagname) {
			res[j].word = sentence + offset;
			res[j].len = tag_words[i].first.size();
			res[j].free = 0;
			j++;
		}

		offset += tag_words[i].first.size();
	}

	res[j].word = NULL;
	res[j].len = 0;
	res[j].free = 0;

	return res;
}

CJiebaWord* CutWithTag(Jieba handle, const char* sentence, size_t len) {
	cppjieba::Jieba* x = (cppjieba::Jieba*) handle;
	vector<pair<string, string> > tag_words;
	x->Tag(string(sentence, len), tag_words);

	CJiebaWord* res = (CJiebaWord*) malloc(sizeof(CJiebaWord) * (2 * tag_words.size() + 1));
	size_t i, j, offset = 0;
	for (i = 0, j = 0; i < tag_words.size(); i++) {
		res[j].word = (char *) malloc(tag_words[i].first.size());
		strncpy((char *) res[j].word, tag_words[i].first.data(), tag_words[i].first.size());
		res[j].len = tag_words[i].first.size();
		res[j].free = 1;

		j++;

		res[j].word = (char *) malloc(tag_words[i].second.size());
		strncpy((char *) res[j].word, tag_words[i].second.data(), tag_words[i].second.size());
		res[j].len = tag_words[i].second.size();
		res[j].free = 1;

		j++;
	}

	res[j].word = NULL;
	res[j].len = 0;
	res[j].free = 0;

	return res;
}

void FreeWords(CJiebaWord* words) {
	for (CJiebaWord *x = words; x->word; x++) {
		if (x->free) {
			free((char *) x->word);
		}
	}
	free(words);
}

bool JiebaInsertUserWord(Jieba handle, const char* word) {
	cppjieba::Jieba* x = (cppjieba::Jieba*) handle;
	return x->InsertUserWord(string(word), "u");
}

Extractor NewExtractor(const char* dict_path,
					   const char* hmm_path,
					   const char* idf_path,
					   const char* stop_word_path,
					   const char* user_dict_path) {
	Extractor handle = (Extractor) (new cppjieba::KeywordExtractor(dict_path, hmm_path, idf_path, stop_word_path, user_dict_path));
	return handle;
}

void FreeExtractor(Extractor handle) {
	cppjieba::KeywordExtractor* x = (cppjieba::KeywordExtractor*) handle;
	delete x;
}

CJiebaWord* Extract(Extractor handle, const char* sentence, size_t len, size_t topn) {
	cppjieba::KeywordExtractor* x = (cppjieba::KeywordExtractor*) handle;
	vector<cppjieba::KeywordExtractor::Word> words;
	x->Extract(sentence, words, topn);
	CJiebaWord* res = (CJiebaWord*) malloc(sizeof(CJiebaWord) * (words.size() + 1));
	for (size_t i = 0; i < words.size(); i++) {
		assert(words[i].offsets.size() > 0);
		size_t offset = words[i].offsets[0];
		assert(offset < len);
		res[i].word = sentence + offset;
		res[i].len = words[i].word.size();
		res[i].free = 0;
	}

	res[words.size()].word = NULL;
	res[words.size()].len = 0;
	res[words.size()].free = 0;

	return res;
}

} // extern "C"
