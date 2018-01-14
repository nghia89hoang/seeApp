//
//  FilterMgr.hpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/8/18.
//

#ifndef FilterMgr_hpp
#define FilterMgr_hpp

#include <stdio.h>
#include <list>
#include <map>
#include "Efxbase.hpp"
using namespace std;

namespace see {
    class FilterMgr;
    typedef shared_ptr<FilterMgr> FilterMgrRef;
    
    class FilterMgr {
    public:
        static FilterMgrRef get() {
            if(!mInstance) {
                mInstance = FilterMgrRef(new FilterMgr());
            }
            return mInstance;
        }
        virtual ~FilterMgr();
    protected:
        FilterMgr();
        static FilterMgrRef mInstance;
        map<int, EfxbaseRef> mEfxMap;
    };
}

#endif /* FilterMgr_hpp */
