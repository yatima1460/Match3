#pragma once

#include <string>
#include <SDL.h>
#include "Vector2i.hpp"
#include "Functional.hpp"

namespace Gem
{
struct GemData
{
	std::string id;

	// Used for smooth animations
	Vector2i drawingOffset;

	GemData() : GemData("")
	{
	}

	explicit GemData(const std::string& id) : id(id), drawingOffset({0, 0})
	{

	}


  

	
};

CONST inline bool operator==(const Gem::GemData& A, const Gem::GemData& B)
{
	return A.id == B.id;
}

} // namespace Gem