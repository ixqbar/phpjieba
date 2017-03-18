<?php

$result = jieba('小明硕士毕业于中国科学院计算所，后在日本京都大学深造');
echo implode('/', $result) . PHP_EOL;
//小明/硕士/毕业/于/中国/科学/学院/科学院/中国科学院/计算/计算所/，/后/在/日本/京都/大学/京都大学/深造

$result = jieba('小明硕士毕业于中国科学院计算所，后在日本京都大学深造', true, 6);
echo implode('/', $result) . PHP_EOL;
//计算所/小明/京都大学/深造/硕士/中国科学院

$result = jieba('他心理健康');
echo implode('/', $result) . PHP_EOL;
//他/心理/健康/心理健康

$result = jieba('this is a demo, my name is jony', true, 10);
echo implode('/', $result) . PHP_EOL;
//demo/jony

$result = jieba('this is a demo, my name is jony');
echo implode('/', $result) . PHP_EOL;
//this/ /is/ /a/ /demo/,/ /my/ /name/ /is/ /jony