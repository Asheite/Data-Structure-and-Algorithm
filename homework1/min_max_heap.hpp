#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <typeinfo>

typedef enum {MIN, MAX} whichHeap; // a type to distinguish two parts of a min-max heap

typedef struct hT {
    std::string raw;
	int record; // record number of data
    int id; // a serial number as record identifier
    int value; // the key for comparison
} heapType;

class mmHeap {
	std::string id; // record file id ex: 101, 102...

	std::vector<heapType> minheap; // min heap
	std::vector<heapType> maxheap; // max heap
	std::vector<heapType> mmheap; // min max heap
    std::vector<heapType> data; // record all data in file

    int getNo( std::string line ); // get number
    int getgNo( std::string line ); // get graduate students number
	int getMax(); // get max element in data
	void swap( heapType &a, heapType &b ); // swap data
	heapType findLeftMost_min(); // find left most data in min heap
	heapType findLeftMost_mm(); // find left most data in min-max heap
	int getLevel( int nodeNumber );
	void reheapUp( int now_pos, int grand_pos );
	void reheapDown( int now_pos, int grand_pos );

    public:
		mmHeap(): id( "" ) {} // constructor
		mmHeap( std::string input ): id( input ) {} // constructor
		void mmHeapInsert( heapType [], const int, const int ); // add one to record
		int leftmostHeap( const heapType [], const int ); // locate the left most bottom node of a heap
        bool readF(); // read file of input ex: input101.txt...
		void printData(); // print all elements in data
		void constructMin(); // construct min heap
		void constructMm(); // construct min max heap
		void printmHeap(); // print min heap
		void printMmHeap(); // print min max heap
}; // end mmHeap

int mmHeap::getLevel( int nodeNumber ) {
    int i;
	int level = 1;
	for ( i = 1; i <= nodeNumber && nodeNumber > 0; i = i * 2 ) {
		nodeNumber - i;
		level++;
		if ( nodeNumber <= 0 )
			break;
	} // for

	return level - 1;
} // getLevel()

heapType mmHeap::findLeftMost_min() { // minheap ver.
	int i;
	for ( i = 1; i < minheap.size(); i = i * 2 + 1 ) {
		if ( i * 2 + 1 >= minheap.size() )
			break;
	} // for
	return minheap[i];
} // findMax()

heapType mmHeap::findLeftMost_mm() {
	int i;
	for ( i = 1; i < mmheap.size(); i = i * 2 + 1 ) {
		if ( i * 2 + 1 >= mmheap.size() )
			break;
	} // for
	
	return mmheap[i];
} // findLeftMost_mm()

void mmHeap::swap( heapType &a, heapType &b ) {
	heapType tmp = a;
	a = b;
	b = tmp;
} // swap()

bool mmHeap::readF() {
    std::ifstream file;
    file.open( "input" + id + ".txt"  );
    std::string line;

    if ( !file.is_open() ) {
        return false;
    } // if
    else {
		int counter = 1;
				
		while ( getline( file, line ) ) {
					
			if ( counter > 3 ) {
                heapType hT;
                hT.raw = line;
				hT.record = counter - 3;
                hT.id = getNo( line );
                hT.value = getgNo( line );
				data.push_back( hT );
			} // if
					
			counter++;
		} // while
    } // else

    return true;
} // readF()

int mmHeap::getNo( std::string line ) {
	std::string word = "";
	std::vector<std::string> rowData;
		
	for ( char&c : line ) {
					
		if ( c != '\t' ) {
			word += c;
		} // if
		else {
			rowData.push_back( word );
			word = "";
		} // else
	} // for
		
	return atoi( rowData[0].c_str() );
} // getNo()

int mmHeap::getgNo( std::string line ) {
	std::string word = "";
	std::vector<std::string> rowData;
		
	for ( char&c : line ) {
					
		if ( c != '\t' ) {
			word += c;
		} // if
		else {
			rowData.push_back( word );
			word = "";
		} // else
	} // for
		
	return atoi( rowData[8].c_str() );
} // getgNo()

