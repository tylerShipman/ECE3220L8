//============================================================================
// Name        : ECE3220L8.cpp
// Author      : Tyler Shipman
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#define MAX 5
using namespace std;



class Message{

	protected:
		string message; //Holds message

	public:
		Message();
		Message(string);
		~Message();
		virtual void printInfo();//Needs to be redefined. Similar to abstract in java

};

Message::Message(){

	cout<<"Please enter a message to convert into Morse code: "<<endl;
	cin>>message;

}

Message::Message(string m){

	message = m;

}

Message::~Message(){


}

void Message::printInfo(){

	cout<< message<<endl;

}

class MorseCodeMessage : public Message{

	private:
		//stores letters in morse code. index correlates to value - 97
		string letterLookup[26] = {".-", "-...", "-.-.", "-..", ".", "..-.",
				"--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
				".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
				"-.--", "--.."};
		//stores numbers in morse code. index correlates to value
		string numberLookup[10] = {"-----", ".----", "..---", "...--", "....-", ".....",
						"-....", "--...", "---..", "----."};


	public:
		MorseCodeMessage(string m);	//Message to translate
		~MorseCodeMessage();

		string * translatedMessage;//Stores translated message

		void translate();//translates message
		void printInfo();//prints trans msg



};

MorseCodeMessage::MorseCodeMessage(string m) : Message(m){

	translate();

}

MorseCodeMessage::~MorseCodeMessage(){

	delete[] translatedMessage;

}

void MorseCodeMessage::translate(){

	translatedMessage = new string[message.length()];

		for (int i = 0; i < message.length(); i++) {
			if (isalpha(message[i])) {		//Check input is a letter
				translatedMessage[i] = letterLookup[tolower(message[i]) - 97];	//Subtract 97 to get index val from ascii value.
			}
			else if(isspace(message[i])){ // Check for space
				translatedMessage[i] = "/";
			}
			else if(isdigit(message[i])){//check for number
				translatedMessage[i] = numberLookup[tolower(message[i]) - 48];//sub 48 from ascii val to get index val
			}
			else {
				translatedMessage[i] = "#"; //For unrecognized chars i.e ?,#,$,%,^,etc.
			}
		}

}

void MorseCodeMessage::printInfo(){

	cout << message << endl;

		for (int i = 0; i < message.length(); i++) {
			cout << translatedMessage[i] << "  ";
		}
		cout << endl;

}

class MessageStack{

	public:
		MessageStack();
		MessageStack(Message*);
		~MessageStack();

		Message* ptrStack[MAX];//Max size of 5
		int topOfStack;//Top of stack index

		Message* pop();//Pops last LIFO
		void push(Message* object);//pushes last LIFO
		void printStack();//prints contents


};

MessageStack::MessageStack(){

	topOfStack = 0;//initializes stack with size 0

}

MessageStack::MessageStack(Message* message){

	topOfStack = 0;
	push(message);

}

MessageStack::~MessageStack(){

}

void MessageStack::push(Message* object){

	if(topOfStack != MAX){//pushes if stack has not reached max
		ptrStack[topOfStack] = object;
		topOfStack++;
	}
	else
		cout<<"Stack is full"<<endl;


}

Message* MessageStack::pop(){

	if (topOfStack == 0) {
			cout << "\nStack empty, can't pop any more" << endl;
			return NULL;
		}
		else {
			Message *hold = ptrStack[topOfStack];
			topOfStack--;
			return hold;
		}

}

void MessageStack::printStack(){
	cout<<"Stack: "<<endl;
	for (int i = 0; i < topOfStack; i++) {
			ptrStack[i]->printInfo();
		}
	cout<<endl<<"___________________________________________________________________________________"<<endl<<endl;

}


int main() {

		//Message msg0("Tyler");

		MorseCodeMessage msg1("Tyler123 Shipman444?");
		MorseCodeMessage msg2("Tyler Shipman");

		MessageStack stack;
		//stack.push(&msg0);
		stack.push(&msg1);
		stack.push(&msg2);

		stack.printStack();
		stack.pop();
		stack.printStack();
		stack.pop();
		stack.printStack();
		stack.pop();


		stack.printStack();

		return 0;
}
