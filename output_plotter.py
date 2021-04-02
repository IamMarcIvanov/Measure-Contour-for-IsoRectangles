import matplotlib.pyplot as plt

for i in range(1, 4):
    rects = []
    contour = []
    with open(r"E:\BITS\Yr 3 Sem 2\CS F364 Design and Analysis of Algo\Assignments\Assignment-1\TestCases\Input\viva_in_" + str(i) + ".txt", "r") as f:
        n = int(f.readline().strip())
        for j in range(n):
            rects.append(list(map(int, f.readline().strip().split())))
    
    # with open(r"E:\BITS\Yr 3 Sem 2\CS F364 Design and Analysis of Algo\Assignments\Assignment-1\TestCases\Ans\op.txt", "r") as f:
        # area = f.readlines()[i - 1].strip()
    
    for r in rects:
        x1, x2, y1, y2 = r[0], r[2], r[1], r[3]
        plt.plot([x1, x2], [y1, y1], color='b')
        plt.plot([x2, x2], [y1, y2], color='b')
        plt.plot([x2, x1], [y2, y2], color='b')
        plt.plot([x1, x1], [y2, y1], color='b')
    
    with open(r"E:\BITS\Yr 3 Sem 2\CS F364 Design and Analysis of Algo\Assignments\Assignment-1\TestCases\Ans\v" + str(i) + ".txt", "r") as f:
        flag = False
        for line in f.readlines():
            if line.strip() == "vert":
                flag = True
                continue
            if flag == False:
                y = list(map(int, line.strip().split()))
                #print(y)
                plt.plot([y[1], y[2]], [y[0], y[0]], color='r')
            else:
                y = list(map(int, line.strip().split()))
                plt.plot([y[0], y[0]], [y[1], y[2]],  color='r')

    
    #plt.title("Area is " + area)
    plt.show()
