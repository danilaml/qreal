#pragma once

#include "qrtext/core/types/typeVariable.h"

class HMTypeVariable : public qrtext::core::types::TypeVariable
{
public:
	HMTypeVariable(int id);

	int getId() const;
private:
	HMTypeVariable() {}

	int mId;
};

