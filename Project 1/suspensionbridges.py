import math

def cable_length(a, d):
    return 2*a * math.sinh(d/(2*a))

def check_length(a, d):
    return (a * math.cosh(d / (2 * a))) - a

def find_a(s, d):
    low = 0
    high = d ** 2
    mid = (low + high) / 2
    count = 0
    cl = check_length(mid, d)
    while s != round(cl,5):
        mid = (low + high) / 2
        cl = check_length(mid, d)
        if cl > s:
            low = mid
            count += 1
        elif cl < s:
            high = mid
            count +=1
        else:
            return mid
    return mid

# Get kattis input
line = input()
d = int(line.split()[0])
s = int(line.split()[1])

a = find_a(s, d)
print(cable_length(a, d))