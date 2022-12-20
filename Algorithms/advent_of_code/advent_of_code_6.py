
for i in range(14,len(input)-14+1):
    if len(set(input[i-14:i])) == 14:
        print(i,input[i-14:i])
        break
