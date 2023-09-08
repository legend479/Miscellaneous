_ = input()

arr = [int(num) for num in input().split(" ")]

for num in sorted(arr):
    print(num, end=" ")
print()