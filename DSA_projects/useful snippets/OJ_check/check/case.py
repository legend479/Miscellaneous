#!/bin/python3
import random
import string

# Step 1
Limit = 2 * 10**5
Total_sum_lim = 6 * 10**5
T = random.randint(1, min(Limit, Total_sum_lim))
print(T)

total_sum = 0

# Step 2
for _ in range(T):
    # Step 2a
    remaining_capacity = Total_sum_lim - total_sum
    max_strings = min(remaining_capacity // 10**5, Limit)
    if max_strings < 1:
        N = 1
    else:
        N = random.randint(1, max_strings)
    print(N)

    # Step 2c
    for _ in range(N):
        # Step 2c(i)
        remaining_capacity = min(remaining_capacity, Limit)
        max_length = min(remaining_capacity, Limit)
        if max_length < 1:
            M = 1
        else:
            M = random.randint(1, max_length)
        # Step 2c(ii)
        random_string = ''.join(random.choice(string.ascii_lowercase) for _ in range(M))
        # Step 2c(iii)
        print(M, random_string)

        total_sum += N * M
