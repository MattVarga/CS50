# The program is intended to Estimate the run time of large NC programs based on the feed rate
# and the sum of all movements commanded

print('')
print("CNC Program Runtime Estimator  Created by:  Matt Varga")
print('')
file = open(input("Enter NC file name to be analyzed: "), 'r')

# divides the files to read by lines
lines = file.readlines()

#initializes all variables to 0
x_dist = 0.0
y_dist = 0.0
z_dist = 0.0
new_x = 0.0
new_y = 0.0
new_z = 0.0
current_x = 0.0
current_y = 0.0
current_z = 0.0
#feed in inches per minute
feed = 0.0

for line in lines:

    # splits the lines into strings with the seperator being the string creating individual commands
    commands = line.split(' ')

    # searches through individual commands
    for command in commands:
        # finds x axis moves
        if command.startswith('X'):
            current_x= float(command[1:])
        # finds y axis moves
        if command.startswith('Y'):
            current_y = float(command[1:])
        # finds z axis moves
        if command.startswith('Z'):
            current_z = float(command[1:])
        #finds the feed rate
        if command.startswith('F'):
            feed= float(command[1:])

    #calculates how much it has moved in total
    x_dist += abs(new_x - current_x)
    y_dist += abs(new_y - current_y)
    z_dist += abs(new_z - current_z)
    new_x = current_x
    new_y = current_y
    new_z = current_z
xy_dist = x_dist + y_dist
run_time = xy_dist / feed

#prints to get user input and return results
print(f"File Name: ",(file.name))
print(f"{x_dist:.2f} X-Axis Inches Traveled")
print(f"{y_dist:.2f} Y-Axis Inches Traveled")
print(f"{z_dist:.2f}  Z-Axis Inches Traveled")
print(f"Estimated Total Run Time: {run_time:.2f} Minutes")

# closes the input file
file.close()
