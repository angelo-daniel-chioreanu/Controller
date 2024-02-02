monitor: controller.o monitorctrl.o
	g++ -g -o monitor controller.o monitorctrl.o
controller.o: controller.cpp controller.h
	g++ -std=c++11 -g -c -Wall controller.cpp
monitorctrl.o: monitorctrl.cpp controller.h
	g++ -std=c++11 -g -c -Wall monitorctrl.cpp
clean:
	rm -f monitor *.o
