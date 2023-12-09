//Epset:存储结点的容器（未定）
set s;
//子集s
queue q;
//队列q

//算起始状态空闭包给I0
//空闭包进入s和q


while (!q.empty()) {
	//出队列到I

	for （非终结符）{
		//temp_s = I读ch后的空闭包

		if (!temp_s.empty()) {
			if (!s.count(temp_s)) {
				s.insert(temp_s);
				q.push(temp_s);
			}
			
			else {
				//为当前I新建一条Edege；

			}
		}
	}
}


Epset epcloure(Epset s) {
	stack<int> epStack;

	Epset::iterator it;
	for (it = s.begin(); it != s.end(); it++) {
		epStack.push(it);
	}

	while (!epStack.empty()) {
		int temp = epStack.top();
		epStack.pop();

		//遍历通过空能到状态集
		//若当前未出现则加入集合并压入栈中
		
	}

	return s;
}