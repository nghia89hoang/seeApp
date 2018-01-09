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
        gl::Fbo::Format format;
        mFbo = gl::Fbo::create(1024, 1024, format.depthTexture());
        
        mFilter = Filterbase::create();
        mGrayPass = GrayPass::create();
        mGrayPass->setInputTexture(0, mCaptureTex);
        
        try {
            initCapture(width, height);
            mCapture->start();
        } catch (ci::Exception &exec) {
            CI_LOG_EXCEPTION("Failed to init capture", exec);
        }
        
    }

    void CaptureView::update() {
        if(mCapture && mCapture->checkNewFrame()) {
            Surface8uRef surf = mCapture->getSurface();
            cv::Mat surfMat(toOcv(*surf));

            mCaptureTex = gl::Texture::create( fromOcv(surfMat), gl::Texture::Format().loadTopDown());
            mGrayPass->setInputTexture(0, mCaptureTex);
        }
    }
    
    void CaptureView::draw() {
        gl::clear( Color( 0.0f, 0.0f, 0.0f ) );
        if(mCaptureTex) {
            {
#if defined CINDER_COCOA_TOUCH
                gl::rotate( M_PI / 2 );
                gl::translate( 0, - getWindowWidth() );
                Rectf flippedBounds( 0, 0, getWindowHeight(), getWindowWidth() );
#if defined( CINDER_ANDROID )
                std::swap( flippedBounds.y1, flippedBounds.y2 );
#endif
                mGrayPass->draw();
#endif
            }
            {
                gl::rotate( M_PI / 2 );
                gl::translate( 0, - getWindowWidth() );
                gl::setMatricesWindow( toPixels( getWindowSize() ) );
                gl::draw( mFbo->getColorTexture(), Rectf( 0, 0, 128, 128 ) );
            }
        }
    }
    
    View& CaptureView::removeFromSuperview() {
        console() << "removeFromSuperview";
        return View::removeFromSuperview();
    }
//    void CaptureView::initGrayProg() {
//        mGrayProg = gl::GlslProg::create(gl::GlslProg::Format()
//                                         .vertex(loadAsset("filter/basic.vert"))
//                                         .fragment(loadAsset("filter/copy.frag")));
//        mGrayProg->uniform("uTexSize", vec2(640.0f, 480.0f));
//    }
//    void CaptureView::initSobelProg() {
//        mSobelProg = gl::GlslProg::create(gl::GlslProg::Format()
//          .vertex(loadAsset("filter/basic.vert"))
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
    
    void CaptureView::initCapture(int width, int height, bool frontDevice) {
        for(const auto &device : Capture::getDevices()) {
            console() << "Devices: " << device->getName() << " "
    #if defined(CINDER_COCOA_TOUCH) || defined(CINDER_ANDROID)
            << (device->isFrontFacing()?"Front":"Rear") << "-facing"
    #endif
            << std::endl;
    #if defined(CINDER_COCOA_TOUCH) || defined(CINDER_ANDROID)
            if(device->isFrontFacing() && frontDevice) {
                mCapture = Capture::create(width, height, device);
            }
    #endif
        }
    }
}

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
