#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()

#define MAX_SIZE 5000

int insertion_sort(int a[], int n) {
    int ops_cnt = 0;
    for (int i = 1; i < n; i++) {
        ops_cnt++;
        int j = i - 1, key = a[i];
        while (j >= 0 && a[j] > key) {
            ops_cnt++;
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
    return ops_cnt;
}

int merge(int a[], int p, int q, int r) {
    int n1 = q - p + 1, n2 = r - q, ops_cnt = 0;
    int* left = new int[n1];
    int* right = new int[n2];
    
    for (int i = p; i <= q; i++) {
        left[i - p] = a[i];
        ops_cnt++;
    }
    
    for (int i = q + 1; i <= r; i++) {
        right[i - q - 1] = a[i];
        ops_cnt++;
    }

    int i = p, j = 0, k = 0;
    while (j < n1 && k < n2) {
        ops_cnt++;
        if (left[j] < right[k]) {
            a[i] = left[j];
            i++, j++;
        } else {
            a[i] = right[k];
            i++, k++;
        }
    }
    
    while (j < n1) {
        ops_cnt++;
        a[i] = left[j];
        i++, j++;
    }
    
    while (k < n2) {
        ops_cnt++;
        a[i] = right[k];
        i++, k++;
    }

    delete left;
    delete right;
    
    return ops_cnt;
}

int merge_sort(int a[], int p, int r) {
    int ops_cnt = 0;
    if (r - p < 1) return 1;
    
    int mid = (p + r) / 2;
    
    ops_cnt = merge_sort(a, p, mid)
        + merge_sort(a, mid + 1, r)
        + merge(a, p, mid, r);

    return ops_cnt;
}

void reverse_arr(int a[], int n) {
    int mid = n / 2, temp;

    for (int i = 0; i <= mid; i++) {
        temp = a[i];
        a[i] = a[n-i];
        a[n-i] = temp;
    }
}

void gen_file(const char *fname) {
    std::ofstream f(fname);
    srand(time(NULL));
    for (int i = 0; i < MAX_SIZE; i++)
        f << rand() << '\n';
    f.close();
    std::cout << "Saved random file." << std::endl;
}

void load_file(int a[], const char *fname, int n = MAX_SIZE) {
    std::ifstream f(fname);
    for (int i = 0; i < n; i++)
        f >> a[i];
    f.close();
}

int main() {
    using namespace std;
    int a[MAX_SIZE], ch, ops_cnt[3][6];
    char fname[MAX_SIZE];

    cout << "Enter the file name: ";
    cin >> fname;
    cout << "Enter 1 to generate input file or 2 to sort file" << endl;
    cin >> ch;

    if (ch == 1) {
        gen_file(fname); 
        return 0;
    } else if (ch != 2) {
        cout << "Invalid choice." << endl;
        return 1;
    }

    const int n[] = {1000, 2000, 5000};
    for (int i = 0; i < 3; i++) {
        load_file(a, fname, n[i]);
        ops_cnt[i][0] = insertion_sort(a, n[i]);
        ops_cnt[i][2] = insertion_sort(a, n[i]);
        reverse_arr(a, n[i]);
        ops_cnt[i][4] = insertion_sort(a, n[i]);

        load_file(a, fname, n[i]);
        ops_cnt[i][1] = merge_sort(a, 0, n[i] - 1);
        ops_cnt[i][3] = merge_sort(a, 0, n[i] - 1);
        reverse_arr(a, n[i]);
        ops_cnt[i][5] = merge_sort(a, 0, n[i] - 1);
    }

    cout << "Sorting results" << endl;
    cout << "Array Size | Randomized elements |    Ordered Array    |    Reversed array   |" << endl;
    cout << "           | InsSort | MergeSort | InsSort | MergeSort | InsSort | MergeSort |" << endl;
    for (int i = 0; i < 3; i++) {
    	cout << "n = " << n[i] << "   |";
        for (int j = 0; j < 6; j += 2) {
	    cout << setw(8) << ops_cnt[i][j] << " |" << setw(10) << ops_cnt[i][j + 1] << " |";
        }
	cout << endl;
    }
   
    return 0;
}
