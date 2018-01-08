//
//  FaceScene.hpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/5/18.
//

#ifndef FaceScene_hpp
#define FaceScene_hpp

#include <stdio.h>
#include <list>
#include "poScene/ViewController.h"
#include "poScene/View.h"
#include "TestView.h"
#include "CaptureView.h"
using namespace std;
namespace see {

    class ViewController;
    typedef std::shared_ptr<ViewController> ViewControllerRef;

    class ViewController : public po::scene::ViewController{
    public:
        static ViewControllerRef create();
        void viewDidLoad() override;
    protected:
        ViewController();
    private:
        list<ViewRef> mListView;
        po::scene::ViewRef mRoot;
        TestViewRef mTestView;
        CaptureViewRef mCaptureView;
    };

}
#endif /* FaceScene_hpp */
