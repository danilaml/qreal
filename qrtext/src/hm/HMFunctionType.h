#pragma once

//#include "qrtext/core/types/typeExpression.h"
#include "qrtext/src/hm/HMTypeVariable.h"

class HMFunctionType : public qrtext::core::types::TypeExpression
{
public:
	HMFunctionType(QSharedPointer<HMTypeVariable> const &returnType
	               , QList<QSharedPointer<HMTypeVariable>> const &formalParameters)
			   : mReturnType(returnType), mFormalParameters(formalParameters)
	{
	}

	void specialize(QList<QSharedPointer<HMTypeVariable>> const &with);

	QSharedPointer<HMTypeVariable> const &returnType() const
	{
		return mReturnType;
	}


	QList<QSharedPointer<HMTypeVariable>> const &formalParameters() const
	{
		return mFormalParameters;
	}

private:
	QSharedPointer<HMTypeVariable> mReturnType;
	QList<QSharedPointer<HMTypeVariable>> mFormalParameters;
};
