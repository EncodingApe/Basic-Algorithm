# 最近点对问题
import math
import random


def findClostest(point_set):
    lenth = len(point_set)
    if lenth <= 2:
        return math.sqrt((point_set[0][0]-point_set[1][0])**2+(point_set[0][1]-point_set[1][1])**2)
    if lenth <= 3:
        return min(math.sqrt((point_set[0][0]-point_set[1][0])**2+(point_set[0][1]-point_set[1][1])**2),math.sqrt((point_set[2][0]-point_set[1][0])**2+(point_set[2][1]-point_set[1][1])**2))

    mid = lenth // 2
    dis1 = findClostest(point_set[:mid])
    dis2 = findClostest(point_set[mid:])
    dis = min(dis1,dis2)
    m = point_set[mid][0]
    low_border = m - dis
    high_border = m + dis
    temp_set = []   # 中间带中的点
    for i in point_set:
        if i[0] > low_border and i[0] < high_border:
            temp_set.append(i)
    temp_set.sort(key=lambda x:x[1])
    for i in range(len(temp_set)):
        count = 0
        for j in range(i+1,len(temp_set),1):
            count += 1
            dis = min(math.sqrt((point_set[i][0]-point_set[j][0])**2+(point_set[i][1]-point_set[j][1])**2),dis)
            if count == 7:
                break
    return dis


if __name__ == '__main__':
    point_set = [(random.randint(0,20),random.randint(0,20)) for i in range(10)]
    s = set(point_set)
    point_set = list(s)
    point_set.sort(key=lambda x:x[0])
    print(findClostest(point_set))
