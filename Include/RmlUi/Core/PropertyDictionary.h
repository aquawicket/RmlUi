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

#ifndef RMLUI_CORE_PROPERTYDICTIONARY_H
#define RMLUI_CORE_PROPERTYDICTIONARY_H

#include "Header.h"
#include "Property.h"

namespace Rml {

/**
	A dictionary to property names to values.

	@author Peter Curry
 */

class RMLUICORE_API PropertyDictionary
{
public:
	PropertyDictionary();

	/// Sets a property on the dictionary. Any existing property with the same id will be overwritten.
	void SetProperty(PropertyId id, const Property& property);
	/// Removes a property from the dictionary, if it exists.
	void RemoveProperty(PropertyId id);
	/// Returns the value of the property with the requested id, if one exists.
	const Property* GetProperty(PropertyId id) const;

	/// Returns the number of properties in the dictionary.
	int GetNumProperties() const;
	/// Returns the map of properties in the dictionary.
	const PropertyMap& GetProperties() const;

	/// Merges the contents of another fully-specified property dictionary with this one.
	/// Properties defined in the new dictionary will overwrite those with the same id.
	/// @param[in] property_dictionary The dictionary to merge.
	void Merge(const PropertyDictionary& property_dictionary);

	/// Set the source of all properties in the dictionary to the given one.
	void SetSourceOfAllProperties(const SharedPtr<const PropertySource>& property_source);

private:
	PropertyMap properties;
};

} // namespace Rml
#endif
