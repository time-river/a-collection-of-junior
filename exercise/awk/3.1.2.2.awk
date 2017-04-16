# hisogram
#   input:  numbers between 0 and 100
#   output: histogram of deciles
# random.awk generate random number

    { x[int($1/10)]++ } # 计算介于 x - x+9 之间数的数量

END {
    for (i = 0; i < 10; ++i) {
        printf(" %2d - %2d: %3d %s\n",
               10*i, 10*i+9, x[i], rep(x[i], "*"))
    }
    printf("100:    %3d %s\n", x[10], rep(x[10], "*"))
}

function rep(n, s, t) { # return string of n s's
    while (n-- > 0)
        t = t s # 拼接字符串
    return t
}
