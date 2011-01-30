/*
Copyright (c) 2010 Jan Miguel Garcia (bobbysing)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include "CGUI.h"

CText::CText( TiXmlElement * pElement )
{
	SetElement( pElement );

	SetThemeElement( gpGui->GetThemeElement( "Text" ) );

	if( !GetThemeElement() )
		MessageBoxA( 0, "Theme element invalid.", "Text", 0 );
	else
		SetElementState( "Norm" );
}

void CText::Draw()
{
	CPos Pos = *GetParent()->GetAbsPos() + *GetRelPos();
	
	gpGui->GetFont()->DrawString( Pos.GetX(), Pos.GetY(), 0, pString, GetFormatted(), GetWidth() );
}

void CText::PreDraw()
{
	GetString( true );
}

void CText::MouseMove( CMouse & pMouse )
{
	CPos Pos = *GetParent()->GetAbsPos() + *GetRelPos();

	SetElementState( SetMouseOver( pMouse.InArea( Pos.GetX(), Pos.GetY(), gpGui->GetFont()->GetStringWidth( GetFormatted().c_str() ), gpGui->GetFont()->GetStringHeight() ) )?"MouseOver":"Norm" );
}

void CText::UpdateTheme( int iIndex )
{
	SElementState * pState = GetElementState( iIndex );

	pString = pState->GetColor( "String" );
}