#include "Correction.h"

int main()
{
    Trie t;
    TrieNode tn;

    t.SetDictionary();
    int size = t.getDictionarySize();

    
    string prefix;
    int choose;
    bool isrunning = true;
 
    while (isrunning) {
        cout << "Enter your prefix: ";
        cin >> prefix;

        t.autoComplete(prefix);

        cout << endl  << endl << "Do you want to continue? (1 - yes, 2 - no)" << endl;
        cin >> choose;
        if (choose == 1) { continue; }

        else {
            isrunning = false;
        }
    }


    return 0;
}




