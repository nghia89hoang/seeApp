//
//  FaceScene.hpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/5/18.
//

#ifndef FaceScene_hpp
#define FaceScene_hpp

#include <stdio.h>
//#include <list>
#include <vector>
#include "poScene/ViewController.h"
#include "poScene/View.h"
using namespace std;
using namespace cinder;

static ivec2 sScreenSize;

namespace see {

    class ViewController;
    typedef std::shared_ptr<ViewController> ViewControllerRef;

    class ViewController : public po::scene::ViewController{
    public:        
        static ViewControllerRef create();
        void viewDidLoad() override;
        void changeView(bool isNext = true);
    protected:
        ViewController();
    private:
        vector<po::scene::ViewRef> mListView;
        int mCurView;
        po::scene::ViewRef mRoot;
    };

}
#endif /* FaceScene_hpp */
