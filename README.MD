Matt Varga                   St.Charles, Missouri                 NC Estimator CS50

    As a bit of a back ground I currently work as a CNC machinist and often post process 40,000+ line programs on a regular basis.
Our current software is lacking in producing accurate estimated run times, Programs can be run in backpot on the machine to get
estimated times but with older processors they are often limited to a 255 bit buffer size and can take 20 minutes to backplot a
program that takes 30 minutes to actually execute, so often it is easier to just run the program and record the execution time than
it is to backplot, so I've decided it would be worth while to make a runtime estimator that used the actual .nc file to create an
anticipated run time.

    I've created a program that processes large .NC files and produces an estimated Machine run time based on the
total movement of each axis(X,Y,Z) and the programmed feed rate.  Upon program execution it will display the File name which was read
in, the total travel in inches of each axis, and the Estimated run time. it works with both standard inch format and metric mm format.
It is capable of executing and returning the results of a 40,000+ line .NC file in less than 1 second without any preperation of the
file.
