#include <iostream>
#include <vector>

using namespace std;

// The Class which describes the social network as a graph
class Network {

private:
    int size;                       // Number of Accounts present in the Network
    vector<vector<int>> accounts;   // An Adjacency Linked List to show Account Connections
    int count = 0;
    

public:
    /****************************************************************************************************
    *   Network : The default constructor of the Network, initializes the adjacency list with slots
    *   up to the size, such that each adjacency list has the account number as its first item.
    *
    *   @param int size : the size of the to-be Network
    *
    *****************************************************************************************************/
    Network(int size) {
        this->size = size;

        for (int i = 0; i < size; i++) {
            vector<int>* vect = new vector<int>;

            vect->push_back(i);

            accounts.push_back(*vect);
        }
    }

    /****************************************************************************************************
    *   addRelation : Adds a two-way relationship to accounts via the adjacency list, does this by
    *   adding the account numbers to the end of the adjacency lists at the slots with those account
    *   numbers as their first entry. Also avoids adding relationships which already exist, are
    *   self-loops, or are with non-existent accounts
    *
    *   @param int accountA : the first acount in the relationship to be added
    *   @param int accountB : the second account in the relationship to be added
    *
    *****************************************************************************************************/
    void addRelation(int accountA, int accountB) {
        if (!hasAccount(accountA) || !hasAccount(accountB) || accountA == accountB ||
            isInArray(accountB, this->accounts[accountA]))
            return;

        accounts[accountA].push_back(accountB);
        accounts[accountB].push_back(accountA);
    }

    /****************************************************************************************************
    *   showRelations : prints out all the friends of the particular account by running down its
    *   adjacency list, also handles if the account has no friends or is non-existent
    *
    *   @param int account : the account whose friends are to be printed
    *
    *****************************************************************************************************/
    void showRelations(int account) {
        if (!hasAccount(account))
            return;

        int relationCount = getRelationCount(account);
        vector<int> currentAccount = accounts[account];

        cout << "Account " << account << "'s Friends List:" << endl;

        if (relationCount <= 0) {
            cout << " - Empty" << endl;
            return;
        }

        for (int i = 0; i < relationCount; i++)
            cout << " - Account " << currentAccount[i + 1] << endl;

        cout << "Count of Relations: " << relationCount;

    }

    /****************************************************************************************************
    *   searchConnection : looks for the connection route between two accounts via depth-first search.
    *   calls its override which handles the recursive calling for instances beyond the first. Also
    *   handles same account searches and if no connection exists.
    *
    *   @param int from : the starting account's number
    *   @param int to : the target account's number
    *   @return bool : whether or not a connection could be found
    *
    *****************************************************************************************************/
    bool searchConnection(int from, int to) {

        if (from == to) {
            cout << "Both are Account " << from << "!" << endl;
            return true;
        }

        vector<int> visited;

        cout << "Connection From Account " << from << " to Account " << to << ":" << endl;

        bool found = searchConnection(to, from, &visited);

        if (found)
            cout << " Account " << to << endl;
        else
            cout << " Could not find connection!" << endl;

        cout << "Connection count: " << count << endl;
        count = 0;

        return found;
    }

    /****************************************************************************************************
    *   searchConncetion : the recursive override to search for a connection between two accounts, it
    *   ensures it does not revisit nodes using its visited list. It recursively calls itself to use
    *   depth-first search to find the target account, outputting a step in the connection if it
    *   such a connection was found.
    *
    *   @param int to : the target account being looked for
    *   @param int from : the origin account from where the search started
    *   @param vector<int> visited : a list of already visited accounts
    *   @return bool : whether or not a successful connection was found
    *
    *****************************************************************************************************/
    bool searchConnection(int to, int from, vector<int> *visited) {
        visited->push_back(to);

        if (to == from)
            return true;

        if (accounts[to].size() <= 1)
            return false;

        for (int j = 1; j < accounts[to].size(); j++) {
            if (!isInArray(accounts[to][j], *visited)) {
                if (searchConnection(accounts[to][j], from, visited)) {
                    cout << " Account " << accounts[to][j] << " ->";
                    count++;
                    return true;
                }
            }
        }

        return false;
    }

    /****************************************************************************************************
    *   isInArray : checks if the key value (usually an account number) is in a specified array, be it
    *   an array of visited accounts, of an adjacency list, or other
    *
    *   @param int key : the key value being looked for
    *   @param vector<int> vector : the vector/array being searched through
    *   @return bool : whether or not if the key was found in the vector
    *
    *****************************************************************************************************/
    bool isInArray(int key, vector<int> vector) {
        bool answer = find(vector.begin(), vector.end(), key) != vector.end();

        return answer;
    }

    /****************************************************************************************************
    *   getRelationCount : gets the number of relationships a specific account has
    *
    *   @param int account : the account to be checked
    *   @return int : the number of relationships the account has
    *
    ****************************************************************************************************/
    int getRelationCount(int account) {
        return accounts[account].size() - 1;
    }

    /****************************************************************************************************
    *   getSize : returns the size of the Network
    *
    *   @return int : the size of the Network
    *
    ****************************************************************************************************/
    int getSize() {
        return this->size;
    }

    /****************************************************************************************************
    *   hasAccount : returns if an account can be found in the Network
    *
    *   @param int account : the account number to be checked
    *   @return bool : whether or not if the account is in the Network
    *
    ****************************************************************************************************/
    bool hasAccount(int account) {
        return account < size;
    }
};