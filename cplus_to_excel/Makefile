Head_repo= ./libxl-3.5.4.1/include_cpp/ 
Lib_repo = ./libxl-3.5.4.1/lib64/ 

All:
	rm -f main
	g++ -I $(Head_repo) -L $(Lib_repo) -lxl -Wl,-rpath,$(Lib_repo) -g main.cpp -o main
	./main
	rm -f main
