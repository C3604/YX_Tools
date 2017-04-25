objs = main.o INIParser.o
cc =   g++
exec_name = ini_parser
head_file = INIParser.h 

$(exec_name):$(objs)
	$(cc) -o $(exec_name) $(objs)

$(objs): $(head_file)

.PHONY:clean

clean:
	-rm $(exec_name).exe $(exec_name) $(objs)
