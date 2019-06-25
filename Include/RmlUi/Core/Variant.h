/*
 * This source file is part of RmlUi, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://github.com/mikke89/RmlUi
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 * Copyright (c) 2019 The RmlUi Team, and contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef RMLUIVARIANT_H
#define RMLUIVARIANT_H

#include "Header.h"
#include "Types.h"
#include "TypeConverter.h"
#include "Animation.h"

namespace Rml {
namespace Core {

/**
	Variant is a container that can store a selection of basic types. The variant will store the
	value in the native form corresponding to the version of Set that was called.

	Get is templated to convert from the stored form to the requested form by using a TypeConverter.

	@author Lloyd Weehuizen
 */

class RMLUICORE_API Variant
{
public:
	/// Type of data stored in the variant.
	enum Type
	{
		NONE = '-',
		BYTE = 'b',
		CHAR = 'c',
		FLOAT = 'f',
		INT = 'i',
		STRING = 's',
		WORD = 'w',
		VECTOR2 = '2',
		VECTOR3 = '3',
		VECTOR4 = '4',
		COLOURF = 'g',
		COLOURB = 'h',
		SCRIPTINTERFACE = 'p',
		TRANSFORMREF = 't',
		TRANSITIONLIST = 'T',
		ANIMATIONLIST = 'A',
		DECORATORLIST = 'D',
		VOIDPTR = '*',
	};

	Variant();
	Variant(const Variant&);
	Variant(Variant&&);
	Variant& operator=(const Variant& copy);
	Variant& operator=(Variant&& other);
	~Variant();

	// Construct by variant type
	template< typename T >
	Variant(const T& t);
	template< typename T >
	Variant(T&& t);

	// Assign by variant type
	template<typename T>
	Variant& operator=(const T& t);
	template<typename T>
	Variant& operator=(T&& t);

	void Clear();

	inline Type GetType() const;

	/// Templatised data accessor. TypeConverters will be used to attempt to convert from the
	/// internal representation to the requested representation.
	/// @param[in] default_value The value returned if the conversion failed.
	/// @return Data in the requested type.
	template< typename T >
	T Get(T default_value = T()) const;

	/// Templatised data accessor. TypeConverters will be used to attempt to convert from the
	/// internal representation to the requested representation.
	/// @param[out] value Data in the requested type.
	/// @return True if the value was converted and returned, false if no data was stored in the variant.
	template< typename T >
	bool GetInto(T& value) const;

	/// Returns a reference to the variants underlying type.
	/// @warning: Undefined behavior if T does not represent the underlying type of the variant.
	template< typename T>
	const T& GetReference() const;

	bool operator==(const Variant& other) const;
	bool operator!=(const Variant& other) const { return !(*this == other); }

private:

	/// Copy another variant's data to this variant.
	/// @warning Does not clear existing data.
	void Set(const Variant& copy);
	void Set(Variant&& other);

	void Set(const byte value);
	void Set(const char value);
	void Set(const float value);
	void Set(const int value);
	void Set(const word value);
	void Set(const char* value);
	void Set(void* value);
	void Set(const Vector2f& value);
	void Set(const Vector3f& value);
	void Set(const Vector4f& value);
	void Set(const Colourf& value);
	void Set(const Colourb& value);
	void Set(ScriptInterface* value);

	void Set(const String& value);
	void Set(String&& value);
	void Set(const TransformRef& value);
	void Set(TransformRef&& value);
	void Set(const TransitionList& value);
	void Set(TransitionList&& value);
	void Set(const AnimationList& value);
	void Set(AnimationList&& value);
	void Set(const DecoratorList& value);
	void Set(DecoratorList&& value);
	
	static constexpr size_t LOCAL_DATA_SIZE = sizeof(TransitionList);

	Type type;
	alignas(TransitionList) char data[LOCAL_DATA_SIZE];
};

}
}

#include "Variant.inl"

#endif
