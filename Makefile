

make:
	gcc main.c calendar_module.c -o plant_scheduler
simple:
	gcc main.c -o plant_scheduler
debug:
	gcc -g main.c calendar_module.c -o plant_scheduler
clean:
	rm ./plant_scheduler
