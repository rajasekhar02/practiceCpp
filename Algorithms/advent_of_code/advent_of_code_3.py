
listOfRuckSacks = elvesRuskSack.split("\n")

sum = 0

dictCharacters = {
   "a": 1,
   "b": 2,
   "c": 3,
   "d": 4,
   "e": 5,
   "f": 6,
   "g": 7,
   "h": 8,
   "i": 9,
   "j": 10,
   "k": 11,
   "l": 12,
   "m": 13,
   "n": 14,
   "o": 15,
   "p": 16,
   "q": 17,
   "r": 18,
   "s": 19,
   "t": 20,
   "u": 21,
   "v": 22,
   "w": 23,
   "x": 24,
   "y": 25,
   "z": 26,
   "A": 27,
   "B": 28,
   "C": 29,
   "D": 30,
   "E": 31,
   "F": 32,
   "G": 33,
   "H": 34,
   "I": 35,
   "J": 36,
   "K": 37,
   "L": 38,
   "M": 39,
   "N": 40,
   "O": 41,
   "P": 42,
   "Q": 43,
   "R": 44,
   "S": 45,
   "T": 46,
   "U": 47,
   "V": 48,
   "W": 49,
   "X": 50,
   "Y": 51,
   "Z": 52
}
# for i in listOfRuckSacks:
#     compartment1 = set(i[:(len(i)>>1)])
#     compartment2 = set(i[(len(i)>>1):])
#     # print(len(compartment1),len(compartment2))
#     # print((compartment1,compartment2))
#     # for j in compartment2:
#     sum += dictCharacters[list(compartment1.intersection(compartment2))[0]]

for i in range(0,len(listOfRuckSacks),3):
    elf1 = listOfRuckSacks[i]
    elf2 = listOfRuckSacks[i+1]
    elf3 = listOfRuckSacks[i+2]
    onetwo = set(elf1).intersection(elf2)
    onetwothree = set(onetwo).intersection(elf3)
    sum += dictCharacters[list(onetwothree)[0]]

print(sum)
