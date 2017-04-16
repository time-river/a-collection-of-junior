awk 程序是由一个或者多个 __模式-动作__ 语句构成的序列:
```
pattern { action }
pattern { action }
```

1. 某些语句中，模式可以不存在；还有些语句，动作及其包围它的花括号也可以不存在。
2. awk 检查后没有语法错误，就会每次读取每一行，对读取到的每一行，按顺序检查每一个模式，对每一个与当前匹配的模式，对应的动作就会执行。
3. 一个缺失的模式匹配每一个输入行，因此每一个不带有模式的动作对每一个输入行都会执行。
4. 只含有模式而没有动作的语句，会打印每一个匹配模式的输入行。

输入文件 countries

程序格式
1. *模式-动作* 语句，以及动作内的语句通常用换行符分隔，但是若干条语句也可出现在同一行，只要他们之间用分号分开即可。一个分号可以放在任何语句的末尾。
2. 动作的左花括号必须与它的模式在同一行；而剩下的部分，包括右花括号，则可以出现在下面几行。
3. 空行会被忽略；他们可以插入在语句之前或之后，用来提高程序的可读性。空格与制表符可以出现在运算符与操作数的周围，同样也是为了提高可读性。
4. 注释可以出现在任意一行的末尾。一个注释以井号（#）开始，以换行符号结束。
{ print $1, $3 }    # print country name and population
5. 一个长语句可以分散成多行，只要在断行处插入一个反斜杠即可。
{ print \
    $1,     # country name
    $2,     # area in thousands of square miles
    $3 }    # population in millions

2.1 模式

模式汇总

1. BEGIN{ *statements* }
在输入被读取之前，*statements*执行一次。
2. END{*statements*}
当所有输入被读取完毕之后，*statements*执行一次。
3. *expression*{ *statements* }
每碰到一个使 *expression* 为真的输入行，*statements* 就执行。*expression* 为真指的是其值非零或非空。
4. /*regular expression*/ { *statements* }
当碰到这样一个输入行时，*statements* 就执行： 输入行含有一段字符串，而该字符串可以被 *regular expression* 匹配。
5. *compound pattern* { *statements* }
一个复合模式将表达式用 &&(AND), ||(OR), !(NOT), 以及括号组合起来；当 *compound pattern* 为真时，*statements* 执行。
6. *pattern_1, pattern_2* { *statements* }
一个范围模式匹配多个输入行，这些输入行从匹配 *pattern_1* 的行开始，到匹配 *pattern_2* 的行结束（也包括这两行），对其中的每一行执行 *statements*。

BEGIN 与 END 不与其他模式组合。一个范围模式不能是其他模式的一部分。BEGIN 与 END 是唯一两个不能省略动作的模式。

BEGIN 与 END
这两个模式匹配任何输入行。当 awk 从输入读取数据之前，BEGIN 的语句开始执行；当所有输入数据被读取完毕，END 语句开始执行。BEGIN 与 END 不能与其他模式做组合。如果有多个 BEGIN，与其关联的动作会按照他们在程序中出现的顺序执行，这种行为对多个 END 同样适用。通常将 BEGIN 放在程序开头，将 END 放在程序末尾，虽然这并不是强制的。

将表达式用作模式
描述字符串的表达式
*string*表示一个由0个或多个字符组成的序列。
空字符串（_null string_）、子字符串（_substring_）
任意一个表达式都可以用作任意一个运算符的操作数。表达式字符串/数值自动转换。
任意一个表达式都可当作数值使用。
表达式比较：数值比较，字符串比较：字符间的先后顺序依赖于机器的字符集（大多数是 ASCII 字符集）

---
运算符 | 意义
---
< | 小于
<= | 小于或等于
== | 等于
!= | 不等于
>= | 大于或等于
> | 大于
~ | 匹配
!~ | 不匹配

