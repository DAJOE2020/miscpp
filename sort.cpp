#include <iostream>  //std::cout, std::cin
#include <algorithm> //std::shuffle
#include <array>     //std::array
#include <random>    //std::default_random_engine
#include <map>       //std::map
#include <vector>    //std::vector
using namespace std;

#define ARRAY_SIZE 10
#define MAX 100

void printArray(array<int,ARRAY_SIZE> to_print) {
	printf("[%d",to_print[0]);
	for (int i=1;i<ARRAY_SIZE;i++) {printf(", %d",to_print[i]);}
	cout<<']'<<endl;
}

void printVector(vector<int> to_print) {
	printf("[%d",to_print.at(0));
	for (vector<int>::iterator it=to_print.begin()+1;it!=to_print.end();++it) {
		printf(", %d",*it);
	}
	cout<<']'<<endl;
}

void bogoSort(array<int,ARRAY_SIZE>& to_sort) { //average O((n+1)!) time, O(1) space
	int running = true;
	int count = 0;
	int avg_atmpts = 1;
	for (int i=2;i<=ARRAY_SIZE;i++) {avg_atmpts *= i;}
	while (running) {
		running = false;
		shuffle(to_sort.begin(),to_sort.end(),default_random_engine(time(NULL)+count++));
		for (int i=1;i<ARRAY_SIZE;i++) {
			if (to_sort[i] < to_sort[i-1]) {running = true;}
		}
		if (count%(avg_atmpts/100) == 0) {
			printf("%d%%\r",(count*100)/avg_atmpts);
			cout.flush();
		}
	}
	cout<<"        \r";
}

void insertionSort(array<int,ARRAY_SIZE>& to_sort) {
	vector<int> sorted;
	int i;
	for (int unsorted_num : to_sort) {
		i = 0;
		for (int sorted_num : sorted) {
			if (unsorted_num <= sorted_num) {break;}
			i++;
		}
		sorted.emplace(sorted.begin()+i,unsorted_num);
	}
	for (i=0;i<ARRAY_SIZE;i++) {
		to_sort[i] = sorted[i];
	}
}

void bubbleSort(array<int,ARRAY_SIZE>& to_sort) {
	bool running = true;
	int tmp;
	while (running) {
		running = false;
		for (int i=1;i<to_sort.size();i++) {
			if (to_sort[i] < to_sort[i-1]) {
				tmp = to_sort[i];
				to_sort[i] = to_sort[i-1];
				to_sort[i-1] = tmp;
				running = true;
			}
		}
	}
}

void pigeonholeSort(array<int,ARRAY_SIZE>& to_sort) {
	map<int,int> counts;
	int i;
	for (i=0;i<MAX;i++) {
		counts[i] = 0;
	}
	for (int num : to_sort) {
		counts[num]++;
	}
	i = 0;
	for (map<int,int>::iterator it=counts.begin();it!=counts.end();++it) {
		while (it->second > 0) {
			to_sort[i++] = it->first;
			it->second--;
		}
	}
}

void blockSort(array<int,ARRAY_SIZE>& to_sort) {
	
}

void mergeSort(array<int,ARRAY_SIZE>& to_sort) {
	int l, r, sr, mr;               //left compare, right compare, start right compare, max right compare
	int* s;                         //smaller number
	int gen_i;                      //index of next_gen
	array<int,ARRAY_SIZE> next_gen; //next generation
	for (int n=1;n<ARRAY_SIZE;n*=2) {
		gen_i = 0;
		for (int i=0;i<ARRAY_SIZE;i+=2*n) {
			l = i;
			r = n+i;
			if (r >= ARRAY_SIZE) {r = ARRAY_SIZE-1;}
			sr = r;
			mr = 2*n+i;
			if (mr > ARRAY_SIZE) {mr = ARRAY_SIZE;}
			
			while (l >= 0 || r >= 0) {
				if (l >= sr) {l = -1;}
				if (r >= mr) {r = -1;}

				if (l < 0) {s = &r;}
				else if (r < 0) {s = &l;}
				else {
					if (to_sort[l] <= to_sort[r]) {s = &l;}
					else {s = &r;}
				}
				
				//printf("n:%d,gen_i:%d,i:%d,l:%d,r:%d,sr:%d,mr:%d,s:%d\n",n,gen_i,i,l,r,sr,mr,*s);
				next_gen[gen_i++] = to_sort[(*s)++];
				
				if (l >= sr) {l = -1;}
				if (r >= mr) {r = -1;}
			}
		}
		for (int i=0;i<ARRAY_SIZE;i++) {to_sort[i] = next_gen[i];}
	}
}

void gnomeSort(array<int,ARRAY_SIZE>& to_sort) {
	int tmp;
	for (int i=0;i<ARRAY_SIZE-1;i++) {
		if (to_sort[i] > to_sort[i+1]) {
			tmp = to_sort[i];
			to_sort[i] = to_sort[i+1];
			to_sort[i+1] = tmp;
			i -= 2;
		}
	}
}

int main() {
	/*
	RANKINGS
	1 - Merge Sort      | O(nlog(n)) | Array size 1000000+
	2 - Pigeonhole Sort | O(n+k^2)   | Array size 1000000+ (With MAX 4000000)
	3 - Insertion Sort  | O(n^2)     | Array size 40000
	4 - Gnome Sort      | O(n^2)     | Array size 20000
	4 - Bubble Sort     | O(n^2)     | Array size 10000
	5 - Bogo sort       | O((n+1)!)  | Array size 10
	*/

	array<int,ARRAY_SIZE> to_sort; //array to be sorted
	for (int i=0;i<ARRAY_SIZE;i++) {srand(time(NULL)+i); to_sort[i] = rand()%MAX;}

	printArray(to_sort);
	bogoSort(to_sort);
	printArray(to_sort);
	return 0;
}
