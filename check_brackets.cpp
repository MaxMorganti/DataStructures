#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    string text;
    getline(cin, text);

    stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];
        // use next character to initialize a bracket struct.
        Bracket next_brack = Bracket(next, position);
        if (next == '(' || next == '[' || next == '{') {
            // add to stack
            opening_brackets_stack.push(next_brack);
        }
        if (next == ')' || next == ']' || next == '}') {            
            //make sure stack isn't empty
            if(opening_brackets_stack.empty()) {
            	cout << position + 1;
            	return 2;
            }
            //check top item of stack
        	Bracket top_stack = opening_brackets_stack.top();
        	//if it pairs off with next element, remove it
        	if(top_stack.Matchc(next)) {
        		opening_brackets_stack.pop();
        	}
        	//if discrepancy is found, return position
        	else {
        		cout << position+1;
        		return 1;
        	}
            
        }
    }
    // check if stack is empty
    if(opening_brackets_stack.empty()) {
    	cout << "Success";	
    }
	else {
		cout << (opening_brackets_stack.top()).position + 1;
	}
    return 0;
}
