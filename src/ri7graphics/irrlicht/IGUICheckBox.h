// Copyright (C) 2002-2007 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_GUI_CHECKBOX_H_INCLUDED__
#define __I_GUI_CHECKBOX_H_INCLUDED__

#include "IGUIElement.h"

namespace irr
{
namespace gui
{

	//! GUI Check box interface.
	class IGUICheckBox : public IGUIElement
	{
	public:

		//! constructor
		IGUICheckBox(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle)
			: IGUIElement(EGUIET_CHECK_BOX, environment, parent, id, rectangle) {}

		//! destructor
		virtual ~IGUICheckBox() {}

		//! Set if box is checked.
		virtual void setChecked(bool checked) = 0;

		//! Returns true if box is checked.
		virtual bool isChecked() const = 0;
	};

} // end namespace gui
} // end namespace irr

#endif