void mmHeap::printData() {
	for ( auto i : data ) {
		std::cout << i.value << std::endl;
	} // for
} // printData()

int mmHeap::getMax() {
	int max = data[0].value;
	for ( int i = 1; i < data.size(); i++ ) {
		if ( data[i].value > max )
			max = data[i].value;
	} // for
	return max;
} // getMax()

void mmHeap::constructMin() {
	// construct min heap
	int counter = 0;

	for ( auto i : data ) {
		minheap.push_back( i );
		int counter2 = counter;

		for ( ; counter2 >= 0; counter2-- ) {
			if ( minheap[counter2].value < minheap[(counter2-1)/2].value ) {
				swap( minheap[counter2], minheap[(counter2-1)/2] ); // change parent and child node position
			} // if
		} // for

		counter++;
	} // for 
} // constructtMin()

void mmHeap::printmHeap() {
	// print min heap
	std::cout << "<min heap>" << std::endl;
	std::cout << "root: [" << minheap[0].record << "] " << minheap[0].value << std::endl;
	std::cout << "bottom: [" << minheap[minheap.size()-1].record << "] " << minheap[minheap.size()-1].value << std::endl;  
	std::cout << "leftmost bottom: [" << findLeftMost_min().record << "] " << findLeftMost_min().value << std::endl;
} // printmHeap()

void mmHeap::constructMm() {

	for ( auto i : data ) {
		mmheap.push_back( i );
		int level = getLevel( mmheap.size() );
		int now_pos = mmheap.size() - 1;
		int parent_pos = ( now_pos - 1 ) / 2;
		int grand_pos = ( parent_pos - 1 ) / 2;

		if ( ( level - 1 ) % 2 == 0 ) { // min max min max min...
			// up level is max now level is min
			if ( mmheap[now_pos].value > mmheap[parent_pos].value ) {
				swap( mmheap[now_pos], mmheap[parent_pos] );
				reheapUp( parent_pos, ( grand_pos - 1 ) / 2 );
				reheapDown( now_pos, grand_pos );
			} // if
			else {
				reheapDown( now_pos, grand_pos );
			} // else
		} // if
		else {
			// up level is min now level is max
			if ( mmheap[now_pos].value < mmheap[parent_pos].value ) {
				swap( mmheap[now_pos], mmheap[parent_pos] );		
				reheapDown( parent_pos, ( grand_pos - 1 ) / 2 );
			} // if

			reheapUp( now_pos, grand_pos );

		} // else
	} //for
} // constructMm()

void mmHeap::printMmHeap() {
	//print min max heap
	std::cout << "<min max heap>" << std::endl;
	std::cout << "root: [" << mmheap[0].record << "] " << mmheap[0].value << std::endl;
	std::cout << "bottom: [" << mmheap[mmheap.size()-1].record << "] " << mmheap[mmheap.size()-1].value << std::endl;  
	std::cout << "leftmost bottom: [" << findLeftMost_mm().record << "] " << findLeftMost_mm().value << std::endl;
} // printMmHeap()

void mmHeap::reheapUp( int now_pos, int grand_pos ) {

	if ( now_pos >= 3 && mmheap[now_pos].value > mmheap[grand_pos].value ) {
		swap( mmheap[now_pos], mmheap[grand_pos] );
		reheapUp( grand_pos, ( ( ( grand_pos - 1 ) / 2 ) - 1 ) / 2 );
	} // if
} // reheapUp()

void mmHeap::reheapDown( int now_pos, int grand_pos ) {
	if ( now_pos >= 3 && mmheap[now_pos].value < mmheap[grand_pos].value ) {
		swap( mmheap[now_pos], mmheap[grand_pos] );
		reheapDown( grand_pos, ( ( ( grand_pos - 1 ) / 2 ) - 1 ) / 2 );
	} // if
} // reheapDown()
