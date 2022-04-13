exec = gen_ten.exe
sources = $(wildcard src/*.cpp)
objects = $(sources:.cpp=.o)
flags = -g

$(exec) : $(objects)
	g++ $(objects) $(flags) -o $(exec)

%.o: %.cpp %include/.h
	g++ -c -I%include $(flags) $< -o $@ 

clean:
	@-rm src/*.o
	@-rm *.exe
	@echo "Clean Complete."

run:
	@make -s
	@./gen_ten
	@make clean -s
cr:
	@make clean -s
	@make -s
	@./gen_ten
	@make clean -s