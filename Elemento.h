#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <iostream>

template<typename T>
class Elemento {
private:
    T* info;
	Elemento<T>* _next;

public:
    Elemento(){}
	Elemento(const T& info, Elemento<T>* next) : info(new T(info)), _next(next) {}

	~Elemento()
	{
		delete info;
	}

    Elemento<T>* getProximo()
	{
		return _next;
	}

    void setInfo(T& myInfo){
        info = &myInfo;
    }
    T* getObj()
    {
        return info;
    }

    T getInfo() const
	{
		return *info;
	}

	T* getMyInfo() const
	{
		return info;
	}

	void setProximo(Elemento<T>* next)
	{
		_next = next;
	}

	void tellName(){
        std::cout << (info->x);
	}
};

#endif
