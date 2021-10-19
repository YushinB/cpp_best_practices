#include <iostream>
#include <memory>

#define TEST_SMART_POINTER
//#define TEST_PASSING_SMART_POINTER
/// <summary>
/// The six rules violate the import dry (don't repeat yourself) 
/// principle for software development.
/// In the end, we have only four rules what makes our life as a software developer a lot easier. Here are the rules.
/// </summary>

#ifdef  TEST_SMART_POINTER
/// <summary>
/// 
/// </summary>
/// <param name="shr">share pointer for checking</param>
void asSmartPointerGood(std::shared_ptr<int>& shr) {
	std::cout << "shr.use_count(): " << shr.use_count() << std::endl;  // (3)
	shr.reset(new int(2011));                                          // (5)
	std::cout << "shr.use_count(): " << shr.use_count() << std::endl;  // (4)
}
/// <summary>
/// 
/// </summary>
/// <param name="shr"> share pointer for checking</param>
void asSmartPointerBad(std::shared_ptr<int>& shr) {
	// doSomethingWith(*shr);
	*shr += 19;
}


int main() {

	std::cout << std::endl;

	auto firSha = std::make_shared<int>(1998);
	auto secSha = firSha;
	std::cout << "firSha.use_count(): " << firSha.use_count() << std::endl;  // (1)

	std::cout << std::endl;

	asSmartPointerGood(firSha);                                              // (2)

	std::cout << std::endl;

	std::cout << "*firSha: " << *firSha << std::endl;
	std::cout << "firSha.use_count(): " << firSha.use_count() << std::endl;

	std::cout << std::endl;

	std::cout << "*secSha: " << *secSha << std::endl;
	std::cout << "secSha.use_count(): " << secSha.use_count() << std::endl;

	std::cout << std::endl;

	asSmartPointerBad(secSha);                                              // (6)
	std::cout << "*secSha: " << *secSha << std::endl;

	std::cout << std::endl;

	system("pause");
	return 0;
}
#endif //  TEST_SMART_POINTER

#ifdef TEST_PASSING_SMART_POINTER

struct Widget {
	Widget(int a):_a(a){}

	int _a = 1;
};

/// <summary>
/// R.32: Take a unique_ptr<widget> parameter to express that a function assumes ownership of a widget
/// I'm for the lifetime of the function body a shared owner of the Widget.
/// At the beginning of the function body, I will increase the reference counter;
/// at the end of the function, I will decrease the reference counter; therefore,
/// the Widget will stay alive, as long as I use it.
/// </summary>
void sink(std::unique_ptr<Widget> uniqPtr) {
	// do something with uniqPtr
}

/// <summary>
/// R.33: Take a unique_ptr<widget>& parameter to express that a function reseats the widget
/// I'm not a shared owner of the Widget
/// because I will not change the reference counter.
/// I have not guaranteed that the Widget will stay alive during the execution of my function
/// but I can reseat the resource. A non-const lvalue reference is more like: I borrow the resource and can reseat it
/// </summary>
void reseat(std::unique_ptr<Widget>& uniqPtr) {// non-const lvalue reference.
	uniqPtr.reset(new Widget(2003));   // (0)
									   // do something with uniqPtr
}

/// <summary>
/// I only borrow the resource.
/// </summary>
/// <param name="shaWid"></param>
void mayShare(const std::shared_ptr<Widget>& shaWid)
{
	shaWid->_a = 1;
}

int main() {
	auto uniqPtr = std::make_unique<Widget>(1998);

	sink(std::move(uniqPtr));      // (1)
	//sink(uniqPtr);                 // (2) ERROR need to move onwership from one to another.


	reseat(std::move(uniqPtr));       // (1) ERROR
	reseat(uniqPtr);                  // (2) 


}
#endif
