/**********************************************************************************
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

#include "ofxUIImageButton.h"
#include "ofxUI.h"

ofxUIImageButton::ofxUIImageButton() : ofxUIButton()
{
    
}

ofxUIImageButton::ofxUIImageButton(float x, float y, float w, float h, bool _value, string _pathURL, string _name, int _size) : ofxUIButton()
{
    useReference = false;
    init(x, y, w, h, &_value, _pathURL, _name, _size);
}

ofxUIImageButton::ofxUIImageButton(float w, float h, bool _value, string _pathURL, string _name, int _size) : ofxUIButton()
{
    useReference = false;
    init(0, 0, w, h, &_value, _pathURL, _name, _size);
}

ofxUIImageButton::ofxUIImageButton(float x, float y, float w, float h, bool *_value, string _pathURL, string _name, int _size) : ofxUIButton()
{
    useReference = true;
    init(x, y, w, h, _value, _pathURL, _name, _size);
}

ofxUIImageButton::ofxUIImageButton(float w, float h, bool *_value, string _pathURL, string _name, int _size) : ofxUIButton()
{
    useReference = true;
    init(0, 0, w, h, _value, _pathURL, _name, _size);
}

void ofxUIImageButton::init(float x, float y, float w, float h, bool *_value, string _pathURL, string _name, int _size)
{
    initRect(0,0,w,h);
    name = string(_name);
    kind = OFX_UI_WIDGET_IMAGEBUTTON;
    
    label = new ofxUILabel(w+padding,0, (name+" LABEL"), name, _size);
    addEmbeddedWidget(label);
    setLabelVisible(false); 
    
    if(useReference)
    {
        value = _value;
    }
    else
    {
        value = new bool();
        *value = *_value;
    }
    
    setValue(*_value);
    
    img = new ofImage();
    img->loadImage(_pathURL);
    bChangedImage = false;
}

ofxUIImageButton::~ofxUIImageButton()
{
    if(!bChangedImage)
    {
        delete img;
    }
}

void ofxUIImageButton::drawBack()
{
    if(draw_back && !draw_fill)
    {
        ofxUIFill();
        ofxUISetColor(color_back);
        img->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());
    }
}

void ofxUIImageButton::drawFill()
{
    if(draw_fill)
    {
        ofxUIFill();
        ofxUISetColor(color_fill);
        img->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());
    }
}

void ofxUIImageButton::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ofxUIFill();
        ofxUISetColor(color_fill_highlight);
        img->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());
    }
}

void ofxUIImageButton::drawOutlineHighlight()
{
    if(draw_outline_highlight)
    {
        ofNoFill();
        ofxUISetColor(color_outline_highlight);
        img->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());
    }
}

ofImage *ofxUIImageButton::getImage()
{
    return img;
}

void ofxUIImageButton::setImage(ofImage *_img)
{
    if(img != NULL && !bChangedImage)
    {
        delete img;
        img = NULL;
    }
    img = _img;
    bChangedImage = true;
}