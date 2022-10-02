number1 = "66666"
number2 = "44886"
list = [int(i) for i in number1]
list.append('@')
sum = 0
flag = 0

while(True):
    newList = []
    for i in range(1,len(list)):
        print(i)
        if list[i] != list[i-1]:
            for j in str(sum+list[i-1]):
                newList.append(int(j));
            sum = 0
            continue;
        flag = 1
        sum += list[i-1];
    if flag == 0:
        break;
    flag = 0
    list = newList
    list.append("@")
    print(list)
print("".join([str(list[i]) for i in range(0,len(list)-1)]))
