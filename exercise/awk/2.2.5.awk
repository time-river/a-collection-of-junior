# 将 Asia 与 Europe 的人口数量累加到数组 pop 中，END 动作打印着两个洲的总人口

/Asia/  { pop["Asia"] += $3 }
/Europe/ { pop["Europe"] += $3 }
END {
    print "Asian population is",
        pop["Asia"], "million."
    print "European population is",
        pop["Europe"], "million."
}