字符串匹配模式
正则表达式（*regular expression*）表示法。字符串匹配模式（*string-matching pattern*）测试一个字符串是否包含一段可以被正则表达式匹配的子字符串。

字符串匹配模式
1. /*regexpr*/
当当前输入行包含一段能够被 *regexpr* 匹配的子字符串，该模式被匹配。
2. *expression* ~ /*regexpr*/
如果 *expression* 的字符串值包含一段能够被 *regexpr* 匹配的子字符时，该模式被匹配。
3. *expression* != /*regexpr*/
如果 *expression* 的字符串值不包含能够被 *regexpr* 匹配的子字符串，该模式被匹配。

在 ~ 与 !~ 的语境中，任意一个表达式都可以用来替换 /*regexpr*/。

`/Asia/`是`$0 ~ /Asia/`的简写形式。

正则表达式
1. 正则表达式的元字符串包括：
`\ ^ $ . [ ] | ( ) * + ?`
2. 一个基本的正则表达式包括下面几种：
一个不是元字符的字符，比如`A`，这个正则表达式匹配的就是它本身。
一个匹配特殊符号的转义字符：`\t`匹配一个制表符。
一个被引用的元字符，例如`\*`，按字面意义匹配元字符。
`^`匹配一行的开始。
`$`匹配一行的结束。
`.`匹配任意一个字符。
一个字符类：`[ABC]`匹配字符 A，B或C。
字符类可能包含缩写形式：`[A-Za-z]`匹配单个字母。
一个互补的字符类：`[^0-9]`匹配任意一个字符，但是除了数字。
3. 这些运算符将正则表达式组合起来：
选择：`A|B`匹配 A 或 B。
拼接：`AB`匹配后面紧跟着 B 的 A。
闭包：`A\*`匹配 0 个或多个 A。
正闭包：`A+`匹配一个或多个 A。
零或一：`A?`匹配空字符串或 A。
括号：被`(r)`匹配的字符串，与`r`所匹配的字符串相同。

