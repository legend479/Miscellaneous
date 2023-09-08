import random 

max_len = 100000
max_elem = 100000

len = random.randint(1,max_len)
print(len)
for i in  range(len-1):
    print(random.randint(-max_elem,max_elem),end=" ")

print(random.randint(-max_elem,max_elem))