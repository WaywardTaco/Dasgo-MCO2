#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include<chrono>
#include<cstdio>

#include "Reader.cpp"

using namespace std;

// The main driver of the program
int main() {

    // Initialization of the reader and the selection variables
    Reader reader;
    int selection = 4;

    do {

        // Initialization of the network's variable
        Network* network;

        do {

            // Asks for a filename and reads it to generate a Network
            string filename;
            cout << endl << "Enter Filename: "; cin >> filename;
            cout << endl;

            auto start = chrono::steady_clock::now();

            network = reader.readFile(filename);
            cout << " Total Relations Count: " << reader.relationCount << endl;

            auto end = chrono::steady_clock::now();
            cout << "Time Elapsed for Friend List: "
                << chrono::duration_cast<chrono::milliseconds>(end - start).count()
                << " ms" << endl << endl;

            // Loops if the network is non-existent
        } while (network == NULL);

        do {
            if (!(selection >= 1 && selection <= 4)) cout << endl << "Invalid" << endl << endl;
            // Outputs options for what to do with the network
            cout << "Select Option:" << endl;
            cout << "[1] Show Friend List" << endl;
            cout << "[2] Find Connection Between" << endl;
            cout << "[3] Load New Network" << endl;
            cout << "[4] Exit" << endl;
            cout << "Enter choice: "; cin >> selection;

            cin.clear();
            cin.ignore();

            switch (selection) {
            case 1: { // Shows the Friend List of the Entered Account Number

                int account;
                cout << endl << "Enter Account ID: "; cin >> account;

                cin.clear();
                cin.ignore();

                if (!network->hasAccount(account)) {

                    cout << "Account " << account << " not found!" << endl << endl;

                    break;
                }

                auto start = chrono::steady_clock::now();

                network->showRelations(account);

                auto end = chrono::steady_clock::now();
                cout << endl << "Time Elapsed for Friend List: "
                    << chrono::duration_cast<chrono::milliseconds>(end - start).count()
                    << " ms" << endl;

                cout << endl;

                break;
            }
            case 2: { // Handles searching for the connection between two existent accounts as entered

                int accountA, accountB;
                cout << endl << "Enter First Account: "; cin >> accountA;
                cout << "Enter Second Account: "; cin >> accountB;

                cin.clear();
                cin.ignore();

                if (!network->hasAccount(accountA)) {
                    cout << endl << "Could not find Account " << accountA << "!" << endl;
                }

                if (!network->hasAccount(accountB)) {
                    cout << "Could not find Account " << accountB << "!" << endl;
                }

                if (network->hasAccount(accountA) && network->hasAccount(accountB)) {
                    auto start = chrono::steady_clock::now();

                    network->searchConnection(accountA, accountB);

                    auto end = chrono::steady_clock::now();
                    cout << endl << "Time Elapsed for Accounts Connection: "
                        << chrono::duration_cast<chrono::milliseconds>(end - start).count()
                        << " ms" << endl;
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