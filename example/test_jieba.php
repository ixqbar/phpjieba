<?php

$result = jz_jieba('小明硕士毕业于中国科学院计算所，后在日本京都大学深造');
print_r($result);

$result = jz_jieba('小明硕士毕业于中国科学院计算所，后在日本京都大学深造', true, 6);
print_r($result);

$result = jz_jieba('他心理健康');
print_r($result);

$result = jz_jieba('this is a demo, my name is jony', true, 10);
print_r($result);

$result = jz_jieba('this is a demo, my name is jony');
print_r($result);