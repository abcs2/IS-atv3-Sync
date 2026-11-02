objects/sync_car.o: source/sync_car.c source/sync_car.h
	gcc -c -pthread source/sync_car.c -o objects/sync_car.o

objects/sync_car-runner.o: source/sync_car-runner.c source/sync_car.h
	gcc -c -pthread source/sync_car-runner.c -o objects/sync_car-runner.o

sync_car: objects/sync_car.o objects/sync_car-runner.o
	gcc -pthread objects/sync_car.o objects/sync_car-runner.o -o sync_car

clean:
	rm -f objects/*.o sync_car

.PHONY: clean