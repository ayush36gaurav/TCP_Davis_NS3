/*
 * Copyright (c) 2007 INRIA, Mathieu Lacage
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Authors: Mathieu Lacage <mathieu.lacage@gmail.com>
 */
#ifndef OBJECT_MAP_H
#define OBJECT_MAP_H

#include "attribute.h"
#include "object-ptr-container.h"
#include "object.h"
#include "ptr.h"

/**
 * \file
 * \ingroup attribute_ObjectMap
 * ns3::ObjectMap attribute value declarations and template implementations.
 */

namespace ns3
{

/**
 * \ingroup attribute_ObjectMap
 * ObjectMapValue is an alias for ObjectPtrContainerValue
 */
typedef ObjectPtrContainerValue ObjectMapValue;

/**
 * \ingroup attribute_ObjectMap
 * MakeAccessorHelper implementation for ObjectVector.
 * \copydetails ns3::DoMakeAccessorHelperOne(U T::*)
 */
template <typename T, typename U>
Ptr<const AttributeAccessor> MakeObjectMapAccessor(U T::*memberVariable);

// Documentation generated by print-introspected-doxygen.cc
template <typename T>
Ptr<const AttributeChecker> MakeObjectMapChecker();

/**
 * \ingroup attribute_ObjectMap
 * \copydoc ns3::MakeObjectPtrContainerAccessor()
 */
template <typename T, typename U, typename INDEX>
Ptr<const AttributeAccessor> MakeObjectMapAccessor(Ptr<U> (T::*get)(INDEX) const,
                                                   INDEX (T::*getN)() const);

/**
 * \ingroup attribute_ObjectMap
 * \copydoc ns3::MakeObjectPtrContainerAccessor()
 */
template <typename T, typename U, typename INDEX>
Ptr<const AttributeAccessor> MakeObjectMapAccessor(INDEX (T::*getN)() const,
                                                   Ptr<U> (T::*get)(INDEX) const);

/***************************************************************
 *  Implementation of the templates declared above.
 ***************************************************************/

template <typename T, typename U>
Ptr<const AttributeAccessor>
MakeObjectMapAccessor(U T::*memberVector)
{
    struct MemberStdContainer : public ObjectPtrContainerAccessor
    {
        bool DoGetN(const ObjectBase* object, std::size_t* n) const override
        {
            const T* obj = dynamic_cast<const T*>(object);
            if (obj == nullptr)
            {
                return false;
            }
            *n = (obj->*m_memberVector).size();
            return true;
        }

        Ptr<Object> DoGet(const ObjectBase* object,
                          std::size_t i,
                          std::size_t* index) const override
        {
            const T* obj = static_cast<const T*>(object);
            auto begin = (obj->*m_memberVector).begin();
            auto end = (obj->*m_memberVector).end();
            uint32_t k = 0;
            for (auto j = begin; j != end; j++, k++)
            {
                if (k == i)
                {
                    *index = (*j).first;
                    return (*j).second;
                }
            }
            NS_ASSERT(false);
            // quiet compiler.
            return nullptr;
        }

        U T::*m_memberVector;
    }* spec = new MemberStdContainer();

    spec->m_memberVector = memberVector;
    return Ptr<const AttributeAccessor>(spec, false);
}

template <typename T>
Ptr<const AttributeChecker>
MakeObjectMapChecker()
{
    return MakeObjectPtrContainerChecker<T>();
}

template <typename T, typename U, typename INDEX>
Ptr<const AttributeAccessor>
MakeObjectMapAccessor(Ptr<U> (T::*get)(INDEX) const, INDEX (T::*getN)() const)
{
    return MakeObjectPtrContainerAccessor<T, U, INDEX>(get, getN);
}

template <typename T, typename U, typename INDEX>
Ptr<const AttributeAccessor>
MakeObjectMapAccessor(INDEX (T::*getN)() const, Ptr<U> (T::*get)(INDEX) const)
{
    return MakeObjectPtrContainerAccessor<T, U, INDEX>(get, getN);
}

} // namespace ns3

#endif /* OBJECT_MAP_H */