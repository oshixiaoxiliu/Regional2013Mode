最小表示法：

   初始时，i=0,j=1，分别以i，j，为起始点顺着i，j，往下比较直到找的str[i+k]!=str[j+k]，然后分两种情况考虑：

1、  str[i+k]>str[j+k]，i变成i=i+k+1，j不变，然后继续往下比较。

2、  str[i+k]<str[j+k]，j变成j=j+k+1，i不变，然后继续往下比较。

直到i或j大于串长，找较小者。

说说我的疑惑吧：

   用枚举方法我们很好理解，一某一点i为起点，不断查看以i后的点为起点的串是否小于以i为起点的串，这理解起来不难。我们假设以i点为起点的串为S1，以j点为起点的串S2，而用最小表示法的话，需要找的S1、S2第一个不相等的字符，假设距离S1、S2起点的k点为第一个不相同的点，然后做一下比较，使i或者j跳到k的下一个字符，这就避免了枚举，这也就是我疑惑的地方，为什么0到k之间（相对于S1，S2来说）为起点的串都不可能成为最小串呢？假如S1[k]>S2[k] 只能说明以S1[k]为起点的串不可能成为最小串，虽然S1[0..k-1] 和 S2[0…k-1]对应字符是相等的又能说明什么问题呢？我想了很久没有想明白。我突发奇想，假如说S1[0..k-1]和S2[0..k-1]所有字符都是相等的，这就可以解释我刚才的疑惑了：假如说S1[k]>S2[k]，若S1[k]>S1[k-1]，想想就知道S1[0…k]是不可能成为最小串的起点。若S1[k]<S1[k-1]，S1[0…k-1]（注意是0到k-1）那就更不可能了，然而S2[k]又小于S1[k]，所以S1[0…k]就不可能了。

   我不知道我的想法对还是不对，反正我没有找到反例，姑且这样认为吧，有更好的解释留言吧。


int work(int m)
{
    int i,j,l;
    i=0; j=1;
    while(i<m && j<m)
    {
        for(l=0;l<m;l++) 
            if(str[(i+l)%m]!=str[(j+l)%m]) break;
        if(l>m) break;
        if(str[(i+l)%m] > str[(j+l)%m])
            i=i+l+1;
        else
            j=j+l+1;
        if(i==j) j=i+1;
    }
    if(i<j) return i;
    return j;
}
