words = input().split()

if len(words) == len(set(words)):
    print("yes")
    exit()

print("no")