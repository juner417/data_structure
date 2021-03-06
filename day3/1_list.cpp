// 1. array list  : 연속된 메모리(배열)
// 2. linked list : 떨어진 메모리 
// 가장 중요한 점 => 왜 linked list 를 사용하는가?

// a. 10개를 입력 받고 싶다 : 10개 짜리 배열사용
// b. 학생수를 입력 받아서 학생의 점수를 관리 : 동적메모리 항당이면 된다. 
// c. -1를 입력 할때 까지 입력 받고 싶다. : linked list가 좋다. 

// list를 만들떄 핵심
// 1. dummy node : list가 비어 있을때와 몇개 쯤 있을 떄의 알고리즘을 하나의 코드로 만들기 위해서. 

// 2. 마지막 노드의 next : 
//						a. 0으로 채우기
// 						b. 처음 주소로 채우기.(환형리스트)
// 3. list의 종류 : singl list, double list 
