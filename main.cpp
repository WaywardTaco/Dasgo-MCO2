#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include "Network.cpp"
#include "Reader.cpp"

using namespace std;

// The main driver of the program
int main(){

    // Initialization of the reader and the selection variables
    Reader reader;
    int selection = -1;

    do{
    
    // Initialization of the network's variable
    Network* network;

    do{

    // Asks for a filename and reads it to generate a Network
    string filename;
    cout << endl << "Enter Filename: "; cin >> filename;
    cout << endl;
    network = reader.readFile(filename);

    // Loops if the network is non-existent
    } while (network == NULL) ;

    do{

    // Outputs options for what to do with the network
    cout << "Select Option:" << endl;
    cout << "[1] Show Friend List" << endl;
    cout << "[2] Find Connection Between" << endl;
    cout << "[3] Load New Network" << endl;
    cout << "[4] Exit" << endl;
    cout << "Enter choice: "; cin >> selection;

    cin.clear();
    cin.ignore();
    
    switch(selection){
        case 1:{ // Shows the Friend List of the Entered Account Number
            
            int account;
            cout << endl << "Enter Account ID: "; cin >> account;

            cin.clear();
            cin.ignore();

            if(!network->hasAccount(account)){

                cout << "Account " << account << " not found!" << endl << endl;

                break;
            }

            network->showRelations(account);

            cout << endl;

            break;
        }
        case 2:{ // Handles searching for the connection between two existent accounts as entered
            
            int accountA, accountB;
            cout << endl << "Enter First Account: "; cin >> accountA;
            cout <<         "Enter Second Account: "; cin >> accountB;

            cin.clear();
            cin.ignore();

            if(!network->hasAccount(accountA)){
                cout << endl << "Could not find Account " << accountA << "!" << endl;
            }

            if(!network->hasAccount(accountB)){
                cout << "Could not find Account " << accountB << "!" << endl;
            }

            if(network->hasAccount(accountA) && network->hasAccount(accountB)){
                network->searchConnection(accountA, accountB);
            }
            
            cout << endl;

            break;
        }
    }

    // Loops back to menu so long as "Load New Network" and "Exit" are not selected
    } while (selection < 3 || selection > 4);

    // Loops back when "Load New Network" is selected
    } while (selection != 4);

    // Feedback for when "Exit is selected"
    cout << "Teminated Program..." << endl;

    return 0;
}
