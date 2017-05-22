#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/jieba.h"

const char *DICT_PATH = "./dict/jieba.dict.utf8";
const char *HMM_PATH = "./dict/hmm_model.utf8";
const char *IDF_PATH = "./dict/idf.utf8";
const char *STOP_WORDS_PATH = "./dict/stop_words.utf8";
const char *USER_DICT = "./dict/user.dict.utf8";

const char *sentence = "小明硕士毕业于中国科学院计算所，后在日本京都大学深造";

Jieba handle;

void CutDemo() {
	printf("CutDemo:\n");

	CJiebaWord *words = Cut(handle, sentence, strlen(sentence));
	CJiebaWord *x;
	for (x = words; x && x->word; x++) {
		printf("%.*s/", (int) x->len, x->word);
	}
	printf("\n");
	FreeWords(words);
}

void CutForSearchDemo() {
	printf("CutForSearchDemo:\n");

	CJiebaWord *words = CutForSearch(handle, sentence, strlen(sentence));
	CJiebaWord *x;
	for (x = words; x->word; x++) {
		printf("%.*s/", (int) x->len, x->word);
	}
	printf("\n");
	FreeWords(words);
}

void CutWithoutTagNameDemo() {
	printf("CutWithoutTagNameDemo:\n");

	CJiebaWord *words = CutWithoutTagName(handle, sentence, strlen(sentence), "x");
	CJiebaWord *x;
	for (x = words; x->word; x++) {
		printf("%.*s/", (int) x->len, x->word);
	}
	printf("\n");
	FreeWords(words);
}

void CutWithTagDemo() {
	printf("CutWithTagDemo:\n");

	CJiebaWord *words = CutWithTag(handle, sentence, strlen(sentence));
	CJiebaWord *x;
	for (x = words; x->word; x++) {
		printf("%.*s", (int) x->len, x->word);
	}
	printf("\n");
	FreeWords(words);
}

void ExtractDemo() {
	printf("ExtractDemo:\n");

	Extractor ehandle = NewExtractor(DICT_PATH, HMM_PATH, IDF_PATH, STOP_WORDS_PATH, USER_DICT);

	size_t top_n = 5;
	CJiebaWord *words = Extract(ehandle, sentence, strlen(sentence), top_n);
	CJiebaWord *x;
	for (x = words; x->word; x++) {
		printf("%.*s/", (int) x->len, x->word);
	}
	printf("\n");
	FreeWords(words);
	FreeExtractor(ehandle);
}

void UserWordDemo() {
	printf("UserWordDemo:\n");

	CJiebaWord *words = Cut(handle, sentence, strlen(sentence));
	CJiebaWord *x;
	for (x = words; x->word; x++) {
		printf("%.*s/", (int) x->len, x->word);
	}
	printf("\n");
	FreeWords(words);

	JiebaInsertUserWord(handle, "计算");
	words = Cut(handle, sentence, strlen(sentence));
	for (x = words; x->word; x++) {
		printf("%.*s/", (int) x->len, x->word);
	}
	printf("\n");
	FreeWords(words);
}

int main(int argc, char **argv) {
	handle = NewJieba(DICT_PATH, HMM_PATH, USER_DICT, IDF_PATH, STOP_WORDS_PATH);

	CutDemo();
	CutForSearchDemo();
	CutWithoutTagNameDemo();
	CutWithTagDemo();
	ExtractDemo();
	UserWordDemo();

	FreeJieba(handle);

	return 0;
}
