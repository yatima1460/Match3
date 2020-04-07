#pragma once

#include <string>
#include <SDL.h>
#include "Vector2f.hpp"
#include "Functional.hpp"

namespace Gem
{

enum GemState
{
	STATIC,
	FALLING,
	SWAPPING,
	CRACKING,
	ANIMATION_DONE
};
struct GemData
{
	std::string id;

	// Used for smooth animations
	Vector2f::Vector2fData drawingOffset;
	Vector2f::Vector2fData drawingOffsetGoal;
	GemState animation;

	GemData() : GemData("")
	{
	}

	explicit GemData(const std::string &id) : id(id), drawingOffset({0, 0}), drawingOffsetGoal({0, 0}), animation(GemState::STATIC)
	{
	}
};

CONST_FUNCTION inline bool operator==(const Gem::GemData &A, const Gem::GemData &B)
{
	return A.id == B.id;
}

} // namespace Gem