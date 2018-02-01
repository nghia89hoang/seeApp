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
#include "poScene/View.h"
#include "ParticleController.h"
#include "Efxbase.hpp"

using namespace cinder;
using namespace po::scene;

namespace see {
    class StillImageView;
    typedef std::shared_ptr<class StillImageView>    StillImageViewRef;
    
    class StillImageView : public po::scene::View {
    public:
        static StillImageViewRef create();
        virtual ~StillImageView();
        virtual void setup() override;
        virtual void update() override;
        virtual void draw() override;
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
