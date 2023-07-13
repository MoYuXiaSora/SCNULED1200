import matplotlib.pyplot as plt

def file2():
    file1 = open("EE_C_FF_W.TXT", "r")
    len1 = file1.readlines()
    len1 = len1[0].split("EE")
    list1 = []
    list2 = []
    for i in range(len(len1)):
        i = len1[i].split(" ")
        if(len(i)>2):
            list1.append(int(i[1],16))
            list2.append(int(i[3],16))
    plt.plot(list1)
    plt.plot(list2)
    plt.show()
file2()