listOfRanges = rangesStr.split("\n")
count = 0

for aRange in listOfRanges:
    [ar,br] = aRange.split(',')
    [ar_a,ar_b] = ar.split('-')
    [br_a,br_b] = br.split('-')
    ar_a = int(ar_a)
    ar_b = int(ar_b)
    br_a = int(br_a)
    br_b = int(br_b)
    # if (ar_a <= br_a and ar_b >= br_b) or (ar_a >= br_a and ar_b <= br_b):
    if ar_b < br_a or ar_a > br_b:
        count+=1
print(len(listOfRanges)-count)
