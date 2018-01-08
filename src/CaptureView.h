//
//  CaptureView.hpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/5/18.
//

#ifndef CaptureView_hpp
#define CaptureView_hpp
#include "cinder/gl/gl.h"
#include "cinder/Capture.h"
#include "poScene/View.h"
#include <stdio.h>

using namespace cinder;
using namespace ci;
using namespace po::scene;

namespace see {
    class CaptureView;
    typedef std::shared_ptr<CaptureView> CaptureViewRef;
    
    class CaptureView : public po::scene::View {
    public:
        static CaptureViewRef create(int width, int heihgt);
        virtual ~CaptureView();
        virtual void setup(int width, int height);
        virtual void update() override;
        virtual void draw() override;
        virtual View& removeFromSuperview() override;
        
        void printDeviceInfo();
    protected:
        CaptureView();
        void initGrayProg();
        void initSobelProg();
    private:
        int mWidth, mHeight;
        CaptureRef mCapture;
        gl::FboRef mFbo;
        gl::GlslProgRef mGrayProg;
        gl::GlslProgRef mSobelProg;
        gl::TextureRef mTex0;
        gl::TextureRef mTex1;
        gl::TextureRef mCaptureTex;
    };
}

#endif /* CaptureView_hpp */
