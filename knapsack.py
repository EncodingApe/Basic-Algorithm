# 背包-背包重量-背包价值
# 1 2 12
# 2 1 10
# 3 3 20
# 4 2 15

# 更新公式 =
# 若第j件物品的重量小于当前背包重量w :
#     情况1. 把不放入j, 那么总价值就是等于前j-1件物品在w下的价值
#     情况2. 把j放入, 那么总价值就是前j-1件物品在w-wj下的价值 + 第j件物品的价值
#     更新后的价值就是情况1 和 情况2 的最大值

if __name__ == '__main__':
    f = open('package.txt','r')
    packages = []
    for line in f:
        bar = line.strip().split(' ')
        packages.append([int(bar[i]) for i in range(1,3,1)])        # 读入背包信息
    W = int(input("总重量:"))
    NUM = len(packages)
    table = [[0 for w in range(W+1)] for j in range(NUM+1)]         # 初始化价值表

    for j in range(1,NUM+1,1):
        for w in range(1,W+1,1):
            if packages[j-1][0] > w:
                continue
            table[j][w] = max(table[j-1][w],table[j-1][w-packages[j-1][0]]+packages[j-1][1])    # 通过前面的记录更改价值表

    print("TABLE:")
    for line in table:
        for i in line:
            print(i,end=' ')
        print()
    print('-----------------------')
    print("THE MOST VALUE: {}".format(table[NUM][W]))
