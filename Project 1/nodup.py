words = input().split()
seen = set()

for word in words:
    if word in seen:
        print("no")
        exit()
    else:
        seen.add(word)

print("yes")