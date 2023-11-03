#include <iostream>
#include "src/myQueue.hpp"
using namespace std;

int main() {
	int n, k, m;
	Queue<int>q;

	cin >> n >> k >> m;
	for (int i = 1;i <= n;i ++) {
		q.push(i);
	}

	while ( k -- > 1 ) { 
		int tmp = q.front();
		 q.pop();
		 q.push(tmp);
	}
	int idx = 1;
	while ( !q.empty() ) {
		int tmp = q.front();
		q.pop();
		if ( idx == m ) {
			idx = 1;
			cout << tmp << ((q.size()) ? "," : "");
			continue;
		}
		q.push(tmp);
		idx ++;
	}
	return 0;
}