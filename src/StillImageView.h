//
//  StillImageView.hpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/31/18.
//

#ifndef StillImageView_hpp
#define StillImageView_hpp
#include <stdio.h>
#include "cinder/gl/gl.h"
#include "BaseView.h"
#include "ParticleController.h"
#include "Efxbase.hpp"

using namespace cinder;
using namespace po::scene;

namespace see {
    class StillImageView;
    typedef std::shared_ptr<class StillImageView>    StillImageViewRef;
    
    class StillImageView : public BaseView {
    public:
        static StillImageViewRef create();
        virtual ~StillImageView();
        virtual void onViewInit() override;
        virtual void setup() override;
        virtual void update() override;
        virtual void draw() override;
        virtual void onViewDeInit() override;
        void onMouseEvent(po::scene::MouseEvent &event);
    protected:
        StillImageView();
    private:
        gl::TextureRef mImage;
        gl::FboRef mFbo;        
        RdPassRef mPass;
    };
}
#endif /* StillImageView_hpp */
