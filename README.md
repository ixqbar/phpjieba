
### version 0.0.6
* 加载字典缘故嫌慢的同学可以考虑使用  https://github.com/jonnywang/goredisjieba

### functions
```php
array jieba(string $text, int $action = 0, int $limit = 50)
```
* action 0 Extract 1 CutForSearch 2 Tag

### install
```
git clone https://github.com/jonnywang/phpjieba.git
cd phpjieba/cjieba
make

cd ..
phpize
./configure
make
make install
```
* jieba more detail please visit https://github.com/yanyiwu/cppjieba

### php.ini
```
extension=jieba.so
jieba.enable=1
jieba.dict_path=/Users/xingqiba/data/softs/phpjieba/cjieba/dict    #指向jieba库dict目录
```

### example
```
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
```
 * 更新请参考example目录
 * 词性可参考HanLP词性标注集解释

### contact
更多疑问请+qq群 233415606 

### plus
https://github.com/jonnywang/goredisjieba


