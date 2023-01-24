# Kattis inputs
people = input().split()
strengths = input().split()
speeds = input().split()

# Convert lists to int lists
people = [int(person) for person in people]
strengths = [int(strength) for strength in strengths]
speeds = [int(speed) for speed in speeds]

# Creating list of people's strengths
people_strengths = []
for i in range(len(people)):
    for j in range(people[i]):
        people_strengths.append(strengths[i])

# Make pairs
pairs = []
i = 0
while i < len(people_strengths):
    pairs.append(people_strengths[i] + people_strengths[i+1])
    i += 2

# Make pairs
pairs2 = []
i = 0
while i < len(people_strengths) / 2:
    pairs2.append(people_strengths[i] + people_strengths[len(people_strengths) - (i+1)])
    i += 1

# Mulitply lowest strength by highest speed
pairs.sort()
pairs2.sort()
speeds.sort(reverse=True)

speeds1 = []
speeds2 = []

for i in range(len(speeds)):
    speeds1.append(speeds[i] * pairs[i])
    speeds2.append(speeds[i] * pairs2[i])

mins = [min(speeds1), min(speeds2)]
print(max(mins))