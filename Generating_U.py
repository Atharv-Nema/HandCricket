'''This is a file that generates all the values of U_bowl and U_bat in a list
This just needs to be executed once to precompute the values of U_bowl and U_bat'''

#Generating U_bowl
U_bowl = []#U_bowl[x] is the utility for the bowler if the bowler has scored x runs
U_bowl.append(1/12)
for i in range(1,1001):
    num = 0
    for j in range(1,7):
        if i - j >= 0:
            num += U_bowl[i - j]/(1 - U_bowl[i - j])
        else:
            num += 0
    denom = 0
    for j in range(1,7):
        if i - j >= 0:
            denom += (1/(1 - U_bowl[i - j]))
        else:
            denom += 1
    U_bowl.append(num/denom)
print(U_bowl)

#Generative U_bat
U_bat = []#U_bat[x] is the utility for the batsman if the bowler has scored x runs
U_bat.append(11/12)
for i in range(1,1001):
    denom = 0
    for j in range(1,7):
        if i - j >= 0:
            denom += (1/(U_bat[i - j]))
        else:
            denom += 1
    U_bat.append(5/denom)
print(U_bat)