#pragma once

#include "gqobject.h"

using namespace gquake;

// TODO: Add to .inl
template <typename T>
T* GQObject::get_child(int index)
{
	if (m_Children.size() <= index) return nullptr;
	return reinterpret_cast<T*>(m_Children[index]);
}

template <typename T>
T* GQObject::get_parent()
{
	if (m_Parent) return m_Parent;
	else return nullptr; // This means we are the root
}
