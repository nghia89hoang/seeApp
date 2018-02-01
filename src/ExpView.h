//
//  ExpView.hpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/20/18.
//
#ifndef ExpView_hpp
#define ExpView_hpp

#include <stdio.h>
#include "cinder/gl/gl.h"
#include "BaseView.h"
#include "ParticleController.h"

using namespace cinder;
using namespace po::scene;

namespace see {
    class ExpView;
    typedef std::shared_ptr<class ExpView>    ExpViewRef;
    
    class ExpView : public BaseView {
    public:
        static ExpViewRef create();
        virtual ~ExpView();
        virtual void onViewInit() override;
        virtual void setup() override;
        virtual void update() override;
        virtual void draw() override;
        virtual void onViewDeInit() override;
        void onMouseEvent(po::scene::MouseEvent &event);
        void onTouchEvent(po::scene::TouchEvent &event);
    protected:
        ExpView();
        void addParticleGrid(int cellSize);
    private:
        CameraPersp mCam;
        gl::TextureRef mImg;
        ParticleController mParticleCtl;
        Channel32fRef mChannel;
        vec2 mMousePos;
        bool mIsMousePressed;
    };
}

#endif /* ExpView_hpp */
