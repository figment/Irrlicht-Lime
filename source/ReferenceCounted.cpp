#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {

bool ReferenceCounted::operator == (ReferenceCounted^ v1, ReferenceCounted^ v2)
{
	bool v1n = Object::ReferenceEquals(v1, nullptr);
	bool v2n = Object::ReferenceEquals(v2, nullptr);

	if (v1n && v2n)
		return true;

	if (v1n || v2n)
		return false;

	return v1->m_ReferenceCounted == v2->m_ReferenceCounted;
}

bool ReferenceCounted::operator != (ReferenceCounted^ v1, ReferenceCounted^ v2)
{
	return !(v1 == v2);
}

ReferenceCounted::ReferenceCounted(irr::IReferenceCounted* referenceCounted_or_null)
{
	m_ReferenceCounted = referenceCounted_or_null;
}

ReferenceCounted::~ReferenceCounted()
{
	if (m_ReferenceCounted != nullptr) 
		Drop();
	m_ReferenceCounted = nullptr;
}

ReferenceCounted::!ReferenceCounted()
{
	// In theory, Drop should be called here in finalizer
	//  in practice, Irrlicht does not consistently grab
	//  pointers so not calling drop is consistent with existing code
	//  but the ~ method due to Dispose gives us better explicit control
	m_ReferenceCounted = nullptr;
}

bool ReferenceCounted::Drop()
{
	LIME_ASSERT(m_ReferenceCounted != nullptr);
	if (irr::IReferenceCounted* ref = m_ReferenceCounted)
	{
		m_ReferenceCounted = nullptr;
		return ref->drop();
	}
	return false;
}

void ReferenceCounted::Grab()
{
	LIME_ASSERT(m_ReferenceCounted != nullptr);
	m_ReferenceCounted->grab();
}

String^ ReferenceCounted::DebugName::get()
{
	LIME_ASSERT(m_ReferenceCounted != nullptr);
	return gcnew String(m_ReferenceCounted->getDebugName());
}

int ReferenceCounted::ReferenceCount::get()
{
	LIME_ASSERT(m_ReferenceCounted != nullptr);
	return m_ReferenceCounted->getReferenceCount();
}

} // end namespace IrrlichtLime