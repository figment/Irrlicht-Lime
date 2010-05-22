#pragma once
#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public ref class ExposedVideoData : Lime::NativeValue<video::SExposedVideoData>
{
public:

	// ...

internal:

	ExposedVideoData(const video::SExposedVideoData& value)
	{
		m_NativeValue = new video::SExposedVideoData(value);
	}
};

} // end namespace Video
} // end namespace IrrlichtLime