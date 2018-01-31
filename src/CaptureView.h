//
//  CaptureView.hpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/5/18.
//

#ifndef CaptureView_hpp
#define CaptureView_hpp
#include "poScene/View.h"
#include "TestEfx.hpp"
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
        virtual void setup() override;
        virtual void update() override;
        virtual void draw() override;
        virtual View& removeFromSuperview() override;
        void initCapture(int width, int height, bool frontDevice = true);
        void keyDown(cinder::app::KeyEvent event) {}
    protected:
        CaptureView();        
        void initEffect();
    private:
        int mWidth, mHeight;        
        TestEfxRef mEfx;
        CaptureRef mCapture;
        gl::FboRef mFbo;
        gl::GlslProgRef mProg;
        gl::TextureRef mTex0;
        gl::TextureRef mTex1;
        gl::TextureRef mCaptureTex;
    };
}

#endif /* CaptureView_hpp */
