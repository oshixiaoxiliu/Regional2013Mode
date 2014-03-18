对KMP的一些理解（lyp点拨的）：pre[i]（或next[i]）的实质是串str[1..i]的最长且小于i的“相等前、后缀”分别为str[1..pre[i]]（前缀）与str[(i-pre[i]+1)..i]（后缀），通俗讲就是：使str[1..i]前k个字母与后k个字母相等的最大k值。
KMP算法详解可见：http://blog.csdn.net/fjsd155/article/details/6864233
另外一个结论：
最小覆盖子串（串尾多一小段时，用前缀覆盖）长度为n-next[n]（n-pre[n]），n为串长。
证明分两部分：
１－长为n-next[n]的前缀必为覆盖子串。
当next[n]<n-next[n]时，如图a，长为next[n]的前缀A与长为next[n]的后缀B相等，故长为n-next[n]的前缀C必覆盖后缀B；

当next[n]>n-next[n]时，如图b，将原串X向后移n-next[n]个单位得到Y串，根据next的定义，知长为next[n]的后缀串A与长为前缀串B相等，X串中的长为n-next[n]的前缀C与Y串中的前缀D相等，而X串中的串E又与Y串中的D相等……可见X串中的长为n-next[n]的前缀C可覆盖全串。

２－长为n-next[n]的前缀是最短的。
如图c，串A是长为n-next[n]的前缀，串B是长为next[n]的后缀，假设存在长度小于n-next[n]的前缀C能覆盖全串，则将原串X截去前面一段C，得到新串Ｙ，则Ｙ必与原串长度大于next[n]的前缀相等，与next数组的定义（使str[1..i]前k个字母与后k个字母相等的最大k值。）矛盾。得证！有人问，为什么Ｙ与原串长大于next[n]的前缀相等？由假设知原串的构成必为CCC……E（E为C的前缀），串Ｙ的构成必为CC……E（比原串少一个Ｃ），懂了吧！
