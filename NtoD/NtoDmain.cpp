//子集s
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
