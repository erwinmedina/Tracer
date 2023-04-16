#include <iostream>
#include <string>
#include <vector>
#include <fstream>

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

    // ------------------------------- //
    // Creates variables i'll be using //
    // ------------------------------- //
    std::vector<char> stack = {'$'};
    bool valid = true;
    std::string userInput = "a(a+a)$";
    int increment = 0;
    char currentValue = userInput[increment];
    std::string currentValue_string;
    std::string stringHolder = "";
    std::string tProcess;
    std::vector<char>::iterator tProcessIterator;
    std::vector<char>::iterator currentValueIterator;
    std::vector<char>::iterator nonTerminalIterator;

    // *************************************** //
    // Process to initailize tProcess variable //
    // *************************************** //

    // -------------------------------- //
    // Finds x position of currentValue //
    // -------------------------------- //
    std::vector<char>::iterator initializerX = std::find(T.begin(), T.end(), currentValue);
    std::cout << "Position = " << initializerX - T.begin() << std::endl;

    // --------------------------------------------------------------------- //
    // Loop that finds y position of first occurance of PT[currentValue][NT] //
    // --------------------------------------------------------------------- //
    for (int x = 0; x < 5; x++) {
        if (parsingTable[x][initializerX - T.begin()] != "" && tProcess == "") {
            tProcess.append(parsingTable[x][initializerX - T.begin()]);
        }
    }
    std::cout << "tProcess value = " << tProcess << std::endl;

    // ***************************************************** //
    // Loop through tProcess until stringHolder == userInput //
    // ***************************************************** //
    int zero = 0;
    while (true) {

        std::cout << tProcess[0] << std::endl;
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

        else if (tProcess[0] == '0') {
            tProcess.erase(tProcess.begin());
        }
        
        // ------------------------------------------ //
        // Handles if first value is a terminal value //
        // ------------------------------------------ //
        else if (tProcessIterator != T.end()) {      // Meaning tProcess[0] is a terminal value

            // If PT[x][y] == currentValue [meaning Terminal matches up] //
            if (tProcess[0] == currentValue) {
                increment += 1;
                currentValue = userInput[increment];
            }
            stringHolder += tProcess[0];        // Add it to stringHolder
            tProcess.erase(tProcess.begin());   // Remove terminal value from tProcess
        }

        // ---------------------------------------------- //
        // Handles if first value is a non-terminal value //
        // ---------------------------------------------- //
        else {                                                              // Meaning tProcess[0] is a non-terminal value
            int nonTerminal_Position = nonTerminalIterator - NT.begin();    // x position [goes first]
            int currentValue_Position = currentValueIterator - T.begin();   // y position [goes second]
            int terminalEpsilon_Position = 7;                               // hard-coded because lazy.
            std::cout << "Parsing Table Value: " << parsingTable[nonTerminal_Position][currentValue_Position] << std::endl;
            
            // ------------------------------ //
            // If PT[NT][CurrentValue] exists //
            // ------------------------------ //
            if (parsingTable[nonTerminal_Position][currentValue_Position] != "") {
                
                currentValue_string += currentValue; // converts char to string - LAZY

                // If PT[x][y] == currentValue [meaning Terminal matches up] //
                if (parsingTable[nonTerminal_Position][currentValue_Position] == currentValue_string) {
                    stringHolder += currentValue;
                    increment += 1;
                    currentValue = userInput[increment];
                    tProcess.erase(tProcess.begin());
                }
                // If we simply find anything but our terminal matching up with currentValue
                else {
                    tProcess.replace(0,1,parsingTable[nonTerminal_Position][currentValue_Position]);
                }

                currentValue_string = ""; // clears out lazy code.
            }

            // ------------------------------------------------ //
            // If PT[NT][CurrentValue] DNE but PT[NT][$] exists //
            // ------------------------------------------------ //
            else if (parsingTable[nonTerminal_Position][currentValue_Position] == "" && parsingTable[nonTerminal_Position][terminalEpsilon_Position] != "") {
                tProcess.erase(tProcess.begin());
            }

            // --------------------------------------------- //
            // If PT[NT][CurrentValue] DNE and PT[NT][$] DNE //
            // --------------------------------------------- //
            else if (parsingTable[nonTerminal_Position][currentValue_Position] == "" && parsingTable[nonTerminal_Position][terminalEpsilon_Position] == "") {
                valid = false;
            }
        }

        if (valid == false) {
            std::cout << "String is not accepted and INVALID!" << std::endl;
            return 0;
        }

        std::cout << "Increment = " << increment << std::endl;
        std::cout << "currentValue = " << currentValue << std::endl;
        std::cout << "String Holder = " << stringHolder << std::endl;
        std::cout << "tProcess value = " << tProcess << std::endl;

        zero += 1;
        std::cout << "--------------------------" << std::endl;
    }


    // [** DONE **] 


    // [** DONE **] // Need parsing table database.
    // [** DONE **] // Need vector to hold stack. [requirement for output]
    // [** DONE **] // Need boolean valid = true [for valid/invalid string]
    // [** DONE **] // Need currentValue = userInput[0] [the current value is the value we're currently searching for]
    // [** DONE **] // Need string stringHolder = "" to compare with UserInput. [stringHolder will get filled in as we go]
    // [** DONE **] // Need tProcess [will hold terminals/non terminals {i.e. FRQ}]
    // [** DONE **] // Need to initialize tProcess.

    // [** DONE **] // Need to read tProcess from the beginning every loop.

        // If char in tProcess is Terminal [not uppercase]
            // move on to next char in tProcess
            
            // If we reach the end of tProcess [$]
                // If stringHolder != userInput
                    // valid = false;
                    // return [we're done here + failed];
                // Else 
                    // return [we're done here];

        // If char in tProcess is NT
            // [** DONE **] // If PT[currentValue][NT] DNE but PT[$][NT] exists
                // [** DONE **] // replace tProcess @ char with PT[$][NT] [which i guess would be empty ?];

            // [** DONE **] // If PT[currentValue][NT] DNE and PT[$][NT] DNE
                // [** DONE **] // valid = false;
                // [** DONE **] // return;

            // [** DONE **] // If PT[currentValue][NT] exists
                // [** DONE **] // tProcess @ char = PT[currentValue][NT]

                // [** DONE **] // If PT[currentValue][NT] == currentValue {meaning that you found a terminal value}
                    // [** DONE **] // increment += 1
                    // [** DONE **] // currentValue = userInput[increment]
                    // [** DONE **] // stringHolder += currentValue

                

        



    // This works, use for later //

    // // User input
    // std::string userInput;
    // std::cout << "Please enter a string: ";
    // std::getline(std::cin, userInput);
    // std::cout << "You entered: " << userInput << std::endl;
    return 0;
}