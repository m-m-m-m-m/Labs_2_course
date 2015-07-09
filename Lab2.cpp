#include <iostream>
#include <vector>

using namespace std;

void swap(int &a, int &b){
	int c = a;
	a = b;
	b = c;
}


//template <type, size>
void sort(vector<int> &temp){
	int Compare=0, Move=0, Time, i, j;
	//for(int i=0; i<10; i++) cout << i+1 << ". " << *first++ << endl << endl;
	
	for (i=1; i<temp.size(); i++)	{
		for (j=0; j<i; j++) {
			Compare++;
			//cout << "first[" << j << "] = " << first[j] << endl;
			//cout << "first[" << i << "] = " << first[i] << endl;
			if(temp[i]<temp[j]) {
				for(int k=j; k<i; k++) {
					swap(temp[k],temp[i]);
					Move++;
				}
				//cout << "WAS SWAP BITCHES!!!" << endl;
				break;
			}
			//for(int l=0; l<10; l++) cout << l+1 << ". " << first[l] << endl
		}
		//for(int k=0; k<100; k++) cout << k+1 << ". " << first[k] << endl;
	}
	cout << "Compare = " << Compare << endl
		 << "Move = " << Move << endl;
}

int main(){
	vector<int> first(100), second(1000), third(10000);

	for(int i=0; i<100; i++) first[i] = rand() % 100;
	for(int i=0; i<1000; i++) second[i] = rand() % 1000;
	for(int i=0; i<10000; i++) third[i] = rand() % 10000;

	//for(int i=0; i<10; i++) cout << i+1 << ". " << first[i] << endl;
	sort(first);
	sort(second);
	sort(third);
	/*for(int i=0; i<1000; i++) cout << i+1 << ". " << second[i] << endl;
	FILE * temp = fopen("temp.txt", "wb");
	for (int i=0; i<1000; i++) fprintf(temp, "%d. %d \r\n", i+1, second[i]);*/

	cin.get();
	return 0;
}
