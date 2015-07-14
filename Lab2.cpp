#include <iostream>
#include <vector>
#include <time.h>
#include <math.h> // for Shell's sort
#include <algorithm> //for finding min and max

using namespace std;

/*inline void swap(int &a, int &b){
	int c = a;
	a = b;
	b = c;
}*/

inline int minElement(const vector<int> &arr){
	int min = arr[0];
	for (int i=1; i<arr.size(); i++) if (arr[i] < min) min = arr[i];
	return min;
}

inline int maxElement(const vector<int> &arr){
	int max = arr[0];
	for (int i=1; i<arr.size(); i++) if (arr[i] > max) max = arr[i];
	return max;
}


inline void showArrayInColumn(const vector<int> &vec)
{
	for(int i=0; i<vec.size(); i++) cout << i+1 << ". " << vec[i] << endl; 
}

inline void showArrayInLine(const vector<int> &vec)
{
	for(int i=0; i<vec.size(); i++) cout << vec[i] << " ";
	cout << endl;
}


inline void fillArray(vector<int> &vec)
{
	for(int i=0; i<vec.size(); i++) vec[i] = rand() % vec.size();
}

void insertionSort(vector<int> &arr){
	int compare=0, move=0, time;
	time = clock();
	
	//showArrayInLine(arr);

	for (int i = 1; i < arr.size(); i++){
		//int key = arr[i];
		//cout << "Current key = " << /*key*/arr[i] << endl;
		if (!(i-1 >= 0 && arr[i-1] > /*key*/arr[i])) {
			++compare;
			//cout << "Compared element = " << arr[i-1] << endl;
		}
		for(int j = i - 1; j >= 0 && arr[j] > /*key*/arr[j+1]; j--){
			//cout << "Compared element = " << arr[j] << endl;
			/*arr[j+1] = arr[j];*/
			swap(arr[j],arr[j+1]);
			++move;
			++compare;
			//cout << "move = " << move << endl;
		}
		/*arr[j+1] = key;*/

		//cout << "compare = " << compare << endl;
		//showArrayInLine(arr);
	}

	cout << "compare = " << compare << endl
		 << "move = " << move << endl
		 << "time = " << ((double)(clock() - time)/CLOCKS_PER_SEC) << " seconds" << endl
		 << clock() << " tacts" << endl;
}

void bubbleSort(vector<int> &arr){
	int compare=0, move=0, time, i, j;
	time = clock();
	bool wasSwap;											//
	for (i=0; i<arr.size()-1; i++){
		wasSwap = false;									//
		for (j=0; j < arr.size() - i - 1; j++, compare++)
			if (arr[j]>arr[j+1]) {
				swap(arr[j], arr[j+1]);
				move++;
				wasSwap = true;								//
			}
		if(!wasSwap) break;									//
	}

	cout << "compare = " << compare << endl
		 << "move = " << move << endl
		 << "time = " << ((double)(clock() - time)/CLOCKS_PER_SEC) << " seconds" << endl
		 << clock() << " tacts" << endl;
}

void selectionSort(vector<int> &arr){
	int compare=0, move=0, time, i, j, min;
	time = clock();
	for (i=0; i < arr.size()-1; i++){
		/*min = i;
		for (j=i+1; j < arr.size(); j++, compare++) 
			if (arr[min] > arr[j]) 
				min = j;*/
		/*if (minElement(arr) != i)
		if (*min_element(begin(arr), end(arr)) != i)*/
		if (minElement(arr) != arr[i])
			swap(arr[i], arr[min]);
		move++;
	}

	cout << "compare = " << compare << endl
		 << "move = " << move << endl
		 << "time = " << ((double)(clock() - time)/CLOCKS_PER_SEC) << " seconds" << endl
		 << clock() << " tacts" << endl;
}

void shellsSort(vector<int> &arr){
	int step, move=0, compare=0;
	double size = arr.size();
	for (int k = floor(log(size)/log(3.0))-1; k > 0; k--)
	{
		cout << "k = " << k << endl;
		step = 1;
		for (int tmp = k; tmp > 1; tmp--) 
		{
			step = 2*step + 1;
			cout << "step = " << step << endl;
		}
		cout << "Result: step = " << step << endl;
		for(int k=0; k<arr.size(); k++) cout << arr[k] << " ";		//
		cout << endl;												//

		for (int i = step; i < arr.size(); i = i + step){
			cout << "Current index = " << i + 1 << endl
				 << "Current key = " << arr[i] << endl;				//
			if (!(i-step >= 0 && arr[i-step] > arr[i])) {
				++compare;
				cout << "Compared element = " << arr[i-step] << endl;	//
			}
			for(int j = i - step; j >= 0 && arr[j] > arr[j+step]; j = j - step){
				cout << "Compared element = " << arr[j] << endl;	//
				swap(arr[j],arr[j+step]);
				++move;
				++compare;
				cout << "move = " << move << endl;					//
			}
			cout << "compare = " << compare << endl;				//
			showArrayInLine(arr);									//
		}
	}

}

void quickSort(vector<int> &arr, int first, int last, int &moves, int &compares){
	int left = first, right = last;
	float pivot = arr[(first + last) / 2];


	//cout << "pivot = " << pivot << endl;
	//showArrayInLine(arr);					?????????????????????????????????

	do {
		
		while (arr[left] < pivot) {
			/*cout << "WAS COMPARE!" << endl
				 << "Left elemenet = " << left + 1 << endl;*/
			left++;
			compares++;
			
		}
		if (arr[left] >= pivot) {
			compares++;											// compare that can be don't counted, if left didn't move
			/*cout << "WAS COMPARE!" << endl
				 << "Left elemenet = " << left + 1 << endl;*/
		}
		//cout << "left = " << left+1 << endl; 
		
		while (arr[right] > pivot) {
			/*cout << "WAS COMPARE!" << endl
				 << "Right elemenet = " << right + 1 << endl;*/
			right--;
			compares++;
		}
		if (arr[right] <= pivot) {
			compares++;											// compare that can be don't counted, if right didn't move
			/*cout << "WAS COMPARE!" << endl
				 << "Right elemenet = " << right + 1 << endl;*/
		}
		//cout << "right = " << right + 1 << endl;

		if(left <= right) {
			if (arr[left] > arr[right]) swap(arr[left], arr[right]); // or oneline style swap(arr[left++], arr[right++]);
			left++;
			right--;
			moves++;
			//cout << "WAS SWAP!" << endl;
			//showArrayInLine(arr);						????????????????????????????
		}
	} while (left <= right);

	if (left < last)
		quickSort(arr, left, last, moves, compares);
	if (first < right)
		quickSort(arr, first, right, moves, compares);

}

void quickSort(vector<int> &arr){
	int time, move = 0, compare = 0;
	time = clock();
	quickSort(arr, 0, arr.size()-1, move, compare);
	cout << "compare = " << compare << endl
		 << "move = " << move << endl
		 << "time = " << ((double)(clock() - time)/CLOCKS_PER_SEC) << " seconds" << endl
		 << clock() << " tacts" << endl;
}
													//настроить время до милисекунд!!!
int main(){
	vector<int> first(100), second(1000), third(10000);
	
	//srand(time(0));

	fillArray(first);
	fillArray(second);
	fillArray(third);
	
	vector<int> tmp(first), tmp2(second), tmp3(third);
	showArrayInColumn(first);
	
	/*FILE * temp = fopen("temp.txt", "wb");
	for (int i=0; i<1000; i++) fprintf(temp, "%d. %d \r\n", i+1, second[i]);*/

	cin.get();
	return 0;
}
