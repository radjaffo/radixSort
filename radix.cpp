/*
Radix Sort C++ data crunch program written by:
Jeffrey Dickason
CSCE 3110.001
Program 3
11/1/14

So this program asks if you want to do base 10 or 16
Program then fills a vector of ints with random numbers from 1-1000
calls function radixSort with the vector passed by reference, total size of vector,
 and user input'd decimal base.
It then loops 3 more times and increases the random int size to a maximum of 10000

for some reason when i had it looping both base 10 and base 16 in one program, the base 16
 botched the numbers and was always smaller then base 10

Line 112 can be taken out of comment to see data put back in, be warned the 10000 is
  nonsensically large
*/

#include <iostream> //include libraries
#include <cstdlib>  //srand time
#include <time.h>	//time functions
#include <ctime>	//tried just using one and numbers were awful
#include <vector>	//use dem vectors
#include <queue>	//queue and commands
#include <math.h>   //pow
#include <chrono>	//more aqrat clock
#include <ratio>

//#define BASE1 10  //nope
//#define BASE2 16  //nope nope nope

using namespace std;
using namespace chrono;	//this thing sucked

//prototype for sorting function
void radixSort(vector<int> &random, int length, int base);

int main(){
	srand(time(NULL));
	vector<int> vec;
	int max=10000;
	int size=10;
	int base=10;
	//clock_t t;		//these can't get nanoseconds when the loop executes too fast
	//clock_t t2;
	//float timer=0;
	double dubtimer=0;
	high_resolution_clock::time_point t2, t1; 	//used to get acurate current clock times	
	//Program Description
	cout << "Jeffrey Dickason" << endl << "CSCE 3110.001" << endl << "Program 3" << endl << "11/1/14" << endl << endl << endl;
	cout << "Please enter decimal base" << endl;
	cin >> base;
	while(base != 10 && base != 16){	//error check
		cout << "Error, please use base 10 or 16 for sanity's sake" << endl;
		cin >> base;
	}
		cout << "Base: " << base << endl;
	for(int p=0; p < 4; p++){   //loop to increase size
		dubtimer = 0;
		if(size > max)		//just incase
			break;
								
		for(int i=0; i < 10; i++){  //loop each one 10 times for data's sake
		vec.resize(size);	//resize the vector
	

	//cout << "Reserve of vector is " << vec.capacity() << endl;
	//cout << "Size of vector is " << vec.size() << endl;
		for(int i=0; i < size; i++){	//load the vector with random ints
			vec.at(i) = rand()%1000;
			if(vec.at(i) > max)
				max = vec.at(i);
		}
	
	//DEBUG
	//Vector initialized and loaded with X random integers.
	//for(int j=0; j < size; j++){
		//cout << "vector contains the following elements and indicies" << endl;
	//	cout << j << ":" << vec.at(j) << " ";
	//}
	//cout << endl;


		t1 = high_resolution_clock::now();	//get time before
				//t = clock();	//failed clock
		radixSort(vec, size, base);
		//t2 = clock();			//more failed clock
		//timer = (float)t2 - (float)t;
		//timer2 = timer/CLOCKS_PER_SEC;
		//sumtimer += timer2;
		t2 = high_resolution_clock::now(); //get time after
		duration<double> time_span = (t2 - t1);	//take the difference
		dubtimer += time_span.count();		//add it to double timer
		vec.erase(vec.begin(), vec.begin()+size); //erase the vector
		}
		dubtimer *= 100000000.00;		//convert it to double nanoseconds
		cout << "Time taken for size " <<size << " was... " << dubtimer << " nanoseconds" << endl;
	size *= 10; //
	}
cout << endl;

	//PUT this back in to see verified sorted data
	//for(int i=0; i < size; i++)
	//	cout << i << ":" << vec.at(i) << " ";

cout << endl;
return 0;
}


//pass vector by reference
//param1 Address of vector
//param2 Address of 2d vector
//param3 number of elements in the vector
//param4 maximum value in the vector
//started with 2 array's of queues, now doing a 2d vector.
void radixSort(vector<int> &random, int length, int base){
	//this works, but is extremely inefficient for elements > 50...
	queue<int> buckets[10];	//Need both 10 and 16 buckets!
	queue<int> hexBuckets[16]; 

	int maxDigits = 3;
	int currentDigit = 0;
	int temp;

	if(base ==10){
		while(currentDigit < maxDigits){		//loop passes
			for(int i=0; i < length; i++){		//loop entire vector
				int divisor = pow(base, currentDigit);	// for mod and dividing purposes
				int num = random.at(i);
				int digitValue = ((num/divisor)%base);	//get bucket number based on current radix
					buckets[digitValue].push(num);	//put it in the correct queue
			}
			int j = 0;
			for(int k=0; k < base; k++){
				while (!buckets[k].empty()){	//delete all elements
					int temp=buckets[k].front();	//get front element in queue
					random.at(j) = temp;		//assign to my vectors
						buckets[k].pop();	//delete element
						j++;	//increment vector index
				}
			}
				currentDigit++;	//go to next pass
		}
	}
	else  //(base == 16)
	{
		//twoD.reserve(16);
		//twoD.resize(16);	//resize buckets to 16
		while(currentDigit < maxDigits){
			for(int i=0; i < length; i++){		//loop entire vector
				int divisor = pow(base, currentDigit);	// for mod and dividing purposes
				int num = random.at(i);
				int digitValue = ((num/divisor)%base);	//get bucket number based on current radix
				hexBuckets[digitValue].push(num);	//put it in the correct queue
			}
			int j = 0;
			for(int k=0; k < base; k++){
				while (!hexBuckets[k].empty()){	//delete all elements
					int temp=hexBuckets[k].front();	//get front element in queue
					random.at(j) = temp;		//assign to my vectors
						hexBuckets[k].pop();	//delete element
						j++;	//increment vector index
				}
			}
				currentDigit++;	//go to next pass
		}
	}
//cout << "Sorting complete!" << endl;
}