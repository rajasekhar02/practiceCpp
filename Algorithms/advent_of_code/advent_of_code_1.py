
elvesCalories = [i.strip().split("\n") for i in x.split("\n\n")]

elvesTotalCalories = []

for listi in elvesCalories:
    totalCalories = 0
    for item in listi:
        totalCalories = totalCalories + int(item)
    elvesTotalCalories.append(totalCalories)
elvesTotalCalories = sorted(elvesTotalCalories, reverse=True)
print(elvesTotalCalories[0] + elvesTotalCalories[1] + elvesTotalCalories[2])
