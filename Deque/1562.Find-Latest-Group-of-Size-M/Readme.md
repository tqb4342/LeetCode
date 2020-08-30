### 1562.Find-Latest-Group-of-Size-M

首先要正确理解题意。举个例子，arr[3]=4的意思是，第3天的时候，将第4个bit位置为1. 如果需要，我们可以反过来定义一个day[4]=3，表示第4个bit位，我们在第3天的时候将其置为1.

文中要找到某一天t，存在一个长度恰为m的区间[i,j]其bit为都是1。那么区间内所有bit对应的day都要小于等于t（不晚于第t天变成1）。显然，对于这个区间而言最早的t，就是这个区间内最大的那个day。也就是说，当[i,j]内最后一个bit变为1的时候，那么整个区间恰好都变成了1.

同时因为“长度恰为m”，说明在第t天完成的时候，第i-1个bit位和第j+1个bit位必须都还是0，也就是要求day[i-1]>t 且 day[j+1]>t。如果满足上面的条件，就可以判定这个[i,j]区间就是我们想要找的“恰好长度为m的全1串”。

本题中，我们很容易遍历一个长度m的滑窗[i,j]，根据这个滑窗内部的day的信息，套用sliding window maximum的做法，可以o(1)时间知道```t = max(day[k]) k=i,...,j```。然后只需查看一下是否day[i-1]>t且day[j+1]>t。是的话，那么意味着在t之后、min(day[i-1], day[j+1])之前的这段时间，这个全1的区间恰好就是m的长度。显然，我们会挑尽量靠后的日子，也就是 ```min(day[i-1], day[j+1])-1```

所以，最终的答案就是遍历长度为m的滑窗，如果判断出这个滑窗符合要求，那么就有机会用```min(day[i-1], day[j+1])-1```更新result. 最终result会取全局所有滑窗里最大的那个答案。

参考 239. sliding window maximum 的deque方法，用o(n)时间求固定长度滑窗的最大值。