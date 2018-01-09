//
//  GrayFilter.cpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/8/18.
//

#include "GrayPass.hpp"

using namespace std;
namespace see {
    
    GrayPass::GrayPass() {
        
    }
    void GrayPass::setup() {
        createGlslProg("filter/basic.vert", "filter/gray.frag");
    }
//    void GrayFilter::update() {
    
//    }
//    void GrayFilter::draw() {
//        
//    }
    GrayPass::~GrayPass(){
        
    }
        
    void GrayPass::setTexSize(){
//        mProg->
    }
}
