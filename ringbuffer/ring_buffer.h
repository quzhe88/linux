#ifndef RING_BUFFER_H
#define RING_BUFFER_H
#include <string>
#define DEFAULT_LENGTH 2	//默认缓存大小
#define CHANGES_BASELINE 2	//缓存变化基线，默认为2倍增长
typedef unsigned int size_t;
/*****************************************************************
brief		: 循环队列
author		: quzhe
data		: 2014/11/2
action		: create
*****************************************************************/
template<typename Type>
class RingBuffer
{
public:
	RingBuffer(void);
	~RingBuffer(void);
	size_t Size();					//返回缓存当前大小
	bool IsEmpty();					//判断缓存是否为空
	bool Push(const Type& elem);	//将元素elem加入到缓存末尾
	bool Pop(Type& elem);			//弹出缓存中第一个元素，返回到elem中
	bool IsFull();					//判断缓存是否已满
	//just for debug
	void Traversal();				//仅供调试使用，支持不完全
	//end
private:
	bool Allocate();				//缓存内存申请
	bool ReAllocate();				//缓存内存再次申请
private:
	Type* data_;
	size_t front_;					//首指针
	size_t rear_;					//末尾指针
	size_t length_;					//长度
};	
template<typename Type>
RingBuffer<Type>::RingBuffer(void)
	:front_(0), 
	rear_(0),
	length_(DEFAULT_LENGTH)
{
	data_ = NULL;
	Allocate();
}

template<typename Type>
RingBuffer<Type>::~RingBuffer(void)
{
	if(NULL != data_)
	{
		delete[] data_;
		data_ = NULL;
	}
}

template<typename Type>
bool RingBuffer<Type>::Allocate()
{
	try
	{
		data_ = new Type[length_];
	}
	catch(...)
	{
		//do something
		return false;
	}
	return true;
}

template<typename Type>
bool RingBuffer<Type>::ReAllocate()
{
	Type* temp = data_;
	size_t old_length = length_;
	size_t old_front = front_;
	size_t old_rear = rear_;

	length_ *= CHANGES_BASELINE;
	front_ = 0;
	rear_ = 0;
	if(!Allocate())
		return false;

	while(old_front % old_length != old_rear)
	{
		data_[rear_] = temp[old_front];
		rear_ = (rear_ + 1)%length_;
		old_front = (old_front + 1)%old_length;
	}
	delete[] temp;
	temp = NULL;
	return true;
}

template<typename Type>
size_t RingBuffer<Type>::Size()
{
	return (length_ - front_ + rear_)%length_;
}

template<typename Type>
bool RingBuffer<Type>::IsEmpty()
{
	return front_ == rear_ ? true : false;
}

template<typename Type>
bool RingBuffer<Type>::IsFull()
{
	return (rear_ + 1)%length_ == front_ ? true : false;
}

template<typename Type>
bool RingBuffer<Type>::Push(const Type& elem)
{
	if(IsFull() && !ReAllocate())
		return false;

	data_[rear_] = elem;
	rear_ = (rear_ + 1)%length_;
	return true;
}

template<typename Type>
bool RingBuffer<Type>::Pop(Type& elem)
{
	if(IsEmpty())
		return false;

	elem = data_[front_];
	front_ = (front_ + 1)%length_;
	return true;
}

//just for debug
template<typename Type>
struct Helper
{
	static const void Print(const Type& T)
	{
		printf("%d\n", T);
	}
};

template<>
struct Helper<std::string>
{
	static const void Print(const std::string& str)
	{
		printf("%s\n", str.c_str());
	}
};

template<typename Type>
void RingBuffer<Type>::Traversal()
{
	int offset = front_;
	while(offset % length_ != rear_)
	{
		Helper<Type>::Print(data_[offset]);
		offset = (offset + 1)%length_;
	}
}
//end
#endif

