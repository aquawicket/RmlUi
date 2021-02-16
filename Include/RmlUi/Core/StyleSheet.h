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

#ifndef RMLUI_CORE_STYLESHEET_H
#define RMLUI_CORE_STYLESHEET_H

#include "Traits.h"
#include "PropertyDictionary.h"
#include "Spritesheet.h"
#include "StyleSheetTypes.h"

namespace Rml {

class Element;
class ElementDefinition;
class StyleSheetNode;
class Decorator;
class FontEffect;
class SpritesheetList;
class Stream;
class StyleSheetContainer;
class StyleSheetParser;
struct Sprite;
struct Spritesheet;

/**
	StyleSheet maintains a single stylesheet definition. A stylesheet can be combined with another stylesheet to create
	a new, merged stylesheet.

	@author Lloyd Weehuizen
 */

class RMLUICORE_API StyleSheet final : public NonCopyMoveable
{
public:
	~StyleSheet();

	using NodeList = Vector< const StyleSheetNode* >;
	using NodeIndex = UnorderedMap< size_t, NodeList >;

	/// Combines this style sheet with another one, producing a new sheet.
	UniquePtr<StyleSheet> CombineStyleSheet(const StyleSheet& sheet) const;

	/// Creates an exact copy of this style sheet.
	UniquePtr<StyleSheet> Clone() const;

	/// Builds the node index for a combined style sheet.
	void BuildNodeIndex();
	/// Optimizes some properties for faster retrieval.
	/// Specifically, converts all decorator and font-effect properties from strings to instanced decorator and font effect lists.
	void OptimizeNodeProperties();

	/// Returns the Keyframes of the given name, or null if it does not exist.
	/// @lifetime The returned pointer becomes invalidated whenever the style sheet is re-generated. Do not store this pointer or references to subobjects around.
	const Keyframes* GetKeyframes(const String& name) const;

	/// Parses the decorator property from a string and returns a list of instanced decorators.
	DecoratorsPtr InstanceDecoratorsFromString(const String& decorator_string_value, const SharedPtr<const PropertySource>& source) const;

	/// Parses the font-effect property from a string and returns a list of instanced font-effects.
	FontEffectsPtr InstanceFontEffectsFromString(const String& font_effect_string_value, const SharedPtr<const PropertySource>& source) const;

	/// Get sprite located in any spritesheet within this stylesheet.
	/// @lifetime The returned pointer becomes invalidated whenever the style sheet is re-generated. Do not store this pointer or references to subobjects around.
	const Sprite* GetSprite(const String& name) const;

	/// Returns the compiled element definition for a given element and its hierarchy.
	SharedPtr<ElementDefinition> GetElementDefinition(const Element* element) const;

	/// Retrieve the hash key used to look-up applicable nodes in the node index.
	static size_t NodeHash(const String& tag, const String& id);

private:
	StyleSheet();

	using ElementDefinitionCache = UnorderedMap< size_t, SharedPtr<ElementDefinition> >;

	/// Returns the Decorator of the given name, or null if it does not exist.
	SharedPtr<Decorator> GetDecorator(const String& name) const;
	
	// Root level node, attributes from special nodes like "body" get added to this node
	UniquePtr<StyleSheetNode> root;

	// Name of every @keyframes mapped to their keys
	KeyframesMap keyframes;

	// Name of every @decorator mapped to their specification
	DecoratorSpecificationMap decorator_map;

	// Name of every @spritesheet and underlying sprites mapped to their values
	SpritesheetList spritesheet_list;

	// Map of all styled nodes, that is, they have one or more properties.
	NodeIndex styled_node_index;

	// Index of node sets to element definitions.
	mutable ElementDefinitionCache node_cache;

	friend Rml::StyleSheetParser;
	friend Rml::StyleSheetContainer;
};

} // namespace Rml
#endif
