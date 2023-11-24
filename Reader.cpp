
using namespace std;

// The class which handles file reading and the intake of a Network
class Reader{

public:

    Reader(){

    };

    /****************************************************************************************************
    *   readFile : searches for a file of the given filename from the local folder to intake entries,
    *   generates a Network of the read in size, then reads number of relationship lines as stated.
    *   Adds a relationship to the Network for every succeeding relationship line. Handles files
    *   unable to be read and repeat relationships.
    * 
    *   @param std::string filename : the name of the file to be read
    *   @return Network* : the pointer to the memory address of the Network generated
    * 
    ****************************************************************************************************/
    Network* readFile(std::string filename){

        // Opens the file pointer to the correct file
        ifstream File;
        File.open(filename);

        if(File.fail()){
            cout << "Unable to Read File! Try Again!" << endl;
            return NULL;
        }

        // Reads the number of accounts from the file 
        int accountCount;
        File >> accountCount;

        Network* newNetwork = new Network(accountCount);
        
        // Reads the number of relationships in the file
        int relationCount;
        File >> relationCount;

        // Reads line by line the relationships and adds it to the Network
        for(int i = 0; i < relationCount; i++){
            int accountA, accountB;

            File >> accountA;
            File >> accountB;

            newNetwork->addRelation(accountA, accountB);
        }
        
        // Closes the file 
        File.close();
        
        cout << "Loaded Network From: \"" << filename << "\"" << endl << endl;

        // Returns the newly generated record array
        return newNetwork;
    }

};