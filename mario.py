from cs50 import get_int
while True:
    height = get_int("please enter a hight between 1 and 8:")
    if height <= 0 or height > 8:
        continue   
    
    for i in range(1, height + 1):
            num_hashes = i
            num_spaces = height - num_hashes
            print(" " * num_spaces, end="")
            print("#" * num_hashes)
    break
