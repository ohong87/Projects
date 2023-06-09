CXX = g++
CPPFLAGS = -Wall -g
# BIN_DIR = bin

all: interpreter

interpreter: Interpreter.cpp add.o div.o end.o goSub.o goTo.o if.o let.o mult.o printAll.o print.o program.o return.o sub.o
	$(CXX) $(CPPFLAGS) $^ -o $@

add.o: AddStatement.cpp AddStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

div.o: DivStatement.cpp DivStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

end.o: EndStatement.cpp EndStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

goSub.o: GoSubStatement.cpp GoSubStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

goTo.o: GoToStatement.cpp GoToStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

if.o: IfStatement.cpp IfStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

let.o: LetStatement.cpp LetStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

mult.o: MultStatement.cpp MultStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

printAll.o: PrintAllStatement.cpp PrintAllStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

print.o: PrintStatement.cpp PrintStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

program.o: ProgramState.cpp ProgramState.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

return.o: ReturnStatement.cpp ReturnStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

sub.o: SubStatement.cpp SubStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@