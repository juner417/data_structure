#include <stdio.h>

// hash 함수 : 입력된 키값을 가지고 저장할 index를 리턴하는 함수 
int hashing(int key)
{
	return key%16;
	//만약 같은 나머지를 같는다면...?
	// 같은 나머지를 같게되면 링크드리스트로 버켓의 노드를 늘려준다.
}

int main()
{
	int x[16] = {0};
	// 사용자에게서 16개를 입력 받아서 배열에 넣습니다.
	// 사용자가 입력한 값을 hash함수로 보내서 저장할 index를 결정합니다. 
	int n = 0;
	printf("input>>");
	scanf("%d", &n);
	int index = hashing(n);

	printf("저장할 index : %d\n", index);
	x[index] = n;

	int n2 = 0;
	printf("찾을 값은>> ");
	scanf("%d", &n2);

	// 배열 순회를 하지말고,,,, hash함수로 보내서 index를 알아낸다. 
	printf("찾은값: %d\n", x[hashing(n2)]);
	// 배열에서 특정 숫자를 검색합니다. - 최악의 경우는
	
}
