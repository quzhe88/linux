#include "ring_buffer.h"

int main()
{
	//int test
	{
		RingBuffer<int> ring;
		for(unsigned int i = 0; i < 5; ++i)
		{
			ring.Push(i);
		}
		int result = 0;
		ring.Pop(result);
		//2,3,4,5
		ring.Traversal();
	}

	//std::string test
	{
		RingBuffer<std::string> ring;
		ring.Push("a");
		ring.Push("b");
		ring.Push("c");
		ring.Push("d");
		
		std::string result;
		ring.Pop(result);
		//b,c,d
		ring.Traversal();
	}


	return 0;
}