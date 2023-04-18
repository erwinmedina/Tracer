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
    // std::string userInput = "*a$";                      // User input [Good]
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

    // -------------------------------------------------- //
    // Finds position of currentValue in Terminals vector //
    // -------------------------------------------------- //
    std::vector<char>::iterator initializerX = std::find(T.begin(), T.end(), currentValue);

    // ------------------------------------------------------------------- //
    // Loop that finds position of first occurance of PT[NT][CurrentValue] //
    // ------------------------------------------------------------------- //
    for (int x = 0; x < 5; x++) {
        if (parsingTable[x][initializerX - T.begin()] != "" && tProcess == "") {
            tProcess += NT[x];                                                  // Adds NT to Stack
            stackOutput(tProcess);                                              // Prints Stack
            tProcess.erase(tProcess.begin());                                   // Removes NT from stack
            tProcess.append(parsingTable[x][initializerX - T.begin()]);         // Adds intersect value into stack [i.e. "TQ"]
            stackOutput(tProcess);                                              // Prints Stack
        }
    }

    // ***************************************************** //
    // Loop through tProcess until stringHolder == userInput //
    // ***************************************************** //
    while (true) {

        tProcessIterator = std::find(T.begin(), T.end(), tProcess[0]);          // Finds position of current Stack value in Terminal vector [i.e. "aFRQ"]
        currentValueIterator = std::find(T.begin(), T.end(), currentValue);     // Finds position of current Value in Terminal vector [i.e. "(a+a)$"]
        nonTerminalIterator = std::find(NT.begin(), NT.end(), tProcess[0]);     // Finds position of current Stack value in NT vector [i.e. "FRQ"]

        // ----------------------------------------- //
        // Handles if we reached the end of tProcess //
        // ----------------------------------------- //
        if (tProcess.length() == 0) {                                           // Stack is empty.
            stringHolder += "$";                                                // Add "$" to stringHolder.
            if (stringHolder != userInput) {                                    // stringHolder != userInput
                valid = false;                                                  // string not accepted.
            }
            else {                                                              // stringHolder == userInput
                std::cout << "String is accepted and VALID!" << std::endl;      // Accepted. Yay.
                return 0;                                                       // End program.
            }
        }
        
        // ------------------------------------------ //
        // Handles if first value is a terminal value //
        // ------------------------------------------ //
        else if (tProcessIterator != T.end()) {

            if (tProcess[0] == currentValue) {                                  // stack value is a terminal and what we're looking for.
                increment += 1;
                currentValue = userInput[increment];                            // Update current value [i.e: look at 'a' instead of '(' in "(a+a)$"]
                stringHolder += tProcess[0];                                    // Add it to stringHolder
                tProcess.erase(tProcess.begin());                               // Remove terminal value from tProcess
                stackOutput(tProcess);                                          // Print updated stack.
            }
            else {                                                              // stack value is a terminal but not what we're looking for. 
                valid = false;                                                  // string cannot be passed. 
            }
        }

        // ---------------------------------------------- //
        // Handles if first value is a non-terminal value //
        // ---------------------------------------------- //
        else {                        
            int nonTerminal_Position = nonTerminalIterator - NT.begin();                                // x position [goes first]
            int currentValue_Position = currentValueIterator - T.begin();                               // y position [goes second]
            int terminalEpsilon_Position = 7;                                                           // hard-coded epsilon position
            
            // ------------------------------ //
            // If PT[NT][CurrentValue] exists //
            // ------------------------------ //
            if (parsingTable[nonTerminal_Position][currentValue_Position] != "") {
                currentValue_string += currentValue;                                                    // converts char to string.

                // If PT[x][y] == currentValue [meaning Terminal matches up] //
                if (parsingTable[nonTerminal_Position][currentValue_Position] == currentValue_string) {
                    tProcess.replace(0,1,parsingTable[nonTerminal_Position][currentValue_Position]);    // If "a" is found, replace "E" with "a" in stack.
                    stackOutput(tProcess);                                                              // Print updated stack
                    stringHolder += currentValue;                                                       // Add 'a' to string holder.
                    increment += 1;                                                                     
                    currentValue = userInput[increment];                                                // Update current value [i.e: look at 'a' instead of '(' in "(a+a)$"]
                    tProcess.erase(tProcess.begin());                                                   // Remove 'a' from the stack since we found value we were looking for.
                    stackOutput(tProcess);                                                              // Print updated stack.
                }

                // If PT[x][y] != currentValue but an epsilon exists at that position - Use epsilon //
                else if (parsingTable[nonTerminal_Position][currentValue_Position] == "0") {
                    tProcess.erase(tProcess.begin());                                                   // i.e. "FRQ" and "F" goes to epsilon. Simply remove F
                    stackOutput(tProcess);                                                              // Print updated stack "RQ"
                }
                // If PT[x][y] != currentValue and PT[x][y] != epsilon. Simply replace.
                else {
                    tProcess.replace(0,1,parsingTable[nonTerminal_Position][currentValue_Position]);    // If "RQ" is found, replace "F" with "RQ" in stack.
                    stackOutput(tProcess);                                                              // Print updated stack.
                }

                currentValue_string = "";                                                               // clears out char to string conversion for next iteration.
            }

            // ------------------------------------------------ //
            // If PT[NT][CurrentValue] DNE but PT[NT][$] exists //
            // ------------------------------------------------ //
            else if (parsingTable[nonTerminal_Position][currentValue_Position] == "" && parsingTable[nonTerminal_Position][terminalEpsilon_Position] != "") {
                tProcess.replace(0,1,parsingTable[nonTerminal_Position][terminalEpsilon_Position]);     // Replace NT in stack with epilson.
                tProcess.erase(tProcess.begin());                                                       // Remove value in stack.
                stackOutput(tProcess);                                                                  // Print updated stack.
            }

            // --------------------------------------------- //
            // If PT[NT][CurrentValue] DNE and PT[NT][$] DNE //
            // --------------------------------------------- //
            else if (parsingTable[nonTerminal_Position][currentValue_Position] == "" && parsingTable[nonTerminal_Position][terminalEpsilon_Position] == "") {
                stackOutput(tProcess);                                                                  // Print final stack.
                valid = false;                                                                          // No matching value for NT value. String is false.
            }
        }

        // If at this point valid = false, then we stop and say its invalid //
        if (valid == false) {                                                                           
            std::cout << "String is not accepted and INVALID!" << std::endl;                            // String not accepted print statement.
            return 0;                                                                                   // End program.
        }

        // std::cout << "currentValue = " << currentValue << std::endl;
        // std::cout << "String Holder = " << stringHolder << std::endl;
        // std::cout << "tProcess value = " << tProcess << std::endl;
        // std::cout << "--------------------------" << std::endl;
    }
}
