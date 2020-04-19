
LIB = ./libft/libft.a
SOURCE = ./main.c ./calendar_module.c
OUT = plant_scheduler

make:
	@make -C libft
	@gcc $(SOURCE) $(LIB) -o $(OUT)
edit:
	@vi main.c
simple:
	@gcc main.c -o plant_scheduler
debug:
	@gcc -g $(SOURCE) $(LIB) -o $(OUT)

memcheck: debug
	valgrind -v --leak-check=yes ./$(OUT)

clean:
	@rm ./plant_scheduler
	@if [ -e $(OUT).dSYM ]; then rm -rf $(OUT).dSYM; fi
