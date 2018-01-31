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
#include "poScene/View.h"
#include "ParticleController.h"

using namespace cinder;
using namespace po::scene;

namespace see {
    class ExpView;
    typedef std::shared_ptr<class ExpView>    ExpViewRef;
    
    class ExpView : public po::scene::View {
    public:
        static ExpViewRef create();
        virtual ~ExpView();
        virtual void setup() override;
        virtual void update() override;
        virtual void draw() override;
        void onMouseEvent(po::scene::MouseEvent &event);
        
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
