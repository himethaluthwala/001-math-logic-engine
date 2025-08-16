#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm> // for transform()

// main function prototypes
std::vector<std::string> Tokenise(const std::string &input);
void Parse(const std::vector<std::string> &tokens);
void Evaluate();

enum class Mode { LOGIC, MATH };

// converts string to uppercase
std::string ToUpper(const std::string &str) {

            std::string upperStr = str;

            std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), [](unsigned char c) { return std::toupper(c); });

            return upperStr;

} 

// checks for math or logic operator
bool IsOperator(const std::string &token) {
    static const std::unordered_set<std::string> operators = {
        "+", "-", "*", "/", "^", "(", ")",  // math
        "AND", "OR", "NOT", "XOR"           // logic
    };

    if (token.empty()) return false;

    return operators.find(ToUpper(token)) != operators.end();
}

// detect mode based on keywords
Mode DetectMode(const std::string &input) {
    std::string upperStr = ToUpper(input);
    if (upperStr.find("AND") != std::string::npos ||
        upperStr.find("OR") != std::string::npos ||
        upperStr.find("NOT") != std::string::npos ||
        upperStr.find("TRUE") != std::string::npos ||
        upperStr.find("FALSE") != std::string::npos) {
        return Mode::LOGIC;
    }
    return Mode::MATH;
}
 
int main (void) {
    std::string input;
    std::cout << "Math / Logic Engine (type 'exit' to quit)\n"; 

    while (true) {
        // read input
        std::cout << "> ";
        std::getline(std::cin, input);
        //std::cout << input << "\n";
 
        if (input == "exit") break;
       
        // Detect mode
        Mode mode = DetectMode(input);
        if (mode == Mode::LOGIC) {
            std::cout << "[Mode] Logic\n";
        } else {
            std::cout << "[Mode] Math\n";
        }

        auto tokens = Tokenise(input); 

        for (auto s : tokens) {
            std::cout << s << "\n";
        }
    }

    // 1. tokenise the input
    /*auto tokens = Tokenise(input);

    std::cout << "\n";

    for (auto s : tokens) {
        std::cout << s << "\n";
    } */

    // 2. parse the data into a tree
    //Parse(tokens); 

    // 3. evaluate the expression by traversing the tree
    //Evaluate();   

    return 0;
}

 

std::vector<std::string> Tokenise(const std::string &input) {
    std::vector<std::string> tokens;
    std::string t;

    for (size_t i = 0; i < input.length(); ++i) {
        // check for empty space
        if (input[i] == ' ') {
            if (!t.empty()) {
                tokens.push_back(t);
                t.clear();
            }
            continue;
        }

        // check for math operator
        std::string c(1, input[i]);
        if (IsOperator(c)) {
            if (!t.empty()) {
                tokens.push_back(t);
                t.clear();
            }
            tokens.push_back(c);
            t.clear();
            continue;
        }    

        // check for logic operator
        if (IsOperator(t)) {
            tokens.push_back(t);
            t.clear();
            continue;
        }     
        t.push_back(input[i]);
    }

    // Push the last token if any
    if (!t.empty()) {
        tokens.push_back(t);
    }

    return tokens;
}

void Parse(const std::vector<std::string> &tokens) {
    // TODO...
}

void Evaluate() {
    // TODO...
}