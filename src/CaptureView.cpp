//
//  CaptureView.cpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/5/18.
//

#include "CaptureView.h"
#include "cinder/app/App.h"
#include "cinder/Log.h"
#include "CinderOpenCV.h"
#include "cinder/ImageIo.h"
using namespace po::scene;
using namespace cinder::app;
namespace see {
    
    CaptureView::CaptureView() {
        
    }
    CaptureView::~CaptureView() {
        
    }
    CaptureViewRef CaptureView::create(int width, int height) {
        console() << "Capture view created with size: "<<width <<" "<<height<<std::endl;
        CaptureViewRef ref = CaptureViewRef(new CaptureView());
        ref->setup(width, height);
        return ref;
    }
    void CaptureView::setup(int width, int height) {
        mWidth = width;
        mHeight = height;
        try {
            initCapture(width, height);
            mCapture->start();
        } catch (ci::Exception &exec) {
            CI_LOG_EXCEPTION("Failed to init capture", exec);
        }
        
        gl::Fbo::Format format;
        mFbo = gl::Fbo::create(width, height, format.depthTexture());
        
        mEfx = TestEfx::create(mFbo);
        mEfx->setTexSize(vec2(width, height));
        
    }

    void CaptureView::update() {
        if(mCapture && mCapture->checkNewFrame()) {
            Surface8uRef surf = mCapture->getSurface();
            if(!mCaptureTex) {
                mCaptureTex = gl::Texture::create( *surf, gl::Texture::Format().loadTopDown());
                mEfx->updateInputTexture(mCaptureTex);
            } else {
                mCaptureTex->update(*surf);
            }
            mEfx->update();
        }
    }
    
    void CaptureView::draw() {
        gl::clear( Color( 0.0f, 0.0f, 0.0f ) );
        if(mCaptureTex) {
            {
#if defined CINDER_COCOA_TOUCH
//                gl::rotate( M_PI / 2 );
//                gl::translate( 0, - getWindowWidth() );
                Rectf flippedBounds( 0, 0, getWindowHeight(), getWindowWidth() );
#if defined( CINDER_ANDROID )
                std::swap( flippedBounds.y1, flippedBounds.y2 );
#endif
                mEfx->draw();
#endif
            }
        }
    }
    
    View& CaptureView::removeFromSuperview() {
        console() << "removeFromSuperview\n";
        return View::removeFromSuperview();
    }
    
    void CaptureView::initCapture(int width, int height, bool frontDevice) {
        for(const auto &device : Capture::getDevices()) {
            console() << "Devices: " << device->getName() << " "
    #if defined(CINDER_COCOA_TOUCH) || defined(CINDER_ANDROID)
            << (device->isFrontFacing()?"Front":"Rear") << "-facing"
    #endif
            << std::endl;
    #if defined(CINDER_COCOA_TOUCH) || defined(CINDER_ANDROID)
            if(device->isFrontFacing() && frontDevice) {
                device->getNative();
                mCapture = Capture::create(width, height, device);
                Area r = mCapture->getBounds();
                console() << r << endl;
            }
    #else
            mCapture = Capture::create(width, height);
    #endif
        }
    }
}
//    void CaptureView::initSobelProg() {
//        mSobelProg = gl::GlslProg::create(gl::GlslProg::Format()
//        .vertex(loadAsset("filter/basic.vert"))
//        .fragment(loadAsset("filter/dilation.frag")));
//        .fragment(loadAsset("filter/billboard.frag")));
//        .fragment(loadAsset("filter/lowBlur.frag")));
//        .fragment(loadAsset("filter/sobel.frag")));
//        .fragment(loadAsset("filter/worhol.frag")));
//        .fragment(loadAsset("filter/thermal.frag")));
//        .fragment(loadAsset("filter/vignette.frag")));
//        .fragment(loadAsset("filter/cell.frag")));
//        .fragment(loadAsset("filter/scanline.frag")));
//                                          .fragment(loadAsset("filter/dream.frag")));
//                                          .fragment(loadAsset("filter/erosion.frag")));
//                                          .fragment(loadAsset("filter/hexpix.frag")));
//                                          .fragment(loadAsset("filter/posterize.frag")));
//                                          .fragment(loadAsset("filter/line.frag")));
//        mSobelProg->uniform("uTexSize", vec2(640.0f, 480.0f));
//    }
//
//bool seeApp::detector(cv::InputArray in, cv::OutputArray out) {
//    cv::Mat gray;
//    std::vector<cv::Rect> faces;
//    if(in.channels() > 1) {
//        cv::cvtColor(in, gray, CV_BGR2GRAY);
//    } else {
//        gray = in.getMat().clone();
//    }
//    cv::equalizeHist(gray, gray);
//    mFaceCascade.detectMultiScale(gray, faces, 1.1, 3, 0, cv::Size(30, 30));
//    cv::Mat(faces).copyTo(out);
//    return true;
//}
