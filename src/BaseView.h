//
//  BaseView.hpp
//  see
//
//  Created by Hoang Ngoc Nghia on 2/1/18.
//

#ifndef BaseView_hpp
#define BaseView_hpp

#include <stdio.h>
#include "poScene/View.h"

using namespace cinder;
using namespace po::scene;

namespace see {
    class BaseView;
    typedef std::shared_ptr<class BaseView>    BaseViewRef;

    class BaseView : public po::scene::View{
    public:
        virtual ~BaseView();
        
        void initialize();
        void deInitialize();
        virtual void onViewInit(){};
        virtual void onViewDeInit(){};
        virtual void setup() override;
        virtual void update() override;
        virtual void draw() override;
        
        
        void setActive(bool active) {
            mIsActive = active;
        }
        bool isActive() {
            return mIsActive;
        }
        bool isInit() {
            return mIsInit;
        }
    protected:
        BaseView();
        bool mIsActive;
        bool mIsInit;
    };

}
#endif /* BaseView_hpp */
