from cs50 import get_float
import math

while True:
    total = get_float("how much change is owed?")
    if total < 0:
        continue
  
    totalPennies = round(total * 100)
    #finds number oF quarters
    quarters = totalPennies // 25
    newTotal = totalPennies - (quarters * 25)
    #finds number of dimes
    dimes = newTotal // 10
    newTotal = (totalPennies - ((quarters * 25) + (dimes * 10)))
    #finds number of nickles
    nickles = newTotal // 5
    newTotal = (totalPennies - ((quarters * 25) + (dimes * 10) + (nickles * 5)))
    #finds number of pennies
    pennies = newTotal
    # prints the total coins required
    print(f"total coins: {quarters + dimes + nickles + pennies}")
    break
