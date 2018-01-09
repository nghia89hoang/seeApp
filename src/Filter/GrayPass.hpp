//
//  GrayFilter.hpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/8/18.
//

#ifndef GrayFilter_hpp
#define GrayFilter_hpp

#include <stdio.h>
#include "Filterbase.hpp"

using namespace std;
namespace see {
    class GrayPass;
    typedef shared_ptr<GrayPass> GrayPassRef;
    
    class GrayPass : public RdPass {
    public:
        static GrayPassRef create() {
            GrayPassRef ref = GrayPassRef(new GrayPass());            
            ref->setup();
            return ref;
        }
        ~GrayPass();
        virtual void setup();
//        virtual void update();
//        virtual void draw();
        void setTexSize();
    protected:
        GrayPass();
    };
}

#endif /* GrayFilter_hpp */
