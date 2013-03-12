/*==============================================================================
 
 Copyright (c) 2010, 2011, 2012 Christopher Baker <http://christopherbaker.net>
 
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
 
 ==============================================================================*/

#pragma once
#include "ofMain.h"

// TODO: readback of pure TEXTURES (i.e. syphon or fbos)
// using this scenario not efficient, especially when it's all going right back
// onto the graphics card.  need a better way to pass textures as video frames w/o all the
// other info.

//template<typename T>
//class ofImage_;
//
//typedef ofImage_<unsigned char> ofImage;
//typedef ofImage_<float> ofFloatImage;
//typedef ofImage_<unsigned short> ofShortImage;


typedef ofImage ofxVideoFrame; // we need a smarter ofImage here --
                               // ofxVideoFrame below might be an option, but since ofImage
                               // already has a member ofTexture, it all seems rather redundant

typedef ofFloatImage ofxFloatVideoFrame;
typedef ofShortImage ofxShortVideoFrame;

// could subclass ofImage and access protected tex and bIsUsingTexture --
// it will still draw, even if it it does not have pixels allocated
// problems arise w/ getWidth() / getHeight(), which are set w/ freeimage, etc.

typedef ofPtr< ofxVideoFrame >  ofxSharedVideoFrame;
typedef ofPtr< ofxFloatVideoFrame >  ofxSharedFloatVideoFrame;
typedef ofPtr< ofxShortVideoFrame >  ofxSharedShortVideoFrame;


///////////

//class ofxVideoFrame : public ofBaseDraws {
//public:
//    
////    static ofPtr< ofxVideoFrame > getImage();
//    
//    
//    ofxVideoFrame() {
//        textureOnly = false;
//    };
//    
//    ofxVideoFrame(bool _TextureOnly) {
//        textureOnly = _TextureOnly;
//    };
//    
//    
//    ofxVideoFrame(const ofImage& _img) {
//        img = _img;
//        textureOnly = false;
//    };
//    
//    ofxVideoFrame(const ofTexture& _tex) {
//        tex = _tex;
//        textureOnly = true;
//    };
//
//    virtual ~ofxVideoFrame() {};
//
//    
//    void update() {
//        if(!textureOnly) img.update();
//    }
//
//    
//    void allocate();
//    
//    
//    bool loadImage(const string& file) {
//        if(textureOnly) tex.clear();
//        textureOnly = false;
//        return img.loadImage(file);
//    }
//    
//    void setFromPixels(const ofPixelsRef pixels) {
//        textureOnly ? tex.loadData(pixels) : img.setFromPixels(pixels);
//    }
//    
//    // from ofBaseDraws
//	void draw(float x, float y) {
//        textureOnly ? tex.draw(x,y) : img.draw(x,y);
//    };
//    
//	void draw(float x, float y, float w, float h) {
//        textureOnly ? tex.draw(x,y,w,h) : img.draw(x,y,w,h);
//    };
//	
//	float getHeight() {
//        return textureOnly ? tex.getHeight() : img.getHeight();
//    }
//    
//	float getWidth() {
//        return textureOnly ? tex.getWidth() : img.getWidth();
//    }
//	
//	void setAnchorPercent(float xPct, float yPct) {
//        textureOnly ? tex.setAnchorPercent(xPct,yPct) : img.setAnchorPercent(xPct,yPct);
//    }
//	void setAnchorPoint(float x, float y){
//        return textureOnly ? tex.setAnchorPoint(x,y) : img.setAnchorPoint(x,y);
//    }
//	void resetAnchor(){
//        return textureOnly ? tex.resetAnchor() : img.resetAnchor();
//    };
//    
//    // from ofBaseHasTexture
//	ofTexture & getTextureReference() {
//        return textureOnly ? tex : img.getTextureReference();
//    }
//    
//	void setUseTexture(bool bUseTex) {
//        if(!textureOnly) {
//            img.setUseTexture(bUseTex);
//        } else {
//            ofLogWarning() << "ofxSharedVideoFrame: setUseTexture() has no effect when the frame is a pure texture.";
//        }
//    }
//
//    bool isAllocated() {
//        return textureOnly ? tex.isAllocated() : img.isAllocated();
//    }
//    
//    void convertToPixelBacked() {
//        if(textureOnly) {
//            ofPixels pix;
//            tex.readToPixels(pix);
//            img.setFromPixels(pix);
//            tex.clear();
//            textureOnly = false;
//        } else {
//            ofLogWarning() << "ofxSharedVideoFrame: convertToPixelBacked() has no effect when the frame is not a pure texture.";
//        }
//    }
//    
//    
//    
//private:
//    bool textureOnly;
//    
//    ofImage   img;
//    ofTexture tex;
//    
//};




