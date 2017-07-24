<?php
ini_set('jieba.enable', 1);
ini_set('jieba.dict_path', '/Users/xingqiba/data/softs/phpjieba/cjieba/dict');

try {
$result = jieba('小明硕士毕业于中国科学院计算所，后在日本京都大学深造');
echo implode('/', $result) . PHP_EOL;
//计算所/小明/京都大学/深造/硕士/中国科学院/毕业/日本

$result = jieba('小明硕士毕业于中国科学院计算所，后在日本京都大学深造', 1, 50);
echo implode('/', $result) . PHP_EOL;
//小明/硕士/毕业/于/中国/科学/学院/科学院/中国科学院/计算/计算所/，/后/在/日本/京都/大学/京都大学/深造

$result = jieba('他心理健康', 1);
echo implode('/', $result) . PHP_EOL;
//他/心理/健康/心理健康

$result = jieba('this is a demo, my name is jony', 1, 10);
echo implode('/', $result) . PHP_EOL;
//demo/jony

$result = jieba('this is a demo, my name is jony');
echo implode('/', $result) . PHP_EOL;
//this/ /is/ /a/ /demo/,/ /my/ /name/ /is/ /jony

$result = jieba('小明硕士毕业于中国科学院计算所，后在日本京都大学深造', 2);
print_r($result);

/*
Array
(
    [小明] => x
    [硕士] => n
    [毕业] => n
    [于] => p
    [中国科学院] => nt
    [计算所] => n
    [，] => x
    [后] => f
    [在] => p
    [日本] => ns
    [京都大学] => nz
    [深造] => v
)
*/
} catch (Exception $e) {
    echo $e->getMessage() . PHP_EOL;    
}