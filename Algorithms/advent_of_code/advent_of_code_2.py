
""" 
R P S
A B C
X Y Z
"""

rockPaperScissorsPairs = {
    "AX": 1 + 3,
    "AY": 2 + 6,
    "AZ": 3 + 0,
    "BX": 1 + 0,
    "BY": 2 + 3,
    "BZ": 3 + 6,
    "CX": 1 + 6,
    "CY": 2 + 0,
    "CZ": 3 + 3,
    "AY": 1 + 3,
    "AZ": 2 + 6,
    "AX": 3 + 0,
    "BX": 1 + 0,
    "BY": 2 + 3,
    "BZ": 3 + 6,
    "CZ": 1 + 6,
    "CX": 2 + 0,
    "CY": 3 + 3
}

totalscore = 0

for item in listOfGames:
    symbols = item.replace(" ","")
    totalscore += rockPaperScissorsPairs[symbols]

print(totalscore)
