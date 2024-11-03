#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class Chatbot {
private:
    map<string, string> responses;

public:
    Chatbot() {
        // Simple responses
        responses["hi"] = "Hello! How can I help you today?";
        responses["how are you"] = "I'm just a program, but thanks for asking!";
        responses["bye"] = "Goodbye! Have a great day!";
    }

    string getResponse(const string& input) {
        string lowerInput = input;
        transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);
        if (responses.find(lowerInput) != responses.end()) {
            return responses[lowerInput];
        }
        return "I'm sorry, I don't understand that.";
    }
};

int main() {
    Chatbot bot;
    string userInput;

    cout << "Chatbot: Hi! I'm here to assist you. Type 'bye' to exit." << endl;

    while (true) {
        cout << "You: ";
        getline(cin, userInput);
        if (userInput == "bye") {
            cout << "Chatbot: Goodbye!" << endl;
            break;
        }
        cout << "Chatbot: " << bot.getResponse(userInput) << endl;
    }

    return 0;
}
