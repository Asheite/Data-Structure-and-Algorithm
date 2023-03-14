// DS2ex1 10927260 劉宗諺
#include "min_max_heap.hpp"
using namespace std;

int main() {
	int command = 0; // user command

 	do { 
 		cout << endl << "**** Heap Construction *****";
 		cout << endl << "* 0. QUIT                  *";
 		cout << endl << "* 1. Build a min heap      *";
 		cout << endl << "* 2. Build a min-max heap  *";
 		cout << endl << "*******************************";
 		cout << endl << "Input a command(0, 1, 2): ";
 		cin >> command; // get the command
 		cout << endl;
 		
        if ( command == 0 )
            break;

 		string id;
 		cout << "Input a file number ([0] Quit): ";
 		cin >> id;
        mmHeap ht = mmHeap();

        if ( id != "0" )
            ht = mmHeap( id );
        else
            continue;
        
 		cout << endl;
 		
 		switch (command) { 
 			case 0: break;
 			
 			case 1:
                if ( ht.readF() ) {
                    ht.constructMin();
                    ht.printmHeap();
                } // if
                else {
                    cout << "### input" << id << ".txt does not exist! ###" << endl;
                } // else
 				break;
 			
 			case 2:
                if ( ht.readF() ) {
                    ht.constructMm();
					ht.printMmHeap();
                } // if
                else {
                    cout << "### input" << id << ".txt does not exist! ###" << endl;
                } // else            
				break;

 			default: 
				cout << endl << "Command does not exist!" << endl;
				break;

 		} // end switch
 		
 	} while (command != 0); // '0': stop the program
 	
 	return 0;	    
} // main()