字符类（_character class_）：一组被包围在方括号中的字符组成的正则表达式——这个表达式匹配的字符类中的任意一个字符。
互补（_complemented_）的字符串：在`[`之后以`^`开始，一个类匹配任意一个不在类中的字符。
在一个字符类中，所有的字符都具有它自身的字面意义，除了引用字符`\`，互补字符类__开头__的`^`，以及两个字符间的`-`。
可以使用括号来指定正则表达式中的各个成分如何组合。由两种二元正则表达式运算符：选择与拼接。
awk 不存在显式的拼接字符串。
正则表达式中，优先级：选择运算符`|` < 拼接运算 < 重复运算`*,+,?`

转义序列（*escape sequences*）
---
序列 | 意义
---
\b | 退格
\f | 换页
\n | 换行
\r | 回车
\t | 制表符
\ddd | 八进制数 *ddd*，*ddd* 含有 1 到 3 个数字，每个数字的值在 0 到 7 之间。
\c | 其他的字面意义上的 c（举例来说，\\ 表示反斜杠，\" 表示双引号）

正则表达式（运算符按照递增的顺序列出）
---
表达式 | 匹配
---
c | 非元字符 c
\c | 转义序列或字面意义上的c
^ | 字符串的开始
$ | 字符串的结束
. | 任意一个字符串
[c1c2...] | 任意一个在 c1c2... 中的字符
[^c1c2...] | 任意一个不在 c1c2... 中的字符
[c1-c2...] | 任意一个在范围内的字符，范围由 c1 开始，由 c2 结束
[^c1-c2...] | 任意一个不在范围内的字符，范围由 c1 开始，由 c2 结束
r1|r2 | 任意一个被 r1 或 r2 匹配的字符串
(r1)|(r2) | 任意一个字符串 xy，其中 r1 匹配 x，而 r2 匹配 y；如果当中不含有选择运算符，那么括号是可以省略的
(r)\* | 零个或连续多个能被 r 匹配的字符串
(r)+ | 一个或连续多个能被 r 匹配的字符串
(r)? | 零个或一个能被 r 匹配的字符串（这里括号可以省略）
(r) | 任意一个能被 r 匹配的字符串

复合模式：一个复合模式式一个组合了其他模式的表达式，通过括号，逻辑运算符来进行组合。

范围模式：一个范围模式由两个被逗号分开的模式组成，正如 *pat1, pat2*
一个范围模式不能是其他模式的一部分。

模式总结

---
模式 | 例子 | 匹配
---
BEGIN | BEGIN | 输入被读取之前
END | END | 所有输入被读取完之后
*expression* | $3 < 100 | 第 3 个字段小于 100 的行
*string-matching* | /Asia/ | 含有 Asia 的行
*compound* | $3 < 100 && $4 == "Asia" | 第 3 个字段小于 100 并且第 4 个字段含有 Asia 的行
*range* | NR == 100, NR == 20 | 输入的第 10 行到第 20 行

2.2 动作

动作
动作中的语句可以包括：
*expression*，包括常量，变量，赋值，函数调用等等。
print *expression-list*
printf(*format*, *expression-list*)
if (*expression*) *statements*
if (*expression*) *statements* else *statements*
while (*expression*; *expression*; *expression*) *statements*
for (*expression* in *array*) *statements*
do *statements* while (*expression*)
break
continue

表达式
常量（*Constants*）：字符串和数值。
变量（*Variables*）：用户定义的，内建的，或字段。未初始化的变量值是`""`与`0`。
内建变量（*Built-In Variables*）：
---
变量 | 意义 | 默认值
---
ARGC | 命令行参数的个数 | -
ARGV | 命令行参数数组 | -
FILENAME | 当前输入文件名 | -
FNR | 当前输入文件的记录个数 | -
FS | 控制着输入行的字段分隔符 | `" "`
NF | 当前记录的字段个数 | -
NR | 到目前为止的记录数量 | -
OFMT | 数值的输出格式 | `"%.6g"`
OFS | 输出字段分隔符 | `" "`
ORS | 输出的记录的分隔符 | `"\n"`
RLENGTH | 被函数 match 匹配的字符串的长度 | -
RS | 控制着输入行的记录分隔符 | `"\n"`
RSTART | 被函数 match 匹配的字符串的开始 |
SUBSEP | 下标分隔符 | `"\034"`

字段变量（*Field Variables*）：当前输入寒风的字段，从`$1`，`$2`，一直到`$NF`；`$0`表示整行。
note: 当 $0 被重新修改或重新赋值，NF 就会被重新计算；同样的道理，当 $1 等被修改，$0 就会被重新构造，构造的方式是使用 OFS 重新分割字段。
字段也可以通过表达式来指定。例如 $(NF-1)
若字段变量引用到来不存在的字段，那么特的值就是初始值——空字符串。
每一行字段数可以不同，awk 的具体实现通常将字段数上限设置为 100。
算术运算符（*Comparison Operators*）
表达式
1. 初等表达式包括：
数值与字符串常量，变量，字段，函数调用，数组元素。
2. 可以把表达式组合起来的运算符包括：
赋值运算符 = += -= \*= /= %= ^=
条件表达式 ?:
逻辑运算符 || && !
匹配运算符 ~ !~
关系运算符 < <= == != > >=
拼接运算符（没有显式的拼接运算符）
算术运算符 + - * / % ^
单目运算符 + -
自增与自减运算符 ++ -- （包括前缀与后缀）
括号（用于分组）
逻辑运算符（*Logical Operators*）
条件表达式(*Conditional Expressions*)。形式：*expr1* ? *expr2* : *expr3*
赋值运算符（*Assignment Operators*）
自增与自减（*Increment and Decrement Operators*）
内建算术函数（*Built-In Arithmetic Functions*）
---
函数 | 返回值
---
atan2(y, x) | $\frac{y}{x}$ 的反正切值，定义域 $(-\pi, \pi)$
cos(x) | $x$ 的余弦值，$x$ 以弧度为单位
exp(x) | $x$ 的指数函数，$e^x$
int(x) | $x$ 的整数部分；当 $x$ 大于 0 时，向 0 取整
log(x) | $x$ 的自然对数（以 $e$ 为底）
rand() | 返回一个随机数 $r$，$0 \le r < 1$
sin(x) | $x$ 的正弦值，$x$ 以弧度为单位
sqrt(x) | $x$ 的方根
srand(x) | $x$ 是 $rand()$ 的新的随机数种子
字符串运算符（*String Operators*）
作为正则表达式的字符串（*Strings as Regular Expressions*）
内建字符串函数（*Built-In String Functions*）
---
函数 | 描述
---
gsub(r, s) | 将 $0 中所有出现的 *r* 替换为 *s*，返回替换发生的次数
gsub(r, s, t) | 将字符串 _t_ 中所有出现的 _r_ 替换为 _s_，返回替换发生的次数
index(s, t) | 返回字符串 _t_ 在 _s_ 中第一次出现的位置，如果 _t_ 没有出现的话，返回 0
length(s) | 返回 _s_ 包含的字符个数
match(s, r) | 测试 _s_ 是否包含能被 _r_ 匹配的子串，返回子串的起始位置；设置 RSTART 与 RLENGTH
split(s, a) | 用 FS 将 _s_ 分割到数组 _a_ 中，返回字段的个数
split(s, a, fs) | 用 _fs_ 分割 _s_ 到数组 _a_ 中，返回字段的个数
sprintf(fmt, expr-list) | 根据格式字符串 _fmt_ 返回格式化后的 _expr-list_
sub(r, s) | 将 $0 的最左最长的，能被 _r_ 匹配的子字符串替换为 _s_，返回替换发生的次数
substr(s, p) | 返回 _s_ 中从位置 _p_ 开始的后缀
substr(s, p, n) | 返回 _s_ 从位置 _p_ 开始的后缀

数值还是字符串（*Number or String*）：表达式的值可以自动从数值转换为字符串
数值运算、比较——数值比较、字符串比较、不同类型的数值比较
---
操作 | 运算符
---
赋值 | = += -= \*= /= %= ^=
条件表达式 | ?: | x ? y : z
逻辑或 | ||
逻辑与 | &&
数组成员匹配 | in
关系运算 | < <= == != >= >
拼接 |
加减法 | + -
乘除法，取模 | * / %
单目加减 | + -
逻辑非 | !
自增，自减 | ++ --
字段 | $
组合 | ()

运算符的总结（*Summary of Operators*）

流程控制语句
1. {*statements*}
语句组
2. if (*expression*) *statements*
如果 *expression*为真，执行*statements*
3. if (*expression*) *statements1* else *statements2*
如果 *expression* 为真，执行 *statements1*，否则执行 *statements2*
4. while (*expression*) *statements*
如果 *expression* 为真，执行 *statements*；然后重复前面的过程
5. for (*expression1*;*expression2*;*expression3*) *statements*
等价与 *expression1*; while (*expression2*) {*statements*; *expression3*}
6. for (*variable* in *array* ) *statements*
轮流地将 *variable* 设置为 *array* 的每一个下标，并执行 *statements*
7. do *statements* while (*expression*)
执行 *statements*；如果 *expression* 为真就重复
8. break
马上离开最内层的，包围 break 的 while, for, 或 do
9. continue 开始最内层的，包围 continue 的 while, for, 或 do 的下一次循环
10. next
开始输入主循环的下一次迭代
11. exit
12. exit *expression*
马上执行 END 动作；如果已经在 END 动作内，那就退出程序，将 *expression* 作为程序的退出状态返回

空语句：单独一个分号表示一个空语句

数组：awk提供了一维数组。数组的下标是字符串（关联数组 - *associative arrays* - ）
A[*subscript*] 存在，那么表达式的值为 1，否则为 0。
1. delete 语句（*The delete Statement*）数组元素删除：delete array[subscript]
2. split 函数（*The split Function*）函数 split(*str*, *arr*, *fs*) 将字符串 *str* 切割成一个个字段，并存储到数组 *arr*。
多维数组（*Multidimensional Arrays*）：利用一维数组来近似模拟多维数组——`arr[i, j]`。数组元素不能再是数组。

2.3 用户自定义函数

定义函数的语句：
```
function name(patameter-list) {
    statements
}
```

 name(patameter-list) {
    statements
}
```

 name(patameter-list) {
    statements
}
```

2.4 输出
输出语句
1. print
将 $0 打印到标准输出
2. print *expression*, *expression* ...
打印各个 *expression*, *expression* 之间由 OFS 分开，由 ORS 终止
3. print *expression*, *expression*, ... > *filename*
输出至文件 *filename*
4. print *expression*, *expression*, ... >> *filenaame*
累加输出到文件 *filename*，不覆盖之前的内容
5. print *expression*, *expression*, ... | command
输出作为命令 *command* 标准输入
6. printf(*format*, *expression*, *expression*, ...)
7. printf(*format*, *expression*, *expression*, ...) > *filename*
8. printf(*format*, *expression*, *expression*, ...) >> *filename*
9. printf(*format*, *expression*, *expression*, ...) | command
printf 类似于 print，但是第一个参数规定了输出的格式
10. close(*filename*), close(*command*)
断开 print 与 *filename*（或*command*）之间的连接
11. system(*command*)
执行 *command*；函数的返回值是 *command* 的退出状态

print 语句：
```
print expression1, expression2, ..., expressionn
print (expression1, expression2, ..., expressionn)
```

输出分隔符：输出字段分隔符与输出记录分隔符存储在内建变量 OFS 与 ORS 中。
printf 语句：
printf 格式控制字符
---
字符 | 表达式将被打印为
---
c | ASCII字符
d | 十进制整数
e | [-]d.ddddddE[+-]dd
f | [-]ddd.dddddd
g | 按照 e 或 f 进行转换，选择较短的那个，无意义的零会被抑制
o | 无符号八进制数
s | 字符串
x | 无符号十六进制数
% | 打印一个百分号 %，不会有参数被吸收

format，每一个格式说明符都以 % 开始，以转换字符结束，可能含有下面三种修饰符：
- 表达式在它的域内左对其
*width* 为了达到规定的宽度，必要时填充空格；前导的 0 表示用零填充
*.prec* 字符串最大宽度，或十进制数的小数部分的位数

输出到文件

输出到管道

关闭文件与管道

2.5 输入
指定输入文件/标准输入

输入分隔符：FS，默认`" "`。所赋字符串多于一个字符，那么它会被当初一个正则表达式。

多行记录：
```
BEGIN { RS = "" }
BEGIN { RS = ""; FS = "\n" } # 处理多行的通常方式
```

命令行变量赋值

命令行参数

2.6 与其他程序的交互
system 函数
用 AWK 制作 Shell 命令

第三章 数据处理

3.1 数据转换与归约
列求和
计算百分比与分位数
带逗号的数
字段固定的输入时
程序的交叉引用检查
格式化的输出

3.2数据验证
对称的分隔符
密码文件检查
自动生成数据验证程序
AWK的版本

3.3打包与拆包
3.4多行记录
不管`FS`的值是什么，换行符总是多行记录的字段分隔符之一。如果`RS`被设置成`""`，则默认的字段分隔符就是空格符、制表符、换行符；如果`FS`是`\n`，则换行副就是唯一的字段分隔符。

4 报表与数据库

4.1 报表生成
4.2 打包的查询与报表
