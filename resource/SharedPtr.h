#pragma once
//SharedPtr:20130424
#include <iostream>
#include <memory>

namespace lexia
{
	template<class T>
	using SharedPtr = std::shared_ptr<T>;
}

