#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// ********************************** //
// This function prints out the stack //
// ********************************** //
void stackOutput(std::string stack) {
    if (stack.length() == 0) {
        std::cout << "Stack = ['$']" << std::endl;
    }
    else {
        std::cout << "Stack = ['$', ";
        for (int i = stack.length()-1; i >= 0; i--) {
            if (i != 0) {
                std::cout << "'" << stack[i] << "', ";
            }
            else {
                std::cout << "'" << stack[i] << "'";
            }
        }
        std::cout << "]" << std::endl;
    }
}

// ************************* //
// This is the main function //
// ************************* //
int main() {

    // --------------------- //
    // Creates Parsing Table //
    // --------------------- //
    std::string parsingTable[5][8] = {
    //    a    +   -   *   /    (    )   $ 
    //  -------------------------------------
        {"TQ", "", "", "", "", "TQ", "", ""},       // E
        {"", "+TQ", "-TQ", "", "", "", "0", "0" },  // Q
        {"FR", "", "", "", "", "FR", "", ""},       // T
        {"", "0", "0", "*FR", "/FR", "", "0", "0"}, // R
        {"a", "", "", "", "", "(E)", "", ""},       // F    
    };

    // ------------------------------- //
    // Creates my vectors for NT and T //
    // ------------------------------- //
    std::vector<char> NT = {'E', 'Q', 'T', 'R', 'F'};
    std::vector<char> T = {'a', '+', '-', '*', '/', '(', ')', '$'};

    // User input //
    std::string userInput;
    std::cout << "Please enter a string: ";
    std::getline(std::cin, userInput);
    std::cout << "Input = " << userInput << std::endl;

    // ------------------------------- //
    // Creates variables i'll be using //
    // ------------------------------- //
    bool valid = true;                                  // If string can be passed.
    // std::string userInput = "*a$";
    // std::string userInput = "(a+a)$";                   // User input [Good]
    // std::string userInput = "(a+a)*a$";                 // User input [Good]
    // std::string userInput = "a*(a/a)$";                 // User input [Good]
    // std::string userInput = "a(a+a)$";                  // User input [Bad]
    // std::string userInput = "(a+a)e$";                  // User input [Bad]
    int increment = 0;                                  // For knowing which char we're on in userInput
    char currentValue = userInput[increment];           // For knowing which char we're on in userInput
    std::string currentValue_string;                    // Converts char to string. [lazy code..]
    std::string stringHolder = "";                      // Final product should be equal to the userInput.
    std::string tProcess;                               // Holds the terminal/non-terminal process [i.e. 'FRQ']
    std::vector<char>::iterator tProcessIterator;       // Creates iterator to find items in our vectors T and NT.
    std::vector<char>::iterator currentValueIterator;
    std::vector<char>::iterator nonTerminalIterator;

    // *************************************** //
    // Process to initailize tProcess variable //
    // *************************************** //

    // -------------------------------- //
    // Finds x position of currentValue //
    // -------------------------------- //
    std::vector<char>::iterator initializerX = std::find(T.begin(), T.end(), currentValue);
    // std::cout << "Position = " << initializerX - T.begin() << std::endl;

    // --------------------------------------------------------------------- //
    // Loop that finds y position of first occurance of PT[currentValue][NT] //
    // --------------------------------------------------------------------- //
    for (int x = 0; x < 5; x++) {
        if (parsingTable[x][initializerX - T.begin()] != "" && tProcess == "") {
            std::string firstStack;
            firstStack += NT[x];
            tProcess.append(firstStack);
            stackOutput(tProcess);
            tProcess.erase(tProcess.begin());
            tProcess.append(parsingTable[x][initializerX - T.begin()]);
        }
    }
    stackOutput(tProcess);

    // ***************************************************** //
    // Loop through tProcess until stringHolder == userInput //
    // ***************************************************** //
    while (true) {

        tProcessIterator = std::find(T.begin(), T.end(), tProcess[0]);
        currentValueIterator = std::find(T.begin(), T.end(), currentValue);
        nonTerminalIterator = std::find(NT.begin(), NT.end(), tProcess[0]);
        
        // ----------------------------------------- //
        // Handles if we reached the end of tProcess //
        // ----------------------------------------- //
        if (tProcess.length() == 0) {
            stringHolder += "$";
            if (stringHolder != userInput) {
                valid = false;
            }
            else {
                std::cout << "String is accepted and VALID!" << std::endl;
                return 0;
            }
        }
        
        // ------------------------------------------ //
        // Handles if first value is a terminal value //
        // ------------------------------------------ //
        else if (tProcessIterator != T.end()) {

            // if tProcess is a terminal and its equal to current value, then great //
            if (tProcess[0] == currentValue) {
                increment += 1;
                currentValue = userInput[increment];
                stringHolder += tProcess[0];        // Add it to stringHolder
                tProcess.erase(tProcess.begin());   // Remove terminal value from tProcess
                stackOutput(tProcess);
            }
            // if tProcess is a terminal and not equal to current value, then string invalid! //
            else {
                valid = false;
            }
        }

        // ---------------------------------------------- //
        // Handles if first value is a non-terminal value //
        // ---------------------------------------------- //
        else {                        
            int nonTerminal_Position = nonTerminalIterator - NT.begin();    // x position [goes first]
            int currentValue_Position = currentValueIterator - T.begin();   // y position [goes second]
            int terminalEpsilon_Position = 7;                               // hard-coded because lazy.
            
            // ------------------------------ //
            // If PT[NT][CurrentValue] exists //
            // ------------------------------ //

            if (parsingTable[nonTerminal_Position][currentValue_Position] != "") {
                currentValue_string += currentValue; // converts char to string - LAZY

                // If PT[x][y] == currentValue [meaning Terminal matches up] //
                if (parsingTable[nonTerminal_Position][currentValue_Position] == currentValue_string) {
                    tProcess.replace(0,1,parsingTable[nonTerminal_Position][currentValue_Position]);
                    stackOutput(tProcess);
                    stringHolder += currentValue;
                    increment += 1;
                    currentValue = userInput[increment];
                    tProcess.erase(tProcess.begin());
                    stackOutput(tProcess);
                }

                else if (parsingTable[nonTerminal_Position][currentValue_Position] == "0") {
                    tProcess.erase(tProcess.begin());
                    stackOutput(tProcess);
                }
                // If we simply find anything but our terminal matching up with currentValue
                else {
                    tProcess.replace(0,1,parsingTable[nonTerminal_Position][currentValue_Position]);
                    stackOutput(tProcess);
                }

                currentValue_string = ""; // clears out lazy code.
            }

            // ------------------------------------------------ //
            // If PT[NT][CurrentValue] DNE but PT[NT][$] exists //
            // ------------------------------------------------ //
            else if (parsingTable[nonTerminal_Position][currentValue_Position] == "" && parsingTable[nonTerminal_Position][terminalEpsilon_Position] != "") {
                tProcess.replace(0,1,parsingTable[nonTerminal_Position][terminalEpsilon_Position]);
                stackOutput(tProcess);
                tProcess.erase(tProcess.begin());    
                stackOutput(tProcess);
            }

            // --------------------------------------------- //
            // If PT[NT][CurrentValue] DNE and PT[NT][$] DNE //
            // --------------------------------------------- //
            else if (parsingTable[nonTerminal_Position][currentValue_Position] == "" && parsingTable[nonTerminal_Position][terminalEpsilon_Position] == "") {
                stackOutput(tProcess);
                valid = false;
            }
        }

        // If at this point valid = false, then we stop and say its invalid //
        if (valid == false) {
            std::cout << "String is not accepted and INVALID!" << std::endl;
            return 0;
        }

        // std::cout << "currentValue = " << currentValue << std::endl;
        // std::cout << "String Holder = " << stringHolder << std::endl;
        // std::cout << "tProcess value = " << tProcess << std::endl;
        // std::cout << "--------------------------" << std::endl;
    }
}
