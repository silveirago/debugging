# Debugging

~~ Troubleshooting / Finding the Problem ... ~~

~ Start using the codes in this folder. Test your buttons and potentiometers, see if they are working right. They should have a steady response, like HIGH/LOW for buttons and 0-1023 for potentiometers. If they are no working fine with these examples it's because there's a problem in your circuit.

~ Your code is not compiling ~
In the IDE, try to read in the dialogue box, the black box below the IDE, what the problem is. Sometimes it seems Greek, sometimes it gives you a good idea of ​​what it can be.
Did you choose the right board? Did you choose the right USB port? Have you downloaded and installed all libraries correctly?
Did everything right go so far? You've read in your code and can't find any error? Be humble, it is not because you have read 10 times that it means you read it right. Do not underestimate your tiredness! Take the time to read the code again. Often it is a different letter that we wrote, or missed a ";". Search, search, search, rest, search.

~ Your code compiles, so you do not know where the problem is ~
First, be humble, do not blame the Arduino, do not blame the board, do not blame the computer, the problem is (98% chance) you. In this case, the ideal is first debugging the circuit. For this, you MUST have a multimeter. Use the multimeter to check the continuity of your circuit. First, check the continuity of all the GNDs, 5Vs, and, after, each component, or go straight to the "faulty" component if it is only one or more problematic components. If you find that there is a lack of continuity somewhere, redo the soldering, or rearrange the jumpers. If the problem continues, you may have a faulty component. If it's just one, or another component that does not work, it's very likely that the problem is in the circuit and not in the code.

~ You checked your circuit and you're sure it's all right ~
Debugging the code is more complicated, there is no exact recipe. It is reading, line by line, that you'll might find the possible problem. Often your algorithm is wrong. That means you are not giving the correct instructions to the Arduino, something is in the wrong order, or, who knows?
In this case, use the serial monitor a lot! Try printing what's coming out of various parts of your code, one at a time. Sometimes you think it should be coming out "10-100", but it's coming out "-2". Why? Then, you'll have to do a mental gymnastics to find out. It can be difficult, but for me it's one of the nicest parts of the process.
A good practice is to put on paper every task your Arduino is doing and try to simulate what numbers are coming out of there, do the calculations, do the "IFs" and see what actually is coming out.

~ It still does not work, I'm in doubt ~
Take a step back. If you used a multiplexer and it is not working without your code, try using the library example, it's still not working, it's because your system is having problems. Using the native Arduino and library examples is a better way to test the problem in your circuit or without code. If it works there, the problem is your code, does not work, the problem is no circuit!

~ The Potentiometer, or any other analog sensor, is sending a signal when it should not ~
Every pot has an unstable nature. We try to solve this in the code, setting a minimum value that must be changed for an event to happen. In general this minimum is stored in the variable "varThreshold". Increase the value of it and see if it improves.
