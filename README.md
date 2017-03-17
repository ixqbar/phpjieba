

```php
array jieba(string $text, bool use_extract = false, long extract_limit = 10)
```

### install
```
git clone https://github.com/jonnywang/phpjieba.git
cd jz/cjieba
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
jieba.dict_path=/Users/xingqiba/data/softs/jz/cjieba/dict    #指向jieba库dict目录
```

### example
```
$result = jz_jieba('小明硕士毕业于中国科学院计算所，后在日本京都大学深造');
print_r($result);

$result = jz_jieba('小明硕士毕业于中国科学院计算所，后在日本京都大学深造', true, 6);
print_r($result);

$result = jz_jieba('他心理健康');
print_r($result);
```
 * 更新请参考example目录

### contact
更多疑问请+qq群 233415606 or [website http://www.hnphper.com](http://www.hnphper.com)